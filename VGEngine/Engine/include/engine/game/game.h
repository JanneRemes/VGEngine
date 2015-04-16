
#pragma once

#include "engine/game/SceneManager.h"
#include "engine/graphics/graphics.h"
#include "engine/assets/fileManager.h"
#include "engine/game/componentSystem.h"
#include "engine/graphics/shader.h"

#include "engine/android_native_app_glue.h"
#include <android/sensor.h>

#include <vector>
#include <unistd.h>
#include <string>

/// @todo Fix comments in this file
namespace vg
{
    /// @todo remove when not needed anymore
    class Scene;
    class SceneManager;



    /**
    <description>
    */
    class Game
    {


    public:

		static Game* mGame;
		static Game* getInstance();

        /**
        <description>
        */
    

        /**
        <description>
        */
        ~Game() = default;


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
		Graphics* getGraphics();
		void setGraphics(Graphics *graphics);
    private:
		Game();
		Graphics *mGraphics;
        bool mIsRunning;     ///< description
		SceneManager *mSceneManager;   ///< Manages and stores game's scenes
		Shader mShader;
    };
}
