#include <SDL.h>
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* color_buffer_texture = nullptr;
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
	//getting the fullscreen resulotion from displaymode and storing it in display struct 
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	WindowWidth = display.w;
	WindowHeight = display.h;



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
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return true;

}

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
void render_color_buffer()
{

	SDL_UpdateTexture(color_buffer_texture, nullptr, color_buffer, WindowWidth * sizeof(uint32_t));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid()
{
	for (int y = 0; y < WindowHeight; y += 15)
	{
		for (int x = 0; x < WindowWidth; x+= 15)
		{
			color_buffer[WindowWidth * y + x] = 0xff333333;
		}
	}
}
void draw_rectangle(int pos_x, int pos_y,int width,int height,uint32_t color)
{
	for (int y = pos_y;y < height; y++)
	{
		for (int x = pos_x; x < width; x++)
		{
			color_buffer[WindowWidth * y + x] = color;
		}
	}

}
void clear_color_buffer(uint32_t color)
{
	//time complixity O(n) but we dont use this because we're working with 2d array
	//  in 1 dimension and we want to have much more control over the pixels
	// 
	//for (int i = 0; i < WindowHeight * WindowWidth; i++) 
	//{
	//	color_buffer[i] = color;
	//}

	for (int y = 0; y < WindowHeight; y++)
	{
		for (int x = 0; x < WindowWidth; x++)
		{
			color_buffer[WindowWidth * y + x] = color;
		}
	}
}
void render()
{

	SDL_SetRenderDrawColor(renderer, 255, 0, 0,0);
	SDL_RenderClear(renderer);
	clear_color_buffer(0xFF000000);
	draw_grid();
	draw_rectangle(400,200,700,600,0xFFFF0000);
	render_color_buffer();
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