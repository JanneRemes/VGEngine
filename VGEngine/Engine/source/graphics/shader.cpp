
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"

using namespace vg;

Shader::Shader(const AttributeNameMap& attributeNames) :
    mVertexElementNames(attributeNames)
{
    mProgramId = glCreateProgram();
    mVertexId = glCreateShader(GL_VERTEX_SHADER);
    mFragmentId = glCreateShader(GL_FRAGMENT_SHADER);

	for (auto& pair : mVertexElementNames)
	{
		glBindAttribLocation(mProgramId, pair.first, pair.second.c_str());
	}
}

bool Shader::load(FileManager& fileManager, const std::string& vertexPath, const std::string& fragmentPath)
{
    // compile shaders
    std::string buffer;
    fileManager.readAsset(mSubFolder + vertexPath, buffer);
    if (compileShaderSource(mVertexId, buffer) != GL_TRUE)
    {
        Log("ERROR", "Vertex shader compile error!", "");
        return false;
    }

    fileManager.readAsset(mSubFolder + fragmentPath, buffer);
    if (compileShaderSource(mFragmentId, buffer) != GL_TRUE)
    {
        Log("ERROR", "Fragment shader compile error!", "");
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
        Log("ERROR", "Shader program link error!", "");
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
    result[Color] = "attrColor";
    result[TexCoord] = "varyTexCoord";
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
