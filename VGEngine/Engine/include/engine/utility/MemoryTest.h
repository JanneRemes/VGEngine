#pragma once
#include <cstdio>
#include <cstdlib>
#include "engine/utility/logger.h"
#include <string>
static std::string fname_delete;
static int line_delete;
static int memorySpaceCount = 0;

void *operator new(size_t, const char *, int);
void *operator new[](size_t, const char *, int);
void operator delete(void *);
void operator delete[](void *);
void deletep(const char *, int);

void *operator new(size_t size, const char *file, int lineno){
	memorySpaceCount++;
	void *pfs = malloc(size);
	if (NULL == pfs)
	{
		//Game::log("no heap to allocate");
	}
	Log("memory", "new object at file: %s and line: %d", file, lineno);
	//Game::log("newed at file ");
	//Game::log(" at line ");
	//hex << pfs << dec << " size " << (int)size << endl;
	return pfs;
}

void *operator new[](size_t size, const char *file, int lineno)
{
	memorySpaceCount++;
	Log("memory", "new object at file: %s and line: %d", file, lineno);
	return operator new(size, file, lineno);
}

void operator delete(void *pfs)
{
	memorySpaceCount--;
	free(pfs); // free pointer
	Log("memory", "deleted object at file: %s and line: %d", fname_delete.c_str(), line_delete);
	//Game::log("deleted at file "+ fname_delete);
	//Game::log(" at line " << lineno_delete << " ");
	//cout << " deleted for " << hex << pfs << dec << endl;
	return;
}

void operator delete[](void *pfs)
{
	operator delete(pfs);
}

void deletep(const char *file, int lineno)
{
	fname_delete = std::string(file);
	line_delete = lineno;
	return;
}
#define new new(__FILE__, __LINE__)
#define delete deletep(__FILE__, __LINE__), delete