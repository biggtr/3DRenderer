#pragma once
#include <SDL.h>
#include <iostream>

#define FPS 30 
#define FRAME_TARGET_TIME  (1000/FPS)  // 1000 is how many millisecond in one second





extern int windowWidth;
extern int windowHeight;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;


bool initializeWindow();
void clearColorBuffer(uint32_t color);
void drawRectangle(int pos_x, int pos_y, int width, int height, uint32_t color);
void drawGrid();
void drawPixel(int x, int y, uint32_t color);
void renderColorBuffer();

void destroyWindow();
