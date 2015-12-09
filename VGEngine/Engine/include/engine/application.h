
#pragma once

#include <string>

namespace vg
{
	namespace core
	{
		/**
		Contains and updates other classes
		*/
		class Application
		{
		public:
			
			Application();
			~Application() = default;
			
			/**
			Draws a frame
			*/
			void drawFrame();
			
			//void initContext();
			//void mmessageCheck();

			/**
			Updates everything
			*/
			void update();

			/**
			Creates a new singleton instance if one doesn't exist already
			@return pointer to application instance
			*/
			static Application *getInstance()
			{
				if (currentApplication == nullptr)
				{
					return new Application();
				}
				return currentApplication;
			}

			/**
			Don't call on Windows!
			@return android_app pointer on Android
			*/
			void *getEngine();

		private:
			static Application *currentApplication;	///< singleton instance
		};
	}
}