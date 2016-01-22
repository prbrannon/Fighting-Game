
#include "Texture.h"
#include "DevIL.h"

Texture::Texture()
{
    //Initialize texture ID
    mTextureID = 0;

    //Initialize texture dimensions
    mTextureWidth = 0;
    mTextureHeight = 0;
}

Texture::~Texture()
{
    //Free texture data if needed
    FreeTexture();
}

bool Texture::LoadTextureFromFile( std::string path )
{
    //Texture loading success
    bool textureLoaded = false;

    //Generate and set current image ID
    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    //Load image
    ILboolean success = ilLoadImage( path.c_str() );

    //Image loaded successfully
    if( success == IL_TRUE )
    {
        //Convert image to RGBA
        success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
            //Create texture from file pixels
            textureLoaded = LoadTextureFromPixels32( (GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) );
        }

        //Delete file from memory
        ilDeleteImages( 1, &imgID );
    }

    //Report error
    if( !textureLoaded )
    {
        printf( "Unable to load %s\n", path.c_str() );
    }

    return textureLoaded;
}

bool Texture::LoadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height )
{
    //Free texture if it exists
    FreeTexture();

    //Get texture dimensions
    mTextureWidth = width;
    mTextureHeight = height;

    //Generate texture ID
    glGenTextures( 1, &mTextureID );

    //Bind texture ID
    glBindTexture( GL_TEXTURE_2D, mTextureID );

    //Generate texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    //Unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }

    return true;
}

void Texture::FreeTexture()
{
    //Delete texture
    if( mTextureID != 0 )
    {
        glDeleteTextures( 1, &mTextureID );
        mTextureID = 0;
    }

    mTextureWidth = 0;
    mTextureHeight = 0;
}

void Texture::Render( GLfloat x, GLfloat y )
{
    //If the texture exists
    if( mTextureID != 0 )
    {
        //Remove any previous transformations
        glLoadIdentity();

        //Move to rendering point
        glTranslatef( x, y, 0.f );

        //Set texture ID
        glBindTexture( GL_TEXTURE_2D, mTextureID );

        //Render textured quad
        glBegin( GL_QUADS );
			glTexCoord2f( 0.f, 0.f ); glVertex2f(           0.f,            0.f );
            glTexCoord2f( 1.f, 0.f ); glVertex2f( mTextureWidth,            0.f );
            glTexCoord2f( 1.f, 1.f ); glVertex2f( mTextureWidth, mTextureHeight );
            glTexCoord2f( 0.f, 1.f ); glVertex2f(           0.f, mTextureHeight );
        glEnd();

		/*
		// Flip vertically for bmp:
            glTexCoord2f( 0.f, 0.f ); glVertex2f(           0.f, mTextureHeight );
            glTexCoord2f( 1.f, 0.f ); glVertex2f( mTextureWidth, mTextureHeight );
            glTexCoord2f( 1.f, 1.f ); glVertex2f( mTextureWidth,            0.f );
            glTexCoord2f( 0.f, 1.f ); glVertex2f(           0.f,            0.f );
			*/
    }
}

GLuint Texture::GetTextureID()
{
    return mTextureID;
}

GLuint Texture::TextureWidth()
{
    return mTextureWidth;
}

GLuint Texture::TextureHeight()
{
    return mTextureHeight;
}


