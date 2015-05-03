
#include "engine/graphics/shader.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"
#include "engine/game/game.h"

using namespace std;
using namespace vg::graphics;
using namespace glm;

const std::string FOLDER = "shaders/"; ///< subfolder for shader sources

Shader::Shader(const VariableNameMap& attributeNames, const VariableNameMap& uniformNames) 
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
	mProjectionLocation = glGetUniformLocation(mProgramId, mUniformNames[Projection].c_str());
	if (mProjectionLocation < 0)
		Log("ERROR", "Shader uniform %s not found!", &mUniformNames[Projection]);

	mModelLocation = glGetUniformLocation(mProgramId, mUniformNames[Model].c_str());
	if (mModelLocation < 0)
		Log("ERROR", "Shader uniform %s not found!", &mUniformNames[Model]);

	mLayerLocation = glGetUniformLocation(mProgramId, mUniformNames[Layer].c_str());
	if (mLayerLocation < 0)
		Log("ERROR", "Shader uniform %s not found!", &mUniformNames[Layer]);
	
    resetUniforms();
    updateUniforms();
	updateProjectionTransform();
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

const VariableNameMap& Shader::getVertexElementNames()
{
    return mVertexElementNames;
}

VariableNameMap Shader::getDefaultAttribNames()
{
	VariableNameMap result;
    result[Position] = "attrPosition";
    result[Color] = "attrColor";
    result[TexCoord] = "attrTexCoord";
    return result;
}

VariableNameMap Shader::getDefaultUniformNames()
{
	VariableNameMap result;
	result[Projection] = "unifProjection";
	result[Model] = "unifModel";
	result[Layer] = "unifLayer";
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
    setPosition(Vector2<int>(0,0));
	setSize(Vector2<int>(1, 1));
    setRotation(0);
    setLayer(0);
}

void Shader::setPosition(Vector2<int> position)
{
	mPosition = vec2(position.getX(), position.getY());
}

void Shader::setSize(Vector2<int> size)
{
	mSize = vec2(size.getX(), size.getY());
}

void Shader::setRotation(float degrees)
{
    mRotation = degrees;
}

void Shader::setLayer(uint layer)
{
    mLayer = layer * 0.0001f;
}

void Shader::updateUniforms()
{
	mat4 modelTransform = mat4();
	modelTransform = translate(modelTransform, vec3(mPosition, 0.0f));
	modelTransform = translate(modelTransform, vec3(0.5f * mSize.x, 0.5f * mSize.y, 0.0f));
	modelTransform = rotate(modelTransform, mRotation, vec3(0.0f, 0.0f, 1.0f));
	modelTransform = translate(modelTransform, vec3(-0.5f * mSize.x, -0.5f * mSize.y, 0.0f));
	modelTransform = scale(modelTransform, vec3(mSize, 1.0f));
	
	gl::setUniform(mModelLocation, modelTransform);
	gl::setUniform(mLayerLocation, mLayer);
}

void Shader::updateProjectionTransform()
{
	vec2 screenSize(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());

	mat4 projectionTransform = ortho(0.0f, screenSize.x, screenSize.y, 0.0f, -1.0f, 1.0f);
	gl::setUniform(mProjectionLocation, projectionTransform);
}
