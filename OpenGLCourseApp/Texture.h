#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class ATexture
{
public:
	ATexture();
	
	ATexture(const char* fileLoc);

	bool LoadTextureWithAlpha();
	bool LoadTexture();

	void UseTexture();
	void ClearTexture();
	
	~ATexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;

	bool LoadTexture(bool WithAlpha);
};

