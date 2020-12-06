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
	{0,0,-1},
	0.5,
	0xFFAAAA11
};

vector3_t light = {
-10,3,10
};

void setup()
{
	
}

float max(float a, float b)
{
	if (a > b)
	{
		return a;
	}

	return b;
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
				float timeHit = (-1*hitb - sqrt(discriminant)) / 2.0*hita;
				vector3_t hitPoint = (rays[(y * BUFFER_WIDTH) + x].origin +  rays[(y * BUFFER_WIDTH) + x].direction) * timeHit;
				rays[(y * BUFFER_WIDTH) + x].hit = true;
				rays[(y * BUFFER_WIDTH) + x].colour = c.colour;
				rays[(y * BUFFER_WIDTH) + x].light = unit(light - hitPoint);
				rays[(y * BUFFER_WIDTH) + x].normal = (hitPoint - c.centre)/c.radius;
				rays[(y * BUFFER_WIDTH) + x].view = unit(hitPoint*-1);
				rays[(y * BUFFER_WIDTH) + x].half = unit(rays[(y * BUFFER_WIDTH) + x].light + rays[(y * BUFFER_WIDTH) + x].view);
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
				
				uint32_t blue = ((rays[(y * BUFFER_WIDTH) + x].colour & 0x00FF0000) >> 16);
				uint32_t green = ((rays[(y * BUFFER_WIDTH) + x].colour & 0x0000FF00) >> 8);
				uint32_t red = ((rays[(y * BUFFER_WIDTH) + x].colour & 0x000000FF));

				float ambientLightIntensity = 0.35;
				
				float lightValue = 1.0f * max(0, dot(rays[(y * BUFFER_WIDTH) + x].normal, rays[(y * BUFFER_WIDTH) + x].light));
				float specularComponent = max(0, dot(rays[(y * BUFFER_WIDTH) + x].normal, rays[(y * BUFFER_WIDTH) + x].half));
				specularComponent = pow(specularComponent, 20);

				//if (lightValue > 1.0f)
				//{
				//	lightValue = 1.0f;
				//}
				/*if (specularComponent > 0)
				{
					specularComponent = specularComponent;
				}*/

				uint32_t shadedblue = (ambientLightIntensity*blue) + (blue * lightValue) +150 * 1 * specularComponent;
				uint32_t shadedGreen = (ambientLightIntensity * green) + (green * lightValue) + 150 * 1 * specularComponent;;
				uint32_t shadedRed = (ambientLightIntensity * red) + (red * lightValue) +150 * 1 * specularComponent;

				shadedblue = shadedblue > 255 ? 255 : shadedblue;
				shadedGreen = shadedGreen > 255 ? 255 : shadedGreen;
				shadedRed = shadedRed > 255 ? 255 : shadedRed;



				int drawY = (BUFFER_HEIGHT - y);

				buffer[(drawY * BUFFER_WIDTH) + x] = (0xFF000000) | (shadedblue << 16) | (shadedGreen << 8) | shadedRed;
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