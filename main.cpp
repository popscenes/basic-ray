#include <stdio.h>
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "defs.h"
#include "graphics.h"
#include "vector.h"
#include "ray.h"


bool isGameRunning = false;
int ticksLastFrame;

float screenLeft = -2;
float screenRight = 2;
float screenTop = 2;
float screenBottom = -2;

vector3_t cameraPos = { 0,0,0 };

ray_t rays[BUFFER_WIDTH * BUFFER_HEIGHT];

vector3_t u = { 2,0,0 };
vector3_t v = { 0,2,0 };
vector3_t w = { 0,0,1 };

void setup()
{
	
}


void update()
{
	// Compute how long we have until the reach the target frame time in milliseconds
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	// Only delay execution if we are running too fast
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	// Store the milliseconds of the current frame to be used in the future
	ticksLastFrame = SDL_GetTicks();

	for (int y = 0; y < BUFFER_HEIGHT; y++)
	{
		for (int x = 0; x < BUFFER_WIDTH; x++)
		{
			float currentU = screenLeft + (screenRight - screenLeft) * ((float)x + 0.5) / BUFFER_WIDTH;
			float currentV = screenBottom + (screenTop - screenBottom) * ((float)y + 0.5) / BUFFER_HEIGHT;

			vector3_t direction = (w * -1) + (currentU * u) + (currentV * v);

			ray_t ray = { 0 };
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;
			ray.direction = direction;

			rays[(y * BUFFER_WIDTH) + x] = ray;
		}
	}
}
void render()
{
	clearColourBuffer(0xFF666666);
	renderColourBuffer();
}

void releaseResources()
{
	destroyWindow();
}

int main(int argc, char* args[])
{
	isGameRunning = initialiseWindow();

	setup();

	while (isGameRunning) {
		update();
		render();
	}
	releaseResources();
	return 0;
}