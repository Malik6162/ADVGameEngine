#pragma once
#include "ADV Game Engine/CoreMinimal.h"
#include "ADV Game Engine/Math/Transformations.h"


class Mesh
{
public:

	Mesh();
	~Mesh();

	//create the mash out of VAO, a shader and texture 
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack  MeshTextures);


	// handle the drawing of all the required classes
	void Draw();

	// this hold the scale, position and rotation of the mesh 
	CTransform Transform;

private:
	// store the shader this mesh requires
	ShaderPtr MeshShader;

	// store the textures this mesh requires 
	TexturePtrStack    MeshTextures;

	// create a new VAO for the mesh 

	VAOPtr   MeshVAO;

};