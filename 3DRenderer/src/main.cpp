#include "display.h"
#include "vector.h"

#define N_POINTS (9*9*9)


bool is_running = false;

vec3_t cube_points[N_POINTS];

vec2_t projected_points[N_POINTS];
int fov_factor = 50;

void setup()
{
	color_buffer = new uint32_t[WindowWidth * WindowHeight];

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowWidth, WindowHeight);

	int points_count = 0;
	//initialize cube vector with values with 9 points in each direction x,y,z 
	for (float x = -1; x <= 1; x += 0.25) // each side is 2 size from -1 to 1  = 2; and we want to fill each with 9 points so 2/9 = 0.22
	{
		for (float y = -1; y <= 1; y += 0.25)
		{
			for (float z = -1; z <= 1; z += 0.25)
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
vec2_t project(vec3_t point)
{
	vec2_t projected_point = { fov_factor * point.x, fov_factor * point.y };
	return projected_point;
}
void update()
{
	for (int i = 0; i < N_POINTS; i++)
	{
		vec2_t projected_point = project(cube_points[i]);
		projected_points[i] = projected_point;
	}

}

void render()
{

	clear_color_buffer(0xFF000000);
	draw_grid();
	for (int i = 0; i < N_POINTS; i++)
	{
		vec2_t projected_point = projected_points[i];
		draw_rectangle(projected_point.x + WindowWidth /2 ,projected_point.y + WindowHeight / 2 ,4,4,0xFFFF0000);
		
	}
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