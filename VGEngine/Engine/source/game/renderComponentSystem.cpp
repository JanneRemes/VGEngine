#include "engine/game/renderComponentSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/transformComponent.h"
#include <vector>
#include <typeinfo>
using namespace vg;
RenderComponentSystem::RenderComponentSystem() :ComponentSystem()
{

}


RenderComponentSystem::~RenderComponentSystem()
{

}
void RenderComponentSystem::update(GameObject* gameObject)
{
	RenderComponent* component = nullptr;
	std::vector<Component*> components = gameObject->getAllComponents();
	for (int i = 0; i < components.size(); i++)
	{
		//component = dynamic_cast<RenderComponent*>(components[i]);
		if (typeid((RenderComponent*)components[i]) == typeid(RenderComponent*))
		{
			component = static_cast<RenderComponent*>(components[i]);
			break;
		}
	}

	//TriangleComponent* component = gameObject->GetComponent<TriangleComponent>();
	TransformComponent* transformComponent = gameObject->GetComponent<TransformComponent>();
	if (component != nullptr)
	{
		VertexBuffer vBuffer(*component->getVertices());
		IndexBuffer iBuffer(*component->getIndices());
		Shader *test = Game::getInstance()->getGraphics()->getShader();

		if (transformComponent == nullptr)
			GraphicsDevice::draw(test, &vBuffer, &iBuffer);
		else
		{
			GraphicsDevice::draw(test, &vBuffer, &iBuffer, transformComponent->mPosition.getX(), transformComponent->mPosition.getY(), transformComponent->getRotation());
		}
	}
}