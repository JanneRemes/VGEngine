
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"

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

    return true;
}

GLuint Shader::getProgramId()
{
    return mProgramId;
}

const AttributeNameMap& Shader::getVertexElementNames()
{
    return mVertexElementNames;
}

AttributeNameMap Shader::getDefaultAttribNames()
{
    AttributeNameMap result;
    result[Position] = "attrPosition";
    //result[Color] = "attrColor";
    //result[TexCoord] = "attrTexCoord";
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
