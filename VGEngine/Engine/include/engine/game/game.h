
#pragma once

#include "engine/game/SceneManager.h"
#include "engine/graphics/graphics.h"
#include "engine/assets/fileManager.h"
#include "engine/game/system.h"
#include "engine/graphics/shader.h"
#include "engine/game/factory.h"
#include "engine/assets/assetManager.h"
#include "engine\sound\AudioManager.h"

#include <vector>
#include <string>

namespace vg
{
    class Scene;
    class SceneManager;
	class Timer;
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
		Updates deltatime timer that returns deltatime in seconds
        */
        void update();


        /**
        <description>
        */
        //void readFiles(core::FileManager& fileManager);

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
		void addComponentSystem(Scene *scene, System *componentSystem);

		/**
		Logger reworked in game for debugging purposes
		@param text Text to log out 
		*/
		static void log(char* text);

		/**
		@return returns the games graphics
		*/
		vg::graphics::Graphics* getGraphics();

		/**
		Sets the graphics for the game
		@param graphics Graphics class that includes everything needed for drawing
		*/
		void setGraphics(vg::graphics::Graphics *graphics);
		Factory *getFactory();

		core::FileManager *getFileManager();
		sound::AudioManager *getAudioManager();

		void setFileManager();

		core::AssetManager* getAssetManager();
		/**
		Creates Game's scenemanager
		*/
		void initSceneManager();

		/**
		Sets game's state not running (engine will shut down)
		*/
		void setIsRunning(bool value){ mIsRunning = value; }
    private:
		core::FileManager *mFileManager;
		core::AssetManager *mAssetManager;
		Game();
		Factory *mFactory;
		vg::graphics::Graphics *mGraphics;
        bool mIsRunning;				///< Boolean used for pausing and starting the game
		SceneManager *mSceneManager;    ///< Manages and stores game's scenes
		vg::graphics::Shader mShader;
		sound::AudioManager *mAudioManager;
		vg::Timer *deltaTimer;
    };
}
