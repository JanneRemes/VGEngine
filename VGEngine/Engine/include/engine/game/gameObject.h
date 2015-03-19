
#pragma once

#include <vector>

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
		GameObject() = default;
		virtual ~GameObject() = default;
		void setIsPooled(bool isPooled);
		bool getIsPooled();
	private:
		std::vector<Component*> mComponents; ///< description
		bool mIsPooled;//does gameobject return to pooled list (ObjectPool class)
	};
}
