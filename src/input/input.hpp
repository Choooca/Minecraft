#pragma once

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <functional>
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

	std::map<int, bool> keys;
	void RegisterCallback(int index, std::function<void()>);

private:
	Input();
	void Init();
	void CalculateDeltaTime();

	static Input *instance;
	float delta_time, last_time, current_time;

	std::map<int, std::vector<std::function<void()>>> callbacks;

	SDL_Event event;

	void EmitCallback(int index);

	bool quit;
};
