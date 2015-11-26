#include "systems/DogeSystem.h"
#include <string>
#include <engine/game/textComponent.h>
#ifdef OS_WINDOWS
#include <engine/input/mouse.h>
#else
#include <engine/input/touch.h>
#endif
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
			float distance = getInputPos().distance(transform->getWorldPosition());
			if (distance < (transform->getSize().x / 2) && isInputDown())
			{
				doges++;
			}
		}
	}

}

bool DogeSystem::isInputDown()
{
	#ifdef OS_WINDOWS
	return Mouse::isKeyPressed(MOUSE_KEY::LEFT);
	#else
	return Touch::getIsReleased();
	#endif
}
vg::Vec2f DogeSystem::getInputPos()
{
#ifdef OS_WINDOWS
	return Mouse::getPos(false);
#else
	return Touch::getPos(false);
#endif
}