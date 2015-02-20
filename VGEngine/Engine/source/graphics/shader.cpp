
#include "engine\graphics\shader.h"
#include "engine\assets\fileManager.h"

using namespace vg;

Shader::Shader(const std::string& path, FileManager* fileManager, ShaderType type, GLuint programId)
    : Asset(path)
	, mType(type)
	, mProgramId(programId)
{
	/// @todo Make use of, or remove 'fileName' parameter
    /// @todo load ShaderSource asset and link shader
}

Shader::~Shader()
{

}


GLuint Shader::getId()
{
    return mId;
}

bool Shader::load(FileManager& fileManager) 
{
	
}


bool Shader::unload() 
{
	
}

