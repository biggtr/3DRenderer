#include "display.h"




int windowWidth = 800;
int windowHeight = 600;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
uint32_t* colorBuffer = nullptr;
SDL_Texture* colorBufferTexture = nullptr;

bool initializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  // 0 means no errors
	{
		std::cerr << "Error Initializing SDL." << std::endl;
		return false;
	}
	//getting the fullscreen resulotion from displaymode and storing it in display struct 
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	windowWidth = display.w;
	windowHeight = display.h;



	//create SDL Window
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

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




void destroyWindow()
{
	delete[]colorBuffer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void renderColorBuffer()
{

	SDL_UpdateTexture(colorBufferTexture, nullptr, colorBuffer, windowWidth * sizeof(uint32_t));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void drawGrid()
{
	for (int y = 0; y < windowHeight; y += 15)
	{
		for (int x = 0; x < windowWidth; x += 15)
		{
			colorBuffer[windowWidth * y + x] = 0xff333333;
		}
	}
}
void drawPixel(int x ,int y , uint32_t color)
{
	if ( x >= 0 && x < windowWidth && y >=0 && y < windowHeight)
		colorBuffer[windowWidth * y + x] = color;
}
void drawRectangle(int pos_x, int pos_y, int width, int height, uint32_t color)
{
	for (int y = pos_y; y < height + pos_y; y++)
	{
		for (int x = pos_x; x < width + pos_x; x++)
		{
			drawPixel(x, y, color);
		}
	}

}
void clearColorBuffer(uint32_t color)
{
	//time complixity O(n) but we dont use this because we're working with 2d array
	//  in 1 dimension and we want to have much more control over the pixels
	// 
	//for (int i = 0; i < WindowHeight * WindowWidth; i++) 
	//{
	//	color_buffer[i] = color;
	//}

	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			colorBuffer[windowWidth * y + x] = color;
		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, uint32_t color)
{
	int deltaX = x1 - x0;
	int deltaY = y1 - y0;

	int sideLength = std::abs(deltaY) >= std::abs(deltaX) ? std::abs(deltaY) : std::abs(deltaX);

	float xIncreament = deltaX / (float)sideLength;

	float yIncreament = deltaY / (float)sideLength;
	
	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i <= sideLength; i++)
	{
		drawPixel(std::round(currentX), std::round(currentY), color);
		currentX += xIncreament;
		currentY += yIncreament;
	}
}
