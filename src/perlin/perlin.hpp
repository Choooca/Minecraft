#pragma once

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

typedef struct
{
	float x, y;
} Vector2;

Vector2 randomGradient(int ix, int iy);

float dotGridGradient(int ix, int iy, float x, float y);

float interpolate(float a0, float a1, float w);

float perlin(float x, float y);