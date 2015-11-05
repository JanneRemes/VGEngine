
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"

#include <string>

const std::string FOLDER = "shaders/"; ///< subfolder for shader sources

using namespace vg::core;
using namespace vg::graphics;
using namespace std;
using namespace glm;

Shader::Shader(const VariableNames& attributeNames, const std::vector<std::string>& uniformNames)
	: mVertexElementNames(attributeNames), mUniformNames(uniformNames)
{
    mInitialized = false;
}

Shader::~Shader()
{
	gl::useProgram(0u);
}

void Shader::initialize()
{
    mProgramId = gl::createProgram();
    mVertexId = gl::createVertexShader();
    mFragmentId = gl::createFragmentShader();

    for (auto& pair : mVertexElementNames)
    {
        gl::bindAttribLocation(mProgramId, pair.first, pair.second.c_str());
    }

    mInitialized = true;
}

bool Shader::isInitialized()
{
    return mInitialized;
}

bool Shader::load(vg::core::FileManager& fileManager, const std::string& vertexPath, const std::string& fragmentPath)
{
    if (!mInitialized)
        initialize();

    // compile shaders
    std::string buffer;
    fileManager.readAsset(FOLDER + vertexPath, buffer);
    if (!compileShaderSource(mVertexId, buffer))
    {
        Log("vgengine", "Vertex shader compile error!", "");
        printErrorLog(mVertexId);
        return false;
    }

    fileManager.readAsset(FOLDER + fragmentPath, buffer);
	if (!compileShaderSource(mFragmentId, buffer))
    {
        Log("vgengine", "Fragment shader compile error!", "");
        printErrorLog(mFragmentId);
        return false;
    }

    // link program
    gl::attachShader(mProgramId, mVertexId);
	gl::attachShader(mProgramId, mFragmentId);
    gl::linkProgram(mProgramId);
    
	if (!gl::linkStatus(mProgramId))
    {
        Log("vgengine", "Shader program link error!", "");
        return false;
    }
    
	//uniforms
    gl::useProgram(mProgramId);
	for (int i = 0; i < mUniformNames.size(); i++)
		mUniformLocations.insert(make_pair<string&, unsigned int>(mUniformNames[i], 0));
	for (auto& pair : mUniformLocations)
	{
		unsigned int location = gl::getUniformLocation(mProgramId, pair.first);
        if (location < 0)
        {
            Log("vgengine", "Shader uniform %s not found!", pair.first.c_str());
        }
		pair.second = location;
	}
    gl::useProgram(0u);

    return true;
}

unsigned int Shader::getProgramId()
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

const std::vector<std::string>& Shader::getUniformNames()
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

vector<string> Shader::getDefaultUniformNames()
{
	return vector<string>
	{
		"unifProjection",
		"unifModel",
		"unifLayer",
		"unifNoTexture",
		"unifFontTexture"
	};
};

bool Shader::compileShaderSource(unsigned int id, const std::string& source)
{
    const char* temp = source.c_str();
    gl::shaderSource(id, 1, &temp, NULL);
    gl::compileShader(id);
	return gl::getShaderivCompileStatus(id);
}

void Shader::printErrorLog(unsigned int shader)
{
    int bufferLenght;
    gl::getShaderivInfoLog(shader, &bufferLenght);
    vector<char> buffer(bufferLenght);
    gl::getShaderInfoLog(shader, buffer.size(), nullptr, buffer.data());
    Log("vgengine", "%s", buffer.data());
}

void Shader::setUniform(string name, glm::mat3 value)
{
	gl::setUniform(mUniformLocations[name], value);
}

void Shader::setUniform(string name, mat4 value)
{
	gl::setUniform(mUniformLocations[name], value);
}

void Shader::setUniform(string name, float value)
{
	gl::setUniform(mUniformLocations[name], &value);
}

void Shader::setUniform(string name, bool value)
{
    float shaderValue;
    value ? shaderValue = 1.0f : shaderValue = 0.0f;
	gl::setUniform(mUniformLocations[name], &shaderValue);
}

void Shader::setUniform(string name, float x ,float y)
{
	glm::vec2 shaderValue(x, y);
	gl::setUniform(mUniformLocations[name], shaderValue);
}

void Shader::setUniform(std::string name, float x, float y, float z)
{
	glm::vec3 shaderValue(x, y, z);
	gl::setUniform(mUniformLocations[name], shaderValue);
}

void Shader::setUniform(std::string name, float x, float y, float z, float w)
{
	glm::vec4 shaderValue(x, y, z, w);
	gl::setUniform(mUniformLocations[name], shaderValue);
}
const std::string Shader::getDefaultVertexPath()
{
#ifdef OS_WINDOWS
	return "win_vertex.glsl";
#else
	return "android_vertex.glsl";
#endif
}
const std::string Shader::getDefaultFragmentPath()
{
#ifdef OS_WINDOWS
	return "win_fragment.glsl";
#else
	return "android_fragment.glsl";
#endif
}