#include <stdio.h>
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "defs.h";
#include "graphics.h";
#include "vector.h"
#include "ray.h"


bool isGameRunning = false;
int ticksLastFrame;

int screenLeft = 0;
int screenRight = BUFFER_WIDTH;
int screenTop = BUFFER_HEIGHT;
int screenBottom = 0;
vector3_t cameraPos = { 0,0,0 };



vector3_t u = { 1,0,0 };
vector3_t v = { 0,1,0 };
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
			float currentU = screenLeft + (screenRight - screenLeft) * (x + 0, 5) / BUFFER_WIDTH;
			float currentV = screenBottom + (screenTop - screenBottom) * (y + 0, 5) / BUFFER_HEIGHT;
			ray_t ray = { 0 };
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;

			//vector3_t vecU = Mult(&u, currentU);

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