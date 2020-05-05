#include "Texture.h"

ATexture::ATexture()
{
	textureID = width = height = bitDepth = 0;
	fileLocation = (char*)"";
}

ATexture::ATexture(const char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;

}

bool ATexture::LoadTexture()
{
	return LoadTexture(false);
}

bool ATexture::LoadTextureWithAlpha()
{
	return LoadTexture(true);
}

bool ATexture::LoadTexture(bool WithAlpha)
{

	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find %s\n", fileLocation);
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (WithAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

void ATexture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}

void ATexture::ClearTexture()
{
	glDeleteTextures(1,& textureID);
	textureID = width = height = bitDepth = 0;
	fileLocation = (char*)"";
}

ATexture::~ATexture()
{
	ClearTexture();
}
