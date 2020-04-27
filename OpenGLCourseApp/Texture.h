#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class ATexture
{
public:
	ATexture();
	
	ATexture(char* fileLoc);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();
	
	~ATexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	char* fileLocation;

};

