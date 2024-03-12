#include <SDL.h>
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
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

int main(int argc,char*args[])
{
	is_running = initialize_window();
	std::cout << "Hello, world!";
	return 0;
}