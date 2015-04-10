#include "engine/game/component.h"
#include <vector>
#include "GLES2/gl2.h"
namespace vg
{
	class RenderComponent :
		public Component
	{
	public:
		RenderComponent(std::vector<GLfloat> vertices,std::vector<GLuint> indices);
		virtual ~RenderComponent();
	private:
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
	};
}