
#pragma once

#include <vector>
#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphicsContext.h"
#include <android/sensor.h>
#include "engine/assets/fileManager.h"

#include <unistd.h>

/// @todo Fix comments in this file

namespace vg
{
    /**
    <description>
    */
    class Scene;


    /**
    <description>
    */
    class Game
    {


    public:
        /**
        <description>
        */
        Game();

        /**
        <description>
        */
        virtual ~Game() = default;


        /**
        <description>
        */
        void update();

        /**
        <description>
        */
        void draw(GraphicsContext* graphicsContext);

        /**
        <description>
        */
        void readFiles(FileManager& fileManager);

    private:
        std::vector<Scene*> mScenes;    ///< description
        float mPulse;                   ///< description
    };
}
