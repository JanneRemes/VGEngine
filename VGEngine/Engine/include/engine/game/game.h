
#pragma once

#include <vector>

namespace vg
{
	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
	private:
		std::vector<Scene*> mScenes;
	};
}