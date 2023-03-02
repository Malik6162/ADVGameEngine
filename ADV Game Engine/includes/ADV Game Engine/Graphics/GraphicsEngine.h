#pragma once

#include "SDL2/SDL.h"
#include <ADV Game Engine/CoreMinimal.h>

class GraphicsEngine {

public:

	GraphicsEngine();
	~GraphicsEngine();

	// creat the window 

	bool InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);
  // show the newest frame graphics 
	void PresentGraphics();
  // clear the old frame graphics
	void ClearGraphics();

	// handle the rendering of our graphics
	void Draw();


// return the sdl window 
	SDL_Window* GetWindow() const;

	//  add a new VAO to the VAO task 
	void CreatVAO(GeometricShapes Shape);

   // add a new shader 
	void CreateShader(VFShaderParams ShaderFilePaths);

	// create a texture and add it to the texture file 
	// avoid duplicate texture
	TexturePtr CreateTexture(const char* FilePath);


   private:
	// this will hold the window 
	SDL_Window* SdlWindow;

	// this will allow openGL to work in  SDL 
	SDL_GLContext SdlGLContext;

	// it will stack all the VAO 
	 
	VAOStack VAOs;

	// handle wireframe mode 

	void HandleWireframeMode(bool bShowWireframeMode);

	bool bWireframeMode;

	// single Shader 
	ShaderPtr Shader;

	TexturePtrStack    TextureStack;

};