#include "ADV Game Engine/Graphics/Mesh.h"
#include "ADV Game Engine/Graphics/ShaderProgram.h"
#include "ADV Game Engine/Graphics/Texture.h"
#include "ADV Game Engine/Graphics/VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"



Mesh::Mesh()
{
	cout << " Mesh | Initialised Mesh " << endl;
 

}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshTextures.clear();
	MeshVAO = nullptr;

	cout << " Mesh | Mesh Destroyed.  " << endl;

}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	cout << "Creating Mesh. " << endl;

	// create the VAO 
	MeshVAO = make_shared<VAO>(Shape);

	// validate the mesh was created 

	if (MeshVAO == nullptr)
	{
		cout << " Mesh | Failed to be created. " << endl;
		return false;
	}

	// assign the shader and textures 
	this->MeshShader = MeshShader;
	this->MeshTextures = MeshTextures;

	cout <<" Mesh | created successfully. " << endl;

	return true;
}




void Mesh::Draw()
{
   // Activate the shader that this mesh use 

	MeshShader->RunShader();

	// Activate the required textures for this mesh 
	for (vmuint Index = 0; Index < MeshTextures.size(); Index++)
	{
		// activating the texture through openGL
		MeshTextures[Index]->ActivateTexture(Index);
		MeshShader->SetInt("TextureColour", Index);
		MeshTextures[Index]->BindTexture();
	}

	static CTransform  OldTransform;
	if (Transform != OldTransform)
	{
		OldTransform = Transform;
		glm::mat4 MatTransform = glm::mat4(1.0f);

		// translate, rotate and scale in this order 

		MatTransform = glm::translate(MatTransform, Transform.Location);
		// rotate 
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.x), Vector3 (1.0f, 0.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3 (0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3 (0.0f, 0.0f, 1.0f));

		// scale 
		MatTransform = glm::scale(MatTransform, Transform.Scale);
		// update the shader with new transform 
		MeshShader->SetMet4("transform", MatTransform);

	}
	
	// Draw the VAO
       MeshVAO->Draw();

}
