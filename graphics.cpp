#include <stdio.h>
#include "graphics.h"
#include "defs.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static uint32_t* colourBuffer = NULL;
static SDL_Texture* colourBufferTexture;

uint32_t* GetColourBuffer()
{
	return colourBuffer;
}
void drawRectangle(int x, int y, int width, int height, uint32_t colour)
{	
	if (x < 0 || (x + width) > BUFFER_WIDTH || y < 0 || (y + height) > BUFFER_HEIGHT)
	{
		return;
	}

	for (int ypos = y; ypos <= (y + height); ypos++)
	{
		for (int xpos = x; xpos <= (x +width); xpos++)
		{
			colourBuffer[(ypos * BUFFER_WIDTH) + xpos] = colour;
		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, uint32_t colour)
{
	int deltaX = x1 - x0;
	int deltaY = y1 - y0;

	int sideLength = abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY);

	float xinc = deltaX / (float)sideLength;
	float yInc = deltaY / (float)sideLength;

	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i < sideLength; i++)
	{
		colourBuffer[(int)(round(currentY) * BUFFER_WIDTH) + (int)round(currentX)] = colour;
		currentX += xinc;
		currentY += yInc;
	}
}

bool initialiseWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error Init SDL.\n");
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
		
	int screenWidth = 640;
	int screenHeight = 640;

	window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	colourBuffer = (uint32_t*)malloc((uint32_t)BUFFER_HEIGHT * (uint32_t)BUFFER_WIDTH * sizeof(uint32_t));
	colourBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, BUFFER_WIDTH, BUFFER_HEIGHT);

	return true;
}

void destroyWindow() {
	free(colourBuffer);
	SDL_DestroyTexture(colourBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clearColourBuffer(uint32_t colour)
{
	for (size_t x = 0; x < BUFFER_WIDTH; x++)
	{
		for (size_t y = 0; y < BUFFER_HEIGHT; y++)
		{
			colourBuffer[(y * BUFFER_WIDTH) + x] = colour;
		}
	}
}

void renderColourBuffer()
{
	SDL_UpdateTexture(colourBufferTexture, NULL, colourBuffer, (int)((uint32_t)BUFFER_WIDTH * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, colourBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}