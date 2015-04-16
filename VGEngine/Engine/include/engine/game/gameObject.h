
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
		<description>
	*/
	class GameObject:
		public BaseClass
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject() { };
		std::string getName(){ return mName; }
		void addComponent(Component* component);
		template<typename T>
		T* GetComponent()
		{
			ComponentMap::const_iterator position = mComponents.find(&typeid(T));
			if (position == mComponents.end())
				return nullptr;
			else
				return static_cast<T*>(position->second);
		}
	private:
		using ComponentMap = std::unordered_map<const std::type_info*, Component*>;
		ComponentMap mComponents;
		std::string mName;
	};
}
