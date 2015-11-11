#pragma once
#include "engine/game/gameObject.h"
#include <vector>
namespace vg
{
	/**
	System-like class for s that is used for updating s
	*/
	class System
	{
		friend class SystemManager;
	public:
		/**
		Priority that determines when this system is updated. Dont use FIRST, LAST or COUNT.
		*/
		enum Priority
		{
			FIRST,
			EARLY,
			NORMAL,
			LATER,
			LAST,
			COUNT
		};
		System();
		~System();

		/**
		Updates the s inside the gameObject
		@param gameObject The gameObject whos components we are updating
		@param deltaTime how many seconds last update took
		*/
		virtual void update(std::vector<GameObject*>* gameObjects, float deltaTime);

		/**
		Fetches system's update priority.
		@return system´s update priority
		*/
		Priority getPriority(){ return mPriority; }
		/**
		You can set priority that will determine when this system is updated. Don´t use FIRST or LAST or COUNT.
		*/
		void setPriority(Priority priority){ mPriority = priority; }
	protected:
		Priority mPriority;
	};

}