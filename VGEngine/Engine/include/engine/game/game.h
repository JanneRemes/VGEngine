
#pragma once

#include <vector>
#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphics.h"
#include <android/sensor.h>
#include "engine/assets/fileManager.h"

#include <unistd.h>

/// @todo Fix comments in this file

namespace vg
{
    /**
    <description>
    */
    class SceneManager;


    /**
    <description>
    */
    class Game
    {


    public:
        /**
        <description>
        */
        Game(Graphics* graphics);

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
        void draw(Graphics* graphics);

        /**
        <description>
        */
        void readFiles(FileManager& fileManager);

        /**
        <description>
        */
        bool isRunning();

        /**
        <description>
        */
        void stop();

        /**
        <description>
        */
        void start();


    private:
		SceneManager mSceneManager();   ///< description
        float mPulse;                   ///< description
        bool mIsRunning;                ///< description

        DebugSprite testSprite;         ///< description
    };
}
