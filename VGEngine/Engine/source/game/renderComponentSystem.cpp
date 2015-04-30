#include "engine/game/renderComponentSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/transformComponent.h"
#include "engine/graphics/opengl.h"
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
		Shader *shader = Game::getInstance()->getGraphics()->getShader();
		shader->useProgram();
		if (component->getTexture() != nullptr)
		{
			component->getTexture()->bind();
		}
		else
		{
			gl::activeTexture();
			gl::bindTexture(0u);
		}
		
		if (transformComponent == nullptr)
			GraphicsDevice::draw(shader, &vBuffer, &iBuffer);
		else
		{
			shader->setPosition(transformComponent->getPosition() - transformComponent->getOrigin());
            shader->setSize(transformComponent->getSize());
            shader->setRotation(transformComponent->getRotation());
            shader->setLayer(transformComponent->getLayer());
            GraphicsDevice::draw(shader, &vBuffer, &iBuffer);
		}
		shader->unUseProgram();
	}
}