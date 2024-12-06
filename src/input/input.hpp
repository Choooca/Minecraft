#pragma once

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "../camera/camera.hpp"

class Input
{
public:
	void operator=(const Input &) = delete;

	Input(Input &other) = delete;

	static Input *GetInstance();

	float GetDeltaTime();

	void InputLoop();

	bool ShouldQuit();

private:
	Input();
	void Init();
	void CalculateDeltaTime();
	std::map<int, bool> keys;

	static Input *instance;
	float delta_time, last_time, current_time;

	SDL_Event event;

	bool quit;

	void Test();
};
