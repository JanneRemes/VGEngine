
#pragma once

#include <engine/engine.h>
#include <android\log.h>

class Test
{
public:
	bool doesItWork()
	{
		main_dummy();

		__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "Test::doesItWork()");

		return true;
	}
private:
};
