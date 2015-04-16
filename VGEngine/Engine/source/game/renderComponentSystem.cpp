#include "engine/game/renderComponentSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
using namespace vg;
RenderComponentSystem::RenderComponentSystem() :ComponentSystem()
{

}


RenderComponentSystem::~RenderComponentSystem()
{

}
void RenderComponentSystem::update(GameObject* gameObject)
{
	TriangleComponent* component = gameObject->GetComponent<TriangleComponent>();
	if (component != nullptr)
	{
		VertexBuffer vBuffer(*component->getVertices());
		IndexBuffer iBuffer(*component->getIndices());
		Shader *test = Game::getInstance()->getGraphics()->getShader();
			GraphicsDevice::draw(test, &vBuffer, &iBuffer);
	}
}