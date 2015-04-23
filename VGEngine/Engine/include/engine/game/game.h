
#pragma once

#include "engine/game/SceneManager.h"
#include "engine/graphics/graphics.h"
#include "engine/assets/fileManager.h"
#include "engine/game/componentSystem.h"
#include "engine/graphics/shader.h"
#include "engine/game/factory.h"

#include "engine/android_native_app_glue.h"
#include <android/sensor.h>

#include <vector>
#include <unistd.h>
#include <string>

namespace vg
{
    /// @todo remove when not needed anymore
    class Scene;
    class SceneManager;

    /**
    Class used for updating and pausing/starting the game
    */
    class Game
    {


    public:

		static Game* mGame;
		static Game* getInstance();

		~Game();

        /**
        Updates the games sceneManager
        */
        void update();


        /**
        <description>
        */
        void readFiles(FileManager& fileManager);

        /**
        @return Returns whether the game is running or not
        */
        bool isRunning();

        /**
        Pauses the game
        */
        void stop();

        /**
        Starts the game if its paused
        */
        void start();

		/**
		@return Returns pointer to scene manager
		*/		
		SceneManager* getSceneManager();

		/**
		Adds componentSystem to the scene 
		@param scene Scene that we are giving our componentSystem to
		@param componentSystem ComponentSystem that we are giving to the scene
		*/
		void addComponentSystem(Scene *scene, ComponentSystem *componentSystem);

		/**
		Logger reworked in game for debugging purposes
		@param text Text to log out 
		*/
		static void log(char* text);

		/**
		@return returns the games graphics
		*/
		Graphics* getGraphics();

		/**
		Sets the graphics for the game
		@param graphics Graphics class that includes everything needed for drawing
		*/
		void setGraphics(Graphics *graphics);
		Factory *getFactory();

		float mPulse;
    private:
		Game();
		Factory *mFactory;
		Graphics *mGraphics;
        bool mIsRunning;				///< Boolean used for pausing and starting the game
		SceneManager *mSceneManager;    ///< Manages and stores game's scenes
		Shader mShader;
    };
}
