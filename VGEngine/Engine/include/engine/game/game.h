
#pragma once

#include <vector>
#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphics.h"
#include <android/sensor.h>
#include "engine/assets/fileManager.h"
#include "engine/game/SceneManager.h"
#include <unistd.h>

/// @todo Fix comments in this file

namespace vg
{
    /**
    <description>
    */



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

		/**
		*/
		SceneManager *mSceneManager;   ///< description

		float mPulse;
    private:
                 ///< description
        bool mIsRunning;                ///< description

        DebugSprite testSprite;         ///< description
    };
}
