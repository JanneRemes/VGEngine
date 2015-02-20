
#include "engine/game.h"
#include "engine\utility\logger.h"

using namespace vg;

Game::Game(android_app *app) : mFileManager(app)
{
	engine.app = app;

	Log("-----", "----- -----", "");
	Log("fm", "Begin", "");
	{
		char buffer[1024];
		getcwd(buffer, sizeof(buffer));
		Log("fm", "path = '%s'", buffer);
		const std::string file = "test.txt";

		std::string str;

		str = "Hello World!";
		Log("fm", "Writing...", "");
        Log("fm", "success? %s", mFileManager.writeFile(FileManager::Internal, file, str) ? "true" : "false");
		Log("fm", "line = '%s'", str.c_str());

		str = "";
		Log("fm", "Reading...", "");
        Log("fm", "success? %s", mFileManager.readFile(FileManager::Internal, file, str) ? "true" : "false");
		Log("fm", "line = '%s'", str.c_str());
	}
	Log("fm", "End", "");
	Log("-----", "----- -----", "");

	// Loop through the "test project", to make sure main isn't stripped.


	memset(&engine, 0, sizeof(engine));
	app->userData = &engine;
	app->onAppCmd = engine_handle_cmd;
	app->onInputEvent = engine_handle_input;
	engine.app = app;

	// Prepare to monitor accelerometer
	engine.sensorManager = ASensorManager_getInstance();
	engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
		ASENSOR_TYPE_ACCELEROMETER);
	engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
		app->looper, LOOPER_ID_USER, NULL, NULL);

	if (app->savedState != NULL) {
		// We are starting with a previous saved state; restore from it.
		engine.state = *(struct saved_state*)app->savedState;
	}
}
void Game::update()
{


	// Read all pending events.
	int ident;
	int events;
	struct android_poll_source* source;

	// If not animating, we will block forever waiting for events.
	// If animating, we loop until all events are read, then continue
	// to draw the next frame of animation.
	while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
		(void**)&source)) >= 0) {

		// Process this event.
		if (source != NULL) {
			source->process(engine.app, source);
		}

		// If a sensor has data, process it now.
		if (ident == LOOPER_ID_USER) {
			if (engine.accelerometerSensor != NULL) {
				ASensorEvent event;
				while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
					&event, 1) > 0) {
					/*LOGI("accelerometer: x=%f y=%f z=%f",
					event.acceleration.x, event.acceleration.y,
					event.acceleration.z);*/


				}
			}
		}

		// Check if we are exiting.
		if (engine.app->destroyRequested != 0)
		{
			engine.graphicsContext.destroy();
			return;
		}
	}

	if (engine.animating) {
		// Done with events; draw next animation frame.
		engine.state.angle += .01f;
		if (engine.state.angle > 1) {
			engine.state.angle = 0;
		}

		// Drawing is throttled to the screen update rate, so there
		// is no need to do timing here.
		engine_draw_frame(&engine);
	}
}



/**
* Just the current frame in the display.
*/
void Game::engine_draw_frame(struct engine* engine)
{
	if (!engine->graphicsContext.isInitialized())
	{
		Log("WARNING", "GraphicsContext not initialized", "");
		return;
	}
	else
		Log( "rwarwasad","DRAWING", "");
	// Just fill the screen with a color.
	glClearColor(((float)engine->state.x) / engine->graphicsContext.getWidth(), engine->state.angle,
		((float)engine->state.y) / engine->graphicsContext.getHeight(), 1);
	glClear(GL_COLOR_BUFFER_BIT);

	engine->graphicsContext.swapBuffers();
}


/**
* Process the next input event.
*/
int32_t Game::engine_handle_input(struct android_app* app, AInputEvent* event) {
	struct engine* engine = (struct engine*)app->userData;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);
		return 1;
	}
	return 0;
}

/**
* Process the next main command.
*/
void Game::engine_handle_cmd(struct android_app* app, int32_t cmd) {
	struct engine* engine = (struct engine*)app->userData;
	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		// The system has asked us to save our current state.  Do so.
		engine->app->savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)engine->app->savedState) = engine->state;
		engine->app->savedStateSize = sizeof(struct saved_state);
		break;
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (engine->app->window != NULL)
		{
			engine->graphicsContext.initialize(engine->app->window);
			engine_draw_frame(engine);
		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		engine->graphicsContext.destroy();
		break;
	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_enableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
			// We'd like to get 60 events per second (in us).
			ASensorEventQueue_setEventRate(engine->sensorEventQueue,
				engine->accelerometerSensor, (1000L / 60) * 1000);
		}
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_disableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
		}
		// Also stop animating.
		engine->animating = 0;
		engine_draw_frame(engine);
		break;
	}
}
