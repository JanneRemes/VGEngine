
#pragma once

#include <vector>
#include "engine/android_native_app_glue.h"
#include "engine/graphics/graphicsContext.h"
#include <android/sensor.h>
#include "engine/assets/fileManager.h"

#include <unistd.h>






/// @todo Fix comments in this file


namespace vg
{
	class Scene;



	/**
		<description>
	*/
	class Game
	{
		struct saved_state {
			float angle;

		};

		/**
		* Shared state for our app.
		*/
		struct engine {
			struct android_app* app;

			ASensorManager* sensorManager;
			const ASensor* accelerometerSensor;
			ASensorEventQueue* sensorEventQueue;
			int animating;
			vg::GraphicsContext graphicsContext;


			struct saved_state state;
		};

	public:
		Game(android_app *app);
		virtual ~Game() = default;
		void update();
	private:
		std::vector<Scene*> mScenes; ///< description
		static void  engine_draw_frame(struct engine* engine);
		static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);
		static void engine_handle_cmd(struct android_app* app, int32_t cmd);
		struct engine engine;
        FileManager mFileManager;
	};
}