#include "ADV Game Engine/Graphics/VertexArrayObject.h"
#include "GL/glew.h"
 

VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB  = VAB = 0;

	// localised versions of the choosen matrices 

	PositionMatrix ChosenPositions = PositionMatrix();
	IndicesMatrix  ChosenIndices   =  IndicesMatrix();

   // switch the chossen matrix on the selected 
	switch (ChosenShape)
	{
	case GeometricShapes::Triangle:
		 ChosenPositions = TrianglePositions;
		 ChosenIndices  = TriangleIndices;
		break;

	case GeometricShapes::Polygon:
		 ChosenPositions = PolyPositions;
		 ChosenIndices = PolyIndices;
		break;

	case GeometricShapes::Circle:
		 ChosenPositions = CirclePositions;
		 ChosenIndices  = CircleIndices;
		break;

	default:
		break;
	}

	Shape.PositionMatrix = ChosenPositions;
	Shape.IndicesMatrix  = ChosenIndices;


	// create the ID for our VAO

	glGenVertexArrays(1, &ID);
	 
	glBindVertexArray(ID);

	 

	// create an ID for our array buffer 
	glGenBuffers(1, &VAB);

	// bind the above ids to open GL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);

	// this will run through the data and attach to the VAB vertices
	glBufferData(GL_ARRAY_BUFFER, 
		Shape.PositionMatrix.size() * sizeof(float),
		&Shape.PositionMatrix[0], 
		GL_STATIC_DRAW);

	// handle the indicies 
	// create an id for our element buffer   
	glGenBuffers(1, &EAB);
	// bind the above id to the OpenGL as the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);

	// run through the data and attach the indices to EAB 
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndicesMatrix.size()* sizeof(vmuint), 
		&Shape.IndicesMatrix[0],
		GL_STATIC_DRAW
	);

	// Assign the vertices and indices to the VAO
	glVertexAttribPointer(
	     0,   // Data set -0 = first data set in the array 
         3,   // how many number in our matrix to make a triangle 
		GL_FLOAT, GL_FALSE,  // data types wheather you want to normlize the values
		sizeof(float) *6,   // stride the lenght it takes to get to each number  
		(void*)0         // offSet of how many numbers to skip in the matrix 
	);
	// enable the vertix array
	glEnableVertexAttribArray(0);

	// Assign the colour to the shader 
	glVertexAttribPointer(
		1, 3, 
		GL_FLOAT, GL_FALSE, 
		sizeof(float) * 6, 
		(void*) (3 * sizeof(float))
	
	);
   //   enable the colour array 
	glEnableVertexAttribArray(1);



	// clear the buffer array
	glBindVertexArray(0);

}

VertexArrayObject::~VertexArrayObject()
{
	// Clean up VAO in the open GL
	glDeleteVertexArrays(1, &ID);

	// clean up the vectors 
	Shape.PositionMatrix.clear();
	Shape.IndicesMatrix.clear();

	cout << "Deleted VAO " << endl;
}

void VertexArrayObject::Draw()
{
	// bind our VAO to the current buffer 
	glBindVertexArray(ID);
	//Draw the 3D object 
	glDrawElements( 

    	GL_TRIANGLES,                  //  what types of object are we drawaing 
		Shape.IndicesMatrix.size(),    // how many vertices do need to draw  
		GL_UNSIGNED_INT,          // whats the type of data that is being input 
	  	 (void*) 0            // how many should we skip 
	);
	// clear the VAO from the current array to allow for the next objects
	glBindVertexArray(0);
}
