
#include "engine/game/gameObject.h"
#include "engine/game/game.h"
#include "engine/game/renderComponent.h"
#include "engine/game/transformComponent.h"
#include "engine/graphics/texture.h"
#include "engine/utility/logger.h"
#include "engine/game/scene.h"
#include <algorithm>

using namespace vg;
using namespace vg::graphics;
int GameObject::currentId = 0;
GameObject::GameObject(std::string name)
	: BaseClass("gameObject"), mName(name), mMarkedForDelete(false)
{
	mParent = nullptr;
	mId = currentId++;
}

GameObject::~GameObject()
{
	for (auto i = mComponents.begin(); i != mComponents.end(); i++)
	{
		delete (*i).second;
	}
	mComponents.clear();
}

GameObject::GameObject(const GameObject &obj) 
	: BaseClass(obj.mName), mName(obj.mName), mMarkedForDelete(false)
{
	mParent = nullptr;
	for (auto ij = obj.mComponents.begin(); ij != obj.mComponents.end(); ij++)
	{
		if (dynamic_cast<RenderComponent*>(ij->second))
		{
			Game *game = Game::getInstance();
			RenderComponent *comppp = dynamic_cast<RenderComponent*>(ij->second);
			std::string path = comppp->getTexture()->getPath();
			RenderComponent *temp = new RenderComponent(path);
			mComponents.insert(std::make_pair(&typeid(*temp), temp));
		}
		else if (dynamic_cast<TransformComponent*>(ij->second))
		{
			TransformComponent *t = new TransformComponent(*dynamic_cast<TransformComponent*>(ij->second));
			mComponents.insert(std::make_pair(&typeid(*ij->second),t));
		}
	}
}

void GameObject::addComponent(Component* component)
{
	component->setGameObject(this);
	mComponents.insert(std::make_pair(&typeid(*component), component));
}

void GameObject::add(Component* component)
{
	addComponent(component);
}

void GameObject::markForDelete()
{
	mMarkedForDelete = true;
}

bool GameObject::markedForDelete()
{
	return mMarkedForDelete;
}

void GameObject::setParent(GameObject *parent)
{
	mParent = parent;
}
GameObject *GameObject::getParent()
{
	return mParent;
}
int GameObject::getId()
{
	return mId;
}
GameObject *GameObject::getGameObject(int id)
{
	
	auto vector = &Game::getInstance()->getSceneManager()->getActiveScene()->mActivePool;
	for (auto it = vector->begin(); it != vector->end(); it++)
	{
		if ((*it)->mId == id)
			return (*it);
	}
	return nullptr;
}
std::vector<GameObject*> *GameObject::getGameObjects()
{
	auto vector = &Game::getInstance()->getSceneManager()->getActiveScene()->mActivePool;
	return vector;
}