#pragma once
#include "engine\game\scene.h"
#include <vector>
using namespace std;
namespace vg
{
	/**
	Manages Scenes.
	*/
	class SceneManager
	{
	public:
		/**
		Default constructor
		*/
		SceneManager(){ mSceneChanged = false; };
		~SceneManager();

		/**
		Draws the current scene
		*/
		void draw();

		/**
		Updates the current scene that isnt paused
		@param dt The elapsed time since the game last updated
		*/
		void update(float dt);

		/**
		Opens a scene, pushes it to the currentScene vector
		@param scene the scene which you want to show on the screen
		*/
		void openScene(Scene *scene);

		/**
		Changes the scene to the scene given for this function
		@param scene the scene which you want to show on the screen
		*/
		void changeScene(Scene *scene);

		/**
		Completely empties the currentScene vector from all scenes
		*/
		void emptyScenes();

		/**
		Closes the scene that is currently playing
		*/
		void closeCurrentScene();

	private:
		vector<Scene*> mCurrentScenes; ///< Vector that includes all the scenes that we are currently using
		bool mSceneChanged; ///< Bool that is used for changing scenes.
	};
}
