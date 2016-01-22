
#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGL.h"
#include <string>

class Texture
{
public:
	Texture(void);
	~Texture(void);

	bool LoadTextureFromFile(std::string path);
	
	bool LoadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );

	void FreeTexture();

	void Render( GLfloat x, GLfloat y );

	GLuint GetTextureID();

	GLuint TextureWidth();

	GLuint TextureHeight();

private:
	//Texture name
	GLuint mTextureID;
	
	//Texture dimensions
	GLuint mTextureWidth;
	GLuint mTextureHeight;
};

#endif