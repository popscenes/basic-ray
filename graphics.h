#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

bool initialiseWindow();
void drawRectangle(int x, int y, int width, int height, uint32_t colour);
void drawLine(int x0, int y0, int x1, int y1, uint32_t colour);
void destroyWindow();
void renderColourBuffer();
void clearColourBuffer(uint32_t colour);
uint32_t* GetColourBuffer();