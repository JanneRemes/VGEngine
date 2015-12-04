#pragma once
#ifdef OS_WINDOWS
#include <string>
enum command
{
	CREATEGAMEOBJECT,
	GETIDGAMEOBJECT,
	GETNAMEGAMEOBJECT,
	GETNAMESGAMEOBJECTS,
	NONE
};
extern "C"
{
	__declspec(dllimport) int __stdcall doubleValue(int value);
	__declspec(dllimport) int __stdcall combineNumbers(int value1, int value2);
	__declspec(dllimport) void __cdecl Add(int value);
	__declspec(dllimport) void __cdecl MakeGame(void *data);
	__declspec(dllimport) void __cdecl Update();
	__declspec(dllimport) int __stdcall Pointer(void *data);
	__declspec(dllimport) int __stdcall SendCommand(const char *data,char* returnData,int returnDataSize);
	
}

command getCommand(std::string command, std::string &returnData);
bool doesEqual(std::string original, std::string compareTo, std::string &returnData);
#endif