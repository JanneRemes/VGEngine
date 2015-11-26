#include "DllTest.h"

#ifdef OS_WINDOWS
#include <stdio.h>
#include <iostream>
extern "C" __declspec(dllexport) int __stdcall doubleValue(int value)
{
	std::cout << value * 2 << std::endl;
	return value * 2;
}

extern "C" __declspec(dllexport) int __stdcall combineNumbers(int value1, int value2)
{
	return value1 + value2;
}
extern "C" __declspec(dllexport) void __cdecl Add(int value)
{
	std::cout << value*value << std::endl;
}
#endif