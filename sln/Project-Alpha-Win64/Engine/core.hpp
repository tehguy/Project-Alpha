#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "gfx.hpp"

class ENGINE_API Core {
public:
	int init();

private:
	void gameLoop();

	void handleInput(int key);

	void draw();

	Graphics gfx;
};