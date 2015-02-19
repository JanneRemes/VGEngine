
#pragma once

#include "engine\assets\asset.h"

/// @todo Fix comments in this file

namespace vg
{
    /**
    Reads a glsl file containing shader program source code
    */
    class ShaderSource : public Asset
    {
    public:
        /**
        <description>
        */
        ShaderSource();

        ~ShaderSource();

        /**
        Loads asset and adds it to AssetManager
        @todo get FileManger instance
        @return was loading successful
        */
        bool load();

        /**
        Unloads asset and removes it from AssetManager
        @todo get AssetManager instance
        @return was unloading successful
        */
        bool unLoad();
    private:
    };
}