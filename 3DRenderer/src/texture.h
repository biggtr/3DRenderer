#pragma once
#include <stdint.h>
struct tex2_t 
{
	float u, v;

};

extern int textureWidth,textureHeight;
extern const uint8_t REDBRICK_TEXTURE[100000];
extern uint32_t* meshTexture;