#pragma once
#ifdef OS_WINDOWS
extern "C"
{
	__declspec(dllimport) int __stdcall doubleValue(int value);
	__declspec(dllimport) int __stdcall combineNumbers(int value1, int value2);
	__declspec(dllimport) void __cdecl Add(int value);
	__declspec(dllimport) void __cdecl MakeGame();
	__declspec(dllimport) void __cdecl Update();
	__declspec(dllimport) int __stdcall Pointer(void *data);
}
#endif