#pragma once
#include "engine\assets\asset.h"

namespace vg
{
    class ShaderSource : public Asset
    {
    public:
        ShaderSource();
        ~ShaderSource();

        bool load();
        bool unLoad();

    private:

    };
}