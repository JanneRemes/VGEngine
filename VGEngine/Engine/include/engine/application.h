
#pragma once

#include <string>

namespace vg
{
	namespace core
	{
		class Application
		{
		public:
			
			Application();
			~Application() = default;
			void initContext();
			void update();
			void drawFrame();
			void mmessageCheck();
			static Application *getInstance()
			{
				if (currentApplication == nullptr)
				{
					return new Application();
				}
				return currentApplication;
			}
		private:
			static Application *currentApplication;
		};
	}
}