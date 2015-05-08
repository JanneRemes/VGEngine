
#include "engine/game.h"
#include <algorithm>
#include "engine/game/game.h"
#include "engine/game/renderComponent.h"
#include "engine/utility/misc.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/triangleComponent.h"
#include "engine/graphics/texture.h"
#include "engine/game/transformComponent.h"
using namespace vg;
using namespace vg::graphics;
void GameObject::addComponent(Component* component)
{
	mComponents.insert(std::make_pair(&typeid(*component), component));
}

GameObject::GameObject(std::string name):BaseClass("gameObject"),mName(name)
{
	
}
GameObject::GameObject(const GameObject &obj) : BaseClass(obj.mName), mName(obj.mName)
{
	for (auto ij = obj.mComponents.begin(); ij != obj.mComponents.end(); ij++)
	{
		
		if (dynamic_cast<RenderComponent*>(ij->second))
		{
			if (dynamic_cast<QuadrangleComponent*>(ij->second))
			{
				Game *game = Game::getInstance();
				QuadrangleComponent *comppp = dynamic_cast<QuadrangleComponent*>(ij->second);
				std::string path = comppp->getTexture()->getPath();
				QuadrangleComponent *temp = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>(path);
				mComponents.insert(std::make_pair(&typeid(*temp), temp));
			}
			else if (typeid((TriangleComponent*)ij->second) == typeid(TriangleComponent))
			{
				TriangleComponent *temp = Game::getInstance()->getFactory()->createRenderComponent<TriangleComponent>(dynamic_cast<TriangleComponent*>(ij->second)->getTexture()->getPath());
				mComponents.insert(std::make_pair(&typeid(*temp), temp));
			}
			else
			{
				Log("error", "error!!!!", "");
			}
		
		}
		else if (dynamic_cast<TransformComponent*>(ij->second))
		{
			TransformComponent *t = new TransformComponent(*dynamic_cast<TransformComponent*>(ij->second));
			mComponents.insert(std::make_pair(&typeid(*ij->second),t));
		}
	}

	//Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("koalapanos.png")
}