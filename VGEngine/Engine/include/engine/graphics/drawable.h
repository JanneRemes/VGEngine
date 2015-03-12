
#pragma once

#include <vector>

namespace vg
{
	class Drawable
	{
	public:
		virtual void draw(std::vector<float>& vertices) const = 0;
		const Texture* getTexture() const;
	};
}
