#pragma once
#include "engine\game\scene.h"
#include <vector>
using namespace std;
namespace vg
{
	/**
	<description>
	*/
	class sceneManager
	{
	public:
		sceneManager();
		~sceneManager();

		void draw();

		/**
		<description>
		@param dt <description>
		@return <description>
		*/
		void update(float dt);

		/**
		<description>
		@param scene <description>
		@return <description>
		*/
		void openScene(Scene *scene);

		/**
		<description>
		@param scene <description>
		@return <description>
		*/

		void changeScene(Scene *scene);

		/**
		<description>
		@param scene <description>
		@return <description>
		*/
		void emptyScenes();
		void closeCurrentScene();

	private:
		vector<Scene*> currentScenes;
		bool sceneChanged = false;
	};
}
