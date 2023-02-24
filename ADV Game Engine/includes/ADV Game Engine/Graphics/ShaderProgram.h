#pragma once
#include "ADV Game Engine/CoreMinimal.h"
#include "glm/glm.hpp"

class ShaderProgram
{

public:
	 ShaderProgram();
	~ShaderProgram();

	// this will initilize our shader as a vertex fregment shader 

	bool InitVFShader(VFShaderParams ShaderFilePaths);

	// Run the current shader program as the current shader 
	void RunShader();

	vmuint GetID()  const { return ProgramID; }

	// allow changing mat4 variables in shader code 
	void SetMet4(const char* ShaderVariable,  glm::mat4 Value);

private:
	// Attach the shader to the VAO  
	bool AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type);

	// Link the shader to the openGL

	bool Link();
		 
private:

   // openGL will assin an ID to our shader 
	vmuint ProgramID;

	// Array that will hold our ids to our unique shaders 
	// 0 - Vertex 
	// 1 - Fragment

	vmuint VFShaderIDs[2] = { 0 };


};