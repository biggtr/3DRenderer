#include <SDL.h>
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
uint32_t* color_buffer = nullptr;
bool is_running = false;
int WindowWidth = 800;
int WindowHeight = 600;

bool initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  // 0 means no errors
	{
		std::cerr << "Error Initializing SDL." << std::endl;
		return false;
	}   
	//create SDL Window
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight,SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::cerr << "Error Initializing The Window" << std::endl;
		return false;
	}
	//create SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cerr << "Error Initializing The Renderer" << std::endl;
		return false;
	}

	return true;

}

void setup()
{
	color_buffer = new uint32_t[WindowWidth * WindowHeight];

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

	SDL_RenderPresent(renderer);

}

void destroy_window()
{
	delete []color_buffer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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