#pragma once
#include <android\log.h>

#ifdef DEBUG
#define Log(tag, message, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "File: %s, Line: %d, Method: %s, Message: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#define  Log(tag, message, ...) (void)(0)
#endif