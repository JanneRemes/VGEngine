#include "TestComponent.h"
#include <engine/game/game.h>
TestComponent::TestComponent() :vg::Component()
{
}


TestComponent::~TestComponent()
{
}
void TestComponent::update()
{
	vg::Game::log("UPDATING COMPONENTSYSTEM");
}
