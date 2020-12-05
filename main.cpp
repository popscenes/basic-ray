#include <stdio.h>
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "defs.h"
#include "graphics.h"
#include "vector.h"
#include "ray.h"
#include "circle.h"


bool isGameRunning = false;
int ticksLastFrame;

float screenLeft = -1;
float screenRight = 1;
float screenTop = 1;
float screenBottom = -1;

vector3_t cameraPos = { 0,0,0 };

ray_t rays[BUFFER_WIDTH * BUFFER_HEIGHT];

vector3_t u = { 1,0,0 };
vector3_t v = { 0,1,0 };
vector3_t w = { 0,0,1 };

circle c = {
	{0,0,-1.0},
	0.7
};

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

			rays[(y * BUFFER_WIDTH) + x].origin.x = 0;
			rays[(y * BUFFER_WIDTH) + x].origin.y = 0;
			rays[(y * BUFFER_WIDTH) + x].origin.z = 0;
			rays[(y * BUFFER_WIDTH) + x].direction = (w * -1) + (currentU * u) + (currentV * v);
			
			ray_t currentRay = rays[(y * BUFFER_WIDTH) + x];
			vector3_t oc = currentRay.origin - c.centre;
			
			float hita = dot(currentRay.direction, currentRay.direction);
			float hitb = 2.0 *dot(currentRay.direction, oc);
			float hitc = dot(oc, oc) - (c.radius * c.radius);

			float discriminant = hitb*hitb - 4.0*(hita * hitc);
			if (discriminant >= 0)
			{
				rays[(y * BUFFER_WIDTH) + x].hit = true;
			}
		}
	}
}
void render()
{
	clearColourBuffer(0xFF666666);
	for (int y = 0; y < BUFFER_HEIGHT; y++)
	{
		for (int x = 0; x < BUFFER_WIDTH; x++)
		{
			uint32_t* buffer = GetColourBuffer();
			if (rays[(y * BUFFER_WIDTH) + x].hit == true)
			{
				buffer[(y * BUFFER_WIDTH) + x] = 0xffffffff;
			}
		}
	}

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