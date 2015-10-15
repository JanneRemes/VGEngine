
#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

namespace vg
{
	class Scene;

	/**
	Manages Scenes.
	*/
	class SceneManager
	{
	public:
		/**
		Default constructor
		*/
		SceneManager();
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
		Changes the scene to the scene given for this function and
		cleares previous scenes
		@param scene the scene which you want to show on the screen
		*/
		void changeScene(string key);

		/**
		Adds scene to templatelist where they can be loaded many times.
		Every load creates new instance of scene from this map.
		*/
		void addTemplateScene(string key,Scene *scene);

		Scene* getActiveScene();



	private:
		Scene* mActiveScene;
		map<string, Scene*> mSceneTemplates;	///< Map of different templates that can be used to create new scene
		bool mSceneChanged; ///< Bool that is used for changing scenes.
	};
}
