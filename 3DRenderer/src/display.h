#pragma once
#include <SDL.h>
#include <iostream>


extern int WindowWidth;
extern int WindowHeight;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;




bool initialize_window();
void clear_color_buffer(uint32_t color);
void draw_rectangle(int pos_x, int pos_y, int width, int height, uint32_t color);
void draw_grid();
void draw_pixel(int x, int y, uint32_t color);
void render_color_buffer();

void destroy_window();