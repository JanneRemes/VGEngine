#pragma once
#ifdef OS_WINDOWS
extern "C"
{
	__declspec(dllimport) int __stdcall doubleValue(int value);
	__declspec(dllimport) int __stdcall combineNumbers(int value1, int value2);
	__declspec(dllimport) void __cdecl Add(int value);
}
#endif