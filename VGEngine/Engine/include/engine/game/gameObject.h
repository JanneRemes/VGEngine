
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <typeinfo>
#include "engine\game\baseClass.h"
/// @todo Fix comments in this file

namespace vg
{
	class Component;

	/**
		Manages an Object in the game
	*/
	class GameObject:
		public BaseClass
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject() { };

		/**
		@return Returns gameObjects name
		*/
		std::string getName(){ return mName; }

		/**
		Adds a component to the gameObject
		@param component Component we want to add for the gameObject
		*/
		void addComponent(Component* component);
		template<typename T>

		/**
		@return Returns component from the gameObject
		*/
		T* GetComponent()
		{
			ComponentMap::const_iterator position = mComponents.find(&typeid(T));
			if (position == mComponents.end())
				return nullptr;
			else
				return static_cast<T*>(position->second);
		}

		/**
		@return Returns all components from the gameObject
		*/
		std::unordered_map<const std::type_info*, Component*> *getAllComponents()
		{
			//std::vector<Component*> tempVector;
			///for (ComponentMap::iterator it = mComponents.begin(); it != mComponents.end(); it++)
			//{
			//	tempVector.push_back((*it).second);
			//}
			return &mComponents;//&tempVector;
		}
	private:
		using ComponentMap = std::unordered_map<const std::type_info*, Component*>; 
		ComponentMap mComponents; ///<  ComponentMap used by the gameObject
		std::string mName; ///< Name of the gameObject
	};
}
