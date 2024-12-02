#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GL/glew.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	Texture(FT_Bitmap& bitmap, GLenum texType, GLenum slot);
	Texture();
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();
	void Unbind();
	void Delete();
};
#endif