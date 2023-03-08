#pragma once
#include"ADV Game Engine/CoreMinimal.h"

// hold the image data for conversion to the text file 
struct ImportImageData
{
	int w = 0;
	int h = 0;
	int channels = 0;

};

class Texture
{

public:
	Texture();
	~Texture();

	// create texture file from the imported image path
	bool CreateTextureFromFilePath(const char* FilePath);


	vmuint GetID() const {  return TextureID;  }

	// bind the texture as current texture in in openGL
	void BindTexture();

	// Assign the relevent data to the current loaded texture 
	void ActivateTexture(vmuint Index);

   // clear the texture in openGL
	static void  ResetTexture();

	// return the file path 
	const char* GetFilePath() const { return FilePath;  }


private:
  // hold the id for the texture in OpenGl
	vmuint   TextureID;
// hold the file path to avoid duplications 
	const  char* FilePath;
};
