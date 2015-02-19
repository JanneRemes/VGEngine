
#include "engine\graphics\shader.h"

using namespace vg;

Shader::Shader(ShaderType type, GLuint programId, std::string fileName)
	: mType(type)
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
