#pragma once
#include "engine\game\scene.h"
#include <vector>
#include <map>
#include <string>
#include "engine/game/game.h"
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
		SceneManager(Game *game);
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
		and doesn't remove previous scenes
		@param scene the scene which you want to show on the screen
		*/
		void openScene(Scene *scene);

		/**
		Changes the scene to the scene given for this function and
		cleares previous scenes
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

		/**
		Adds scene to templatelist where they can be loaded many times.
		Every load creates new instance of scene from this map.
		*/
		void addTemplateScene(string key,Scene *scene);

	private:
		Game *mGame;
		vector<Scene*> mCurrentScenes; ///< Vector that includes all the scenes that we are currently using
		map<string, Scene*> mSceneTemplates;	///< Map of different templates that can be used to create new scene
		bool mSceneChanged; ///< Bool that is used for changing scenes.
	};
}
