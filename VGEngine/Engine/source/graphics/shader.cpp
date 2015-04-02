
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"

using namespace std;
using namespace vg;

const std::string FOLDER = "shaders/"; ///< subfolder for shader sources

Shader::Shader(const AttributeNameMap& attributeNames) :
    mVertexElementNames(attributeNames)
{
    mInitialized = false;
}

Shader::Shader(const Shader& shader)
{
    mVertexId = shader.mVertexId;
    mFragmentId = shader.mFragmentId;
    mProgramId = shader.mProgramId;
    mVertexElementNames = shader.mVertexElementNames;
    mInitialized = shader.mInitialized;
    mProjectionLocation = shader.mProjectionLocation;
    mViewLocation = shader.mViewLocation;
    mWorldLocation = shader.mWorldLocation;
}

void Shader::initialize()
{
    mProgramId = glCreateProgram();
    mVertexId = glCreateShader(GL_VERTEX_SHADER);
    mFragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    for (auto& pair : mVertexElementNames)
    {
        glBindAttribLocation(mProgramId, pair.first, pair.second.c_str());
    }
    mInitialized = true;
}

bool Shader::isInitialized()
{
    return mInitialized;
}

bool Shader::load(FileManager& fileManager, const std::string& vertexPath, const std::string& fragmentPath)
{
    if (!mInitialized)
        initialize();

    // compile shaders
    std::string buffer;
    fileManager.readAsset(FOLDER + vertexPath, buffer);
    if (compileShaderSource(mVertexId, buffer) != GL_TRUE)
    {
        Log("SHADER", "Vertex shader compile error!", "");
        printErrorLog(mVertexId);
        return false;
    }

    fileManager.readAsset(FOLDER + fragmentPath, buffer);
    if (compileShaderSource(mFragmentId, buffer) != GL_TRUE)
    {
        Log("SHADER", "Fragment shader compile error!", "");
        printErrorLog(mFragmentId);
        return false;
    }

    // link program
    GLint result = GL_FALSE;
    glAttachShader(mProgramId, mVertexId);
    glAttachShader(mProgramId, mFragmentId);
    glLinkProgram(mProgramId);
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);

    if (result != GL_TRUE)
    {
        Log("SHADER", "Shader program link error!", "");
        return false;
    }

    mProjectionLocation = glGetUniformLocation(mProgramId, "unifProjection");
    if (mProjectionLocation < 0)
        Log("SHADER", "unifProjection not found!", "");

    mViewLocation = glGetUniformLocation(mProgramId, "unifView");
    if (mViewLocation < 0)
        Log("SHADER", "unifView not found!", "");

    mWorldLocation = glGetUniformLocation(mProgramId, "unifWorld");
    if (mWorldLocation < 0)
        Log("SHADER", "unifWorld not found!", "");

    setUniforms();

    return true;
}

GLuint Shader::getProgramId()
{
    return mProgramId;
}

void Shader::useProgram()
{
	glUseProgram(mProgramId);
}

void Shader::unUseProgram()
{
	glUseProgram(0u);
}

const AttributeNameMap& Shader::getVertexElementNames()
{
    return mVertexElementNames;
}

AttributeNameMap Shader::getDefaultAttribNames()
{
    AttributeNameMap result;
    result[Position] = "attrPosition";
    result[Color] = "attrColor";
    result[TexCoord] = "attrTexCoord";
    return result;
}

GLint Shader::compileShaderSource(GLuint id, const std::string& source)
{
    GLint result = GL_FALSE;
    const char* temp = source.c_str();
    glShaderSource(id, 1, &temp, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    return result;
}

void Shader::printErrorLog(GLuint shader)
{
    GLint bufferLenght;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufferLenght);
    vector<GLchar> buffer(bufferLenght);
    glGetShaderInfoLog(shader, buffer.size(), nullptr, buffer.data());

    Log("SHADER", "%s", buffer.data());

}

void Shader::setUniforms()
{
    gl::useProgram(mProgramId);

    ///@ todo get screen size
    mProjectionTransform = glm::perspective(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
    glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, glm::value_ptr(mProjectionTransform));

    mViewTransfrom = glm::inverse(glm::translate(glm::vec3(1.0f, 0.0f, 3.0f)));
    glUniformMatrix4fv(mViewLocation, 1, GL_FALSE, glm::value_ptr(mViewTransfrom));

    mWorldTransform = glm::rotate(0.15f * 360, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(mWorldLocation, 1, GL_FALSE, glm::value_ptr(mWorldTransform));
    
    gl::useProgram(0u);
}
