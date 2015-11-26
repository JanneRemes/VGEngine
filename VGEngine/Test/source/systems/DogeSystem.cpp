#include "systems/DogeSystem.h"
#include <string>
#include <engine/game/textComponent.h>
#include <engine/input/mouse.h>
#include <engine/game/transformComponent.h>
#include <engine/utility/logger.h>
#include <engine/utility/string.h>
using namespace vg;
using namespace vg::input;
DogeSystem::DogeSystem()
{
	doges = 0;
}


DogeSystem::~DogeSystem()
{
}
void DogeSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	std::string objectName = "";
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		objectName = (*it)->getName();
		if (objectName == "DogeText")
		{
			(*it)->getComponent<TextComponent>()->setText("doges: " + toStringi(doges));
		}
		if (objectName == "doge")
		{
			TransformComponent *transform = (*it)->getComponent<TransformComponent>();
			float distance = Mouse::getPos(false).distance(transform->getWorldPosition());
			if (distance < (transform->getSize().x / 2) && Mouse::isKeyPressed(MOUSE_KEY::LEFT))
			{
				doges++;
			}
		}
	}

}