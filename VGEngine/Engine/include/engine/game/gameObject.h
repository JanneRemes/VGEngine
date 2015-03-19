
#pragma once

#include <vector>
#include <string>
/// @todo Fix comments in this file

namespace vg
{
	class Component;

	/**
		<description>
	*/
	class GameObject
	{
	public:
		GameObject(std::string name) :mName(name){};
		virtual ~GameObject() = default;
		void setIsPooled(bool isPooled);
		bool getIsPooled();
		std::string getName(){ return mName; }
	private:
		std::vector<Component*> mComponents; ///< description
		bool mIsPooled;//does gameobject return to pooled list (ObjectPool class)
		std::string mName;
	};
}
