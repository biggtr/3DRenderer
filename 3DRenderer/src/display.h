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


bool initialize_window();
void clear_color_buffer(uint32_t color);
void draw_rectangle(int pos_x, int pos_y, int width, int height, uint32_t color);
void draw_grid();
void draw_pixel(int x, int y, uint32_t color);
void render_color_buffer();

void destroy_window();
