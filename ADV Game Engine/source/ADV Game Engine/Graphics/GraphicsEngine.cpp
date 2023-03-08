#include "ADV Game Engine/Graphics/GraphicsEngine.h"
#include "iostream"
#include "GL/glew.h"
#include "ADV Game Engine/Graphics/VertexArrayObject.h"
#include "ADV Game Engine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ADV Game Engine/Graphics/Texture.h"
#include "ADV Game Engine/Graphics/Mesh.h"

 

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	// clear the mesh stack 
	MeshStack.clear();

	//clear shader
	Shader = nullptr;
	
	// remove textures from memory 
	TextureStack.clear();





// delete the sdl window from  memory 
	SDL_DestroyWindow(SdlWindow);
// destroy the gl context
	SDL_GL_DeleteContext(SdlGLContext);
// close the sdl frame work 
	SDL_Quit();

	cout << "Destroy Graphics Engine.." << endl;
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	// making sure that SDL is initialised
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
	{
		cout << "SDL Failed.." << SDL_GetError()<< endl;
		return false;
	}
// USE openGL 4.6 compatability and set default attributes
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
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

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireframeMode(false);

	// run through each mesh and call its draw method 

	for (MeshPtr LMesh : MeshStack)
	{
		LMesh->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

MeshPtr GraphicsEngine::CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	// initializ a new mesh class 

	MeshPtr NewMesh = make_shared<Mesh>();

	// make sure it worked 

	if (!NewMesh->CreateSimpleShape(Shape, MeshShader, MeshTextures))
		return nullptr;

// add mesh into the stack of meshes to be rendered
	MeshStack.push_back(NewMesh);

	// retun the new mesh 
	return NewMesh;


}

ShaderPtr  GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{

	ShaderPtr NewShader = make_shared<ShaderProgram>();

	// Initialize the shader into openGL usig the file path
	NewShader->InitVFShader(ShaderFilePaths);

	// add the shader to our graphics engine 
	Shader = NewShader;

	return NewShader;

}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{

	TexturePtr NewTexture = nullptr;

	// Run through all the textures and check if one with the same path exists 

	for (TexturePtr TestTexture : TextureStack)
	{
		// if we find the texture with the same file path 
		if (TestTexture->GetFilePath() == FilePath)
		{
			// pass in the already created texture
			NewTexture = TestTexture;
			cout << "Texture Found ! Assigning current texture " << endl;
			break;
		}


	}

		// if there is no texture already in the existance 
		if (NewTexture == nullptr)
		{
			cout << "Creating a new texture " << endl;

             // create a new texture as a shared ptr

			NewTexture = make_shared<Texture>();

			// if the filer was found assign it to the texture stack 

			if (NewTexture->CreateTextureFromFilePath(FilePath))
			{
				cout << "Texture " << NewTexture->GetID()<<"Creating Success ! Adding to texture stack. " << endl;

				// Add the texture to the texture stack 
				TextureStack.push_back(NewTexture);
				
			}
		}
 
	return NewTexture;
}




void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	// if wireframe mode is set change it, vice verse 
	if (bShowWireframeMode != bWireframeMode)
	{
		bWireframeMode = bShowWireframeMode;
		
		// change how openGL renders between vertices 
		if (bWireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
		}
		cout << "Wire Frame mode updated..." << endl;

	}


}
