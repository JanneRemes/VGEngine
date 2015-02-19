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

#include "engine\graphics\graphicsContext.h"
#include "engine\utility\logger.h"
#include "engine\game.h"
void main_dummy()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "main_dummy()");
}

/**
 * Our saved state data.
 */



/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {

	vg::Game game(state);
	// TEST
	test_dummy();

	// Make sure app_glue isn't stripped.
	app_dummy();

    // loop waiting for stuff to do.
	while (1)
	{
		game.update();
	}
}

//END_INCLUDE(all)
