
#pragma once

#include "engine\assets\asset.h"

#include <GLES2\gl2.h>
#include <string>

/// @todo Fix comments in this file

namespace vg
{
    /**
    supported shader types
    */
    enum ShaderType
    {
        vertex,
        fragment
    };

    /**
    Holds shader attribute and  ids and links itself
    @todo add map of shader attribute names and ids
    */
    class Shader: public Asset
    {
    public:
        /**
        <description>
        @param path filepath
        @param type shaders type
        @param programId shader program id used for linking
        */
        Shader(const std::string& path, FileManager* fileManager, ShaderType type, GLuint programId);

        ~Shader();

        /**
        Loads asset and adds it to AssetManager
        @todo get FileManger instance
        @return was loading successful
        */
        bool load(FileManager& fileManager) override; 

        /**
        Unloads asset and removes it from AssetManager
        @todo get AssetManager instance
        @return was unloading successful
        */
        bool unload() override;

        /**
            <description>
            @return shaders own id used for linking
        */
        GLuint getId();

    private:
        ShaderType mType;  ///< shaders type
        GLuint mId;        ///< shaders own id used for linking
        GLuint mProgramId; ///< shader program id used for linking
    };
}