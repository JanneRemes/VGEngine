/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// Call a dummy function to make sure main isn't stripped.
extern void test_dummy();

// Define a dummy function that the external dummy can call
#include "engine/engine.h"


//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/log.h>

#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphics.h"
#include "engine/utility/logger.h"
#include "engine/game.h"
#include "engine/input/input.h"
#include "engine/assets/fileManager.h"
#include "engine/input/input.h"
#include "engine/graphics/opengl.h"

using namespace vg;
using namespace vg::Input;
using namespace vg::graphics;
extern void mainGame(Game* game);

void main_dummy()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "main_dummy()");
}

static void  drawFrame(struct Engine* engine);
static int32_t handleInput(struct android_app* app, AInputEvent* event);
static void handleCommand(struct android_app* app, int32_t cmd);


/**
* Our saved state data.
*/
struct SavedState
{
    Game* game;
};

/**
* Shared state for our app.
*/
struct Engine
{
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;
    int animating;
    Graphics graphics;

    struct SavedState state;
};


/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app* state)
{
    struct Engine engine;
    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = handleCommand;
    state->onInputEvent = vg::Input::Input::engine_handle_input;
    engine.app = state;
    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
        ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
        engine.app->looper, LOOPER_ID_USER,NULL, NULL);

    if (engine.app->savedState != NULL)
    {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct SavedState*)engine.app->savedState;
    }
    // TEST
    test_dummy();
	char* dooooge = "dddoooge";
	delete dooooge;

    // Make sure app_glue isn't stripped.
    app_dummy();
	Game* game = Game::getInstance();
	game->setFileManager(state);
	game->setGraphics(&engine.graphics);

	engine.state.game = game;
    engine.state.game->start();

    // loop waiting for stuff to do.
    while (engine.state.game->isRunning())
    {
		//Log("fm", "%f %f %f SENSOR", vg::Input::getSensorX(), vg::Input::getSensorY(), vg::Input::getSensorZ());
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
		vg::Input::Input::update();
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
                if (engine.accelerometerSensor != NULL)
                {
					vg::Input::Input::accelerometerEvent(engine.sensorEventQueue);
                }
            }

            // Check if we are exiting.
            if (engine.app->destroyRequested != 0)
            {
				delete Game::getInstance();
                engine.graphics.unInitialize();
				Log("memory", "MemoryCount is: %d", BaseClass::getValue("gameObject"));
                return;
            }
        }

        if (engine.animating)
        {
            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            drawFrame(&engine);
        }


    }

}

/**
* Just the current frame in the display.
*/
void drawFrame(struct Engine* engine)
{
    if (!engine->graphics.isInitialized())
    {
        Log("ERROR", "GraphicsContext is not initialized!", "");
        return;
    }

	gl::clear();
	gl::clearColor(vg::Input::Input::getTouchX() / engine->graphics.getScreenWidth(), engine->state.game->mPulse,
		(vg::Input::Input::getTouchY()) / engine->graphics.getScreenHeight(), 1);
	
	engine->state.game->update();

    engine->graphics.swapBuffers();
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
        // The system has asked us to save our current state.  Do so.
        engine->app->savedState = malloc(sizeof(struct SavedState));
        *((struct SavedState*)engine->app->savedState) = engine->state;
        engine->app->savedStateSize = sizeof(struct SavedState);
        break;

    case APP_CMD_INIT_WINDOW:
        // The window is being shown, get it ready.
        if (engine->app->window != NULL)
        {
            engine->graphics.initialize(engine->app);
            engine->animating = true;
            drawFrame(engine);
			mainGame(engine->state.game);
        }
        break;

    case APP_CMD_TERM_WINDOW:
        // The window is being hidden or closed, clean it up.
        engine->graphics.unInitialize();
        engine->state.game->stop();
        break;

    case APP_CMD_GAINED_FOCUS:
        // When our app gains focus, we start monitoring the accelerometer.
        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
            // We'd like to get 60 events per second (in us).
            ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L / 60) * 1000);
        }
        engine->state.game->getAudioManager()->playAll();
        break;

    case APP_CMD_LOST_FOCUS:
        // When our app loses focus, we stop monitoring the accelerometer.
        // This is to avoid consuming battery while not being used.
        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
        }
        // Also stop animating.
        engine->animating = 0;
        drawFrame(engine);
        engine->state.game->getAudioManager()->pauseAll();
        break;
    }
}