#include"ADV Game Engine/Graphics/Texture.h"
#include "GL/glew.h"
#include "stb_image/stb_image.h"
#include <string>


Texture::Texture()
{
	TextureID = 0;
	FilePath = " ";

	// assign an open gl texture ID 
	glGenTextures( 1, &TextureID);

	// Set the current texture as current openGL texture 
 	BindTexture();

	// set default geometry texture settings 

	// see what happens if the texture does not fit the whole geometry 
	// s = u = x --- t = v = y = --- r = z (we dont use z for 2d textures)
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// set the image how it will blur between as it scales up and down resulation

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	cout << "Initialised Texture with ID :" << TextureID <<endl;

}

Texture::~Texture()
{
	// destroy the texture from the memory 
	glDeleteTextures(1, &TextureID);

	cout << " Texture "<< TextureID << " Deleted !" << endl;

}

bool Texture::CreateTextureFromFilePath(const char* FilePath)
{
	BindTexture();

	this->FilePath = FilePath;
	// hold the imported image data 
	ImportImageData  ImageData;

	// tell stbi to load our images in flipped
	stbi_set_flip_vertically_on_load(true);

	// loading the image using file path and getting image data 
	    unsigned  char* RawImage = stbi_load(
  	FilePath,
		&ImageData.w,
		&ImageData.h,
		&ImageData.channels,
		STBI_rgb_alpha
	);

		if (!RawImage)
		{
			cout << "Texture | Image couldn't be loaded." << endl;
			return false;	
		}

		// convert the image data into a openGL texture 


		glTexImage2D(
		
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		ImageData.w, ImageData.h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		RawImage
		
		);

		// genrate the smaller version of the texture for when further away 
		glGenerateMipmap(GL_TEXTURE_2D);

		// destroy the raw image data from memory
		stbi_image_free(RawImage);

	    return true;
}



void Texture::BindTexture()
{
	// check that an id has been assined then bind the texture as the current 
	if (TextureID != 0)
	{
		glBindTexture(GL_TEXTURE_2D , TextureID);

	}

}

void Texture::ActivateTexture()
{
	if (TextureID != 0 )
	{
		glActiveTexture(GL_TEXTURE0 + TextureID - 1);
	}

}

void Texture::ResetTexture()
{

	// assign the first texture to anything without a texture 
	glActiveTexture(GL_TEXTURE0);


}
