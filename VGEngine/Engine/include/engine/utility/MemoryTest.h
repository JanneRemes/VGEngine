#pragma once
#include <cstdio>
#include <cstdlib>
#include "engine/game/game.h"
int memorySpaceCount = 0;
	void* operator new(size_t sz){
		memorySpaceCount++;
		vg::Game::log("Creating new object!");
		void* m = malloc(sz);
		return m;
	}

		void operator delete(void* m) {
		memorySpaceCount--;
		vg::Game::log("deleting object!");
		free(m);
	}
