#if defined(OS_ANDROID)

#include "engine/application.h"
#include "engine/platforms/android/android_native_app_glue.h"
#include "engine/utility/logger.h"
#include "engine/graphics/graphics.h"
#include "engine/utility/logger.h"
#include "engine/game.h"
#include "engine/input/sensor.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/opengl.h"
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/log.h>
#include <android/sensor.h>

using namespace vg;
using namespace vg::core;
using namespace vg::input;
using namespace vg::graphics;
static int32_t handleInput(struct android_app* app, AInputEvent* event);
static void handleCommand(struct android_app* app, int32_t cmd);
void sensorEvent(ASensorEventQueue *queue);
extern void test_dummy();
extern void mainGame(Game* game);
Application *Application::currentApplication = nullptr;
void main_dummy()
{
	__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "main_dummy()");
}

/**
* Shared state for our app.
*/

struct SavedState
{
	Game* game;
};
struct Engine
{
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	const ASensor* gyroscopeSensor;
	ASensorEventQueue* sensorEventQueue;
	int animating;
	Graphics graphics;

	struct SavedState state;
};

Engine engine;
Engine *getEngine()
{
	return &engine;
}
Application::Application()
{

}
void Application::initContext()
{

}
void Application::update()
{
	//Log("fm", "%f %f %f SENSOR", vg::Input::getSensorX(), vg::Input::getSensorY(), vg::Input::getSensorZ());
	// Read all pending events.
	int ident;
	int events;
	struct android_poll_source* source;

	// If not animating, we will block forever waiting for events.
	// If animating, we loop until all events are read, then continue
	// to draw the next frame of animation.
	vg::input::Touch::update();
	while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
	{
		//Log("test", "AccelerationX: %f", vg::Input::Input::getSensorX());
		// Process this event.
		if (source != NULL)
		{
			source->process(engine.app, source);
		}

		// If a sensor has data, process it now. 
		if (ident == LOOPER_ID_USER)
		{
			if (engine.accelerometerSensor != NULL && engine.gyroscopeSensor != NULL)
			{
				sensorEvent(engine.sensorEventQueue);
			}
		}

		// Check if we are exiting.
		if (engine.app->destroyRequested != 0)
		{
			delete Game::getInstance();
			engine.graphics.unInitialize();
			//Log("memory", "MemoryCount is: %d", BaseClass::getValue("gameObject"));
			return;
		}
	}

	if (engine.animating)
	{
		// Drawing is throttled to the screen update rate, so there
		// is no need to do timing here.
		drawFrame();
	}
}
void Application::drawFrame()
{
	if (!engine.graphics.isInitialized())
	{
		Log("vgengine", "GraphicsContext is not initialized!", "");
		return;
	}

	gl::clear();
	gl::clearColor(Screen::getRed(), Screen::getGreen(), Screen::getBlue(), Screen::getAlpha());

	engine.state.game->update();

	engine.graphics.swapBuffers();
}

int32_t engine_handle_input(android_app* app, AInputEvent* event)
{
	//struct engine* engine = (struct engine*)app->userData;


	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		vg::Vector2<float> touchPos = vg::Vector2<float>(
			AMotionEvent_getX(event, 0),
			AMotionEvent_getY(event, 0)
			);
		vg::input::Touch::setPos(touchPos);
		vg::input::Touch::setIsTouched(true);
		//Log("vgengine", "movement %f %f", mTouchX, mTouchY);
		if ((AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_UP)
		{
			//Log("vgengine", "Released touch %d", 5);
			if (vg::input::Touch::getIsTouched())
			{
				vg::input::Touch::setIsTouched(false);
				vg::input::Touch::setIsReleased(true);
			}
		}

		return 1;
	}

	return 0;
}

void sensorEvent(ASensorEventQueue *queue)
{
	ASensorEvent event;
	while (ASensorEventQueue_getEvents(queue, &event, 1) > 0)
	{
		vg::input::Sensor::setSensor(event.acceleration.x, event.acceleration.y, event.acceleration.z);
		vg::input::Sensor::setAngles(event.vector.x, event.vector.y, event.vector.z);
	}
}
void android_main(struct android_app* state)
{
	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = handleCommand;
	state->onInputEvent = engine_handle_input;
	engine.app = state;
	// Prepare to monitor accelerometer
	engine.sensorManager = ASensorManager_getInstance();
	engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
		ASENSOR_TYPE_ACCELEROMETER);
	engine.gyroscopeSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
		ASENSOR_TYPE_GYROSCOPE);
	engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
		engine.app->looper, LOOPER_ID_USER, NULL, NULL);

	if (engine.app->savedState != NULL)
	{
		// We are starting with a previous saved state; restore from it.
		engine.state = *(struct SavedState*)engine.app->savedState;
	}
	// TEST
	test_dummy();


	Game* game = Game::getInstance();
	game->setFileManager();
	game->setGraphics(&engine.graphics);

	engine.state.game = game;
	engine.state.game->start();

	// Make sure app_glue isn't stripped.
	app_dummy();
	Application *app = new Application();
	while (true)
	{
		app->update();
	}
}
/**
* Process the next main command.
*/
void handleCommand(struct android_app* app, int32_t cmd)
{
	struct Engine* engine = (struct Engine*)app->userData;
		switch (cmd)
		{
		case APP_CMD_SAVE_STATE:
			Log("vgengine", "APP_CMD_SAVE_STATE!", "");
			// The system has asked us to save our current state.  Do so.
			//  engine->app->savedState = malloc(sizeof(struct SavedState));
			//  *((struct SavedState*)engine->app->savedState) = engine->state;
			//  engine->app->savedStateSize = sizeof(struct SavedState);
			break;

		case APP_CMD_INIT_WINDOW:
			Log("vgengine", "APP_CMD_INIT_WINDOW!", "");
			// The window is being shown, get it ready.
			if (engine->app->window != NULL)
			{
				engine->graphics.initialize();
				engine->animating = true;
				engine->state.game->initSceneManager();
				engine->state.game->setFileManager();
				mainGame(engine->state.game);
				Application::getInstance()->drawFrame();
			}
			break;

		case APP_CMD_TERM_WINDOW:
			Log("vgengine", "APP_CMD_TERM_WINDOW!", "");
			// The window is being hidden or closed, clean it up.

			engine->state.game->getAudioManager()->pauseAll();
			break;

		case APP_CMD_GAINED_FOCUS:
			Log("vgengine", "APP_CMD_GAINED_FOCUS!", "");
			// When our app gains focus, we start monitoring accelerometer and gyroscope.
			if (engine->accelerometerSensor != NULL)
			{
				ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
				//Accelerometer refresh rate to 60/sec
				ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L / 60) * 1000);
			}

			if (engine->gyroscopeSensor != NULL)
			{
				ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->gyroscopeSensor);
				//Gyroscope refresh rate to 60/sec
				ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->gyroscopeSensor, (1000L / 60) * 1000);
			}
			engine->state.game->getAudioManager()->playAll();
			engine->state.game->start();
			break;

		case APP_CMD_LOST_FOCUS:
			Log("vgengine", "APP_CMD_LOST_FOCUS!", "");
			// When our app loses focus, we stop monitoring accelerometer and gyroscope.
			// This is to avoid consuming battery while not being used.
			engine->state.game->getAudioManager()->pauseAll();
			if (engine->accelerometerSensor != NULL)
			{
				ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
			}

			if (engine->gyroscopeSensor != NULL)
			{
				ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->gyroscopeSensor);
			}
			engine->state.game->stop();
			engine->graphics.unInitialize();

			// Also stop animating.
			engine->animating = 0;
			break;

		case  APP_CMD_START:
			Log("vgengine", "APP_CMD_START!", "");
			break;

		case APP_CMD_RESUME:
			Log("vgengine", "APP_CMD_RESUME!", "");
			break;

		case APP_CMD_PAUSE:
			Log("vgengine", "APP_CMD_PAUSE!", "");
			break;

		case APP_CMD_STOP:
			Log("vgengine", "APP_CMD_STOP!", "");
			break;

		case APP_CMD_INPUT_CHANGED:
			Log("vgengine", "APP_CMD_INPUT_CHANGED!", "");
			break;

		case  APP_CMD_DESTROY:
			Log("vgengine", "APP_CMD_DESTROY!", "");
			break;

		default:
			Log("vgengine", "Unknown APP_CMD = %d !", cmd);

		}
}
void *Application::getEngine()
{
	return engine.app;
}

#endif