#include "engine\graphics\shader.h"
using namespace vg;

Shader::Shader(ShaderType type, GLuint programId, std::string fileName)
{
    mType = type;
    mProgramId = programId;
}


Shader::~Shader()
{

}
