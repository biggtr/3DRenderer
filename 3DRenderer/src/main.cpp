#include "display.h"


bool is_running = false;



void setup()
{
	color_buffer = new uint32_t[WindowWidth * WindowHeight];

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowWidth, WindowHeight);
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			is_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;

	}

}

void update()
{


}

void render()
{

	SDL_SetRenderDrawColor(renderer, 255, 0, 0,0);
	SDL_RenderClear(renderer);
	clear_color_buffer(0xFF000000);
	draw_grid();
	draw_rectangle(100,600,400,200,0xFFFF0000);
	render_color_buffer();
	SDL_RenderPresent(renderer);

}



int main(int argc,char*args[])
{
	is_running = initialize_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	std::cout << "Hello, world!";
	return 0;
}