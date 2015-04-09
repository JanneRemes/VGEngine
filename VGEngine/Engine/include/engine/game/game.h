
#pragma once

#include <vector>
#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphics.h"
#include <android/sensor.h>
#include "engine/assets/fileManager.h"
#include "engine/game/SceneManager.h"
#include <unistd.h>
#include "engine/game/componentSystem.h"
#include <string>

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
		Returns pointer to scene manager
		*/
		
		SceneManager* getSceneManager();
		float mPulse;
		void addComponentSystem(Scene *scene,ComponentSystem *componentSystem);
		static void log(char* text);
    private:
        bool mIsRunning;     ///< description
		SceneManager *mSceneManager;   ///< Manages and stores game's scenes
    };
}
