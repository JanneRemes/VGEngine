
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"
#include "engine/game/game.h"
using namespace std;
using namespace vg;
using namespace glm;

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
    
    gl::useProgram(mProgramId);

    mProjectionLocation = glGetUniformLocation(mProgramId, "unifProjection");
    if (mProjectionLocation < 0)
        Log("SHADER", "unifProjection not found!", "");

    mViewLocation = glGetUniformLocation(mProgramId, "unifView");
    if (mViewLocation < 0)
        Log("SHADER", "unifView not found!", "");

    mWorldLocation = glGetUniformLocation(mProgramId, "unifWorld");
    if (mWorldLocation < 0)
        Log("SHADER", "unifWorld not found!", "");

    resetUniforms();
    updateUniforms();

    gl::useProgram(0u);

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

void Shader::resetUniforms()
{
    setPosition(0.0f, 0.0f);
    setRotation(0);
    setScale(1.0f);
}

void Shader::setPosition(float x, float y)
{
    mPosition = vec2(x, y);
}

void Shader::setRotation(float degrees)
{
    mRotation = degrees;
}

void Shader::setScale(float scale)
{
    mScale = scale;
}

void Shader::updateUniforms()
{
    mViewTransfrom = inverse(translate(vec3(mPosition, 1.0f / mScale)));
    glUniformMatrix4fv(mViewLocation, 1, GL_FALSE, value_ptr(mViewTransfrom));

    mWorldTransform = rotate(mRotation, vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(mWorldLocation, 1, GL_FALSE, value_ptr(mWorldTransform));

    ///@ todo get screen size
	float screenX = (float)Game::getInstance()->getGraphics()->getContext()->getWidth();
	float screenY = (float)Game::getInstance()->getGraphics()->getContext()->getHeight();
	mProjectionTransform = glm::perspective(120.0f, screenX /screenY , 0.1f, 1000.0f);
    glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, glm::value_ptr(mProjectionTransform));
}
