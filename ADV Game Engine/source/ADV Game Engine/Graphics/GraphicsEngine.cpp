#include "ADV Game Engine/Graphics/GraphicsEngine.h"
#include "iostream"
#include "GL/glew.h"

using namespace std;

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
}

GraphicsEngine::~GraphicsEngine()
{
	cout << "Destroy Graphics engine.." << endl;
// delete the sdl window from  memory 
	SDL_DestroyWindow(SdlWindow);
// destroy the gl context
	SDL_GL_DeleteContext(SdlGLContext);
// close the sdl frame work 
	SDL_Quit();
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	// making sure that SDL is initialised
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
	{
		cout << "SDL Failed.." << SDL_GetError()<< endl;
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);

	int FullscreenFlag = 0;

	if (bFullScreen)
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	SdlWindow = SDL_CreateWindow(

		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth,
		WHeight,
        FullscreenFlag

	
	);

	if (SdlWindow == nullptr)
	{
		cout << "Sdl window failed.." << SDL_GetError() << endl;
		return false;

	}

	SdlGLContext = SDL_GL_CreateContext(SdlWindow);

	if (SdlGLContext == NULL)
	{
		cout << "SdlContext failed.." << SDL_GetError() << endl;
		return false;
	}

	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK)
	{
		cout << "Glew Failed.." << glewGetErrorString(InitGLEW) << endl;
		return false;

	}

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	glClearColor(0.23f,0.38f,0.47f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}
