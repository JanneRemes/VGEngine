
#pragma once

#include <vector>

/// @todo Fix comments in this file

namespace vg
{
	class Scene;

	/**
		<description>
	*/
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
	private:
		std::vector<Scene*> mScenes; ///< description
	};
}