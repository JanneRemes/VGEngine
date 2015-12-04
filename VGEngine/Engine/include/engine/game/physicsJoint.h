#pragma once
#include "Box2D/Box2D.h"
#include "engine/game/system.h"
#include "engine/utility/vec2f.h"
#include "engine/game/physicsComponent.h"

namespace vg
{
	class Joint
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

		bool connected;
	private:
		void reCreate();

		b2Body *mBodyA;
		b2Body *mBodyB;

		b2RevoluteJointDef revoluteDef;
		b2RevoluteJoint *revoluteJoint;
	};
}