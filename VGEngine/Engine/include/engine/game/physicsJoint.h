#pragma once
#include "Box2D/Box2D.h"
#include "engine/game/system.h"
#include "engine/utility/vec2f.h"
#include "engine/game/physicsComponent.h"
#include "engine/game/physicsSystem.h"

namespace vg
{
	class Joint : public System
	{
	public:
		Joint(PhysicsComponent *bodyA, PhysicsComponent *bodyB);
		~Joint();

		void createRevoluteJoint();
		void enableLimits(float lowerLimit, float upperLimit, bool b);
		void enableLimit(bool b);
		void setAnchorA(Vec2f pos);
		void setAnchorB(Vec2f pos);
		void removeJoint();
	private:
		void reCreate();
		vg::PhysicsSystem *system;

		b2Body *mBodyA;
		b2Body *mBodyB;

		b2RevoluteJointDef revoluteDef;
		b2RevoluteJoint *revoluteJoint;
	};
}