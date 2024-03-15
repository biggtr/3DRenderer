#include "display.h"
#include "vector.h"

bool is_running = false;

int N_POINTS;
vec3_t * cube_points = new vec3_t[N_POINTS];


void setup()
{
	color_buffer = new uint32_t[WindowWidth * WindowHeight];

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowWidth, WindowHeight);

	int points_count = 0;
	//initialize cube vector with values with 9 points in each direction x,y,z 
	for (float x = -1; x <= 1; x += 0.22) // each side is 2 size from -1 to 1  = 2; and we want to fill each with 9 points so 2/9 = 0.22
	{
		for (float y = -1; y <= 1; y += 0.22)
		{
			for (float z = -1; z <= 1; z += 0.22)
			{
				vec3_t new_point = { x,y,z };
				cube_points[points_count++] = new_point;
			}
		}
	}
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
	draw_pixel(100, 100, 0xFFFF0000);
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