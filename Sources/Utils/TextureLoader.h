#pragma once

#include "GL\glew.h"

#include "..\bitmap\bitmap_image.hpp"

class TextureLoader {
private:
	char* files [6] = { "skybox\\ascend4bk.bmp",
			"skybox\\ascend4dn.bmp", "skybox\\ascend4ft.bmp",
			"skybox\\ascend4lf.bmp", "skybox\\ascend4rt.bmp" ,
			"skybox\\ascend4up.bmp" };

public:
	GLuint* loadTextures()
	{
		GLuint textures [6] = { 0 };
		for (int i = 0; i < 6; i++)
		{
			bitmap_image image(files[i]);

			const unsigned char* data = image.data();

			int width = image.width(),
				height = image.height();
			GLuint texture;

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

			textures[i] = texture;
		}

		return textures;
	}
};