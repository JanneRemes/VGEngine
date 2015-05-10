
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"
#include "engine/game/game.h"

using namespace std;
using namespace vg::graphics;
using namespace glm;

const std::string FOLDER = "shaders/"; ///< subfolder for shader sources

Shader::Shader(const VariableNames& attributeNames, const UniformNames& uniformNames) 
: mVertexElementNames(attributeNames), mUniformNames(uniformNames)
{
    mInitialized = false;
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
        Log("ERROR", "Vertex shader compile error!", "");
        printErrorLog(mVertexId);
        return false;
    }

    fileManager.readAsset(FOLDER + fragmentPath, buffer);
    if (compileShaderSource(mFragmentId, buffer) != GL_TRUE)
    {
        Log("ERROR", "Fragment shader compile error!", "");
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
        Log("ERROR", "Shader program link error!", "");
        return false;
    }
    
	//uniforms
    gl::useProgram(mProgramId);
	for (auto& pair : mUniformNames)
	{
		GLuint location = glGetUniformLocation(mProgramId, pair.second.getName().c_str());
        if (location < 0)
        {
            Log("ERROR", "Shader uniform %s not found!", pair.second.getName().c_str());
        }
		pair.second.setLocation(location);
	}
    gl::useProgram(0u);

    return true;
}

GLuint Shader::getProgramId()
{
    return mProgramId;
}

void Shader::useProgram()
{
	gl::useProgram(mProgramId);
}

void Shader::unUseProgram()
{
	gl::useProgram(0u);
}

const VariableNames& Shader::getVertexElementNames()
{
    return mVertexElementNames;
}

const UniformNames& Shader::getUniformNames()
{
	return mUniformNames;
}

VariableNames Shader::getDefaultAttribNames()
{
	VariableNames result;
    result[Position] = "attrPosition";
    result[Color] = "attrColor";
    result[TexCoord] = "attrTexCoord";
    return result;
}

UniformNames Shader::getDefaultUniformNames()
{
	UniformNames result;
	result[UniformUsage::Projection] = UniformElement(UniformType::Mat4, "unifProjection");
	result[UniformUsage::Model] = UniformElement(UniformType::Mat4, "unifModel");
	result[UniformUsage::Layer] = UniformElement(UniformType::Float, "unifLayer");
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

void Shader::setUniform(UniformUsage usage, mat4 value)
{
	gl::setUniform(mUniformNames[usage].getLocation(), value);
}

void Shader::setUniform(UniformUsage usage, float value)
{
	float shaderValue = value;
	gl::setUniform(mUniformNames[usage].getLocation(), shaderValue);
}

void Shader::setUniform(UniformUsage usage, uint value)
{
	float shaderValue = static_cast<float>(value);
	gl::setUniform(mUniformNames[usage].getLocation(), shaderValue);
}

void Shader::setUniform(string name, bool value)
{
    GLuint location = glGetUniformLocation(mProgramId, name.c_str());
    if (location < 0)
    {
        Log("ERROR", "Shader uniform %s not found!", name.c_str());
    }
    float shaderValue;
    value ? shaderValue = 1.0f : shaderValue = 0.0f;
    gl::setUniform(location, shaderValue);
}
