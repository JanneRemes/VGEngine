#pragma once
#include "engine/game/component.h"
#include <vector>
#include "GLES2/gl2.h"
#include "engine/graphics/texture.h"
using namespace std;
namespace vg
{
	class RenderComponent :
		public Component
	{
		friend class Factory;
	public:
		RenderComponent(std::vector<float> vertices,std::vector<GLuint> indices);
		~RenderComponent() = default;
		std::vector<float> *getVertices(){ return &vertices; };
		std::vector<GLuint> *getIndices(){ return &indices; };
		Texture *getTexture();
	private:
		Texture *mTexture;
		void setTexture(Texture *texture);
		std::vector<float> vertices;
		std::vector<GLuint> indices;
	};
}