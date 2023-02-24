#pragma once
#include "ADV Game Engine/CoreMinimal.h"

const PositionMatrix TrianglePositions
{
	//  x      y        z
   	-0.5f,   -0.5f,     0.0f,     1.0f, 0.0f, 0.0f,         // bottom left 
	0.5f,    -0.5f,     0.0f,     0.0f, 1.0f, 0.0f,       // bottom right
    0.0f,     0.5f,     0.0f,     0.0f, 0.0f, 1.0f       // top

};

const IndicesMatrix  TriangleIndices
{
    	0, 1, 2

};

const PositionMatrix PolyPositions
{
	//  x      y        z
	-0.5f,   -0.5f,     0.0f,     0.0f,  1.0f,   0.0f,      // bottom left 
	0.5f,    -0.5f,     0.0f,     0.0f,  1.0f,   0.0f,      // bottom right
	0.5f,     0.5f,     0.0f,     0.0f,  1.0f,   0.0f,       // top right
   -0.5f,     0.5f,     0.0f,     0.0f,  1.0f,   0.0f         // top left 

};

const IndicesMatrix  PolyIndices
{
	   0, 3, 1,   // Triangle 1
	   0, 2, 1    // Triangle 2
};

const PositionMatrix CirclePositions
{
	//  x      y        z
	-0.5f,   -0.5f,     0.0f,    // bottom left 
	0.5f,    -0.5f,     0.0f,    // bottom right
	0.5f,     0.5f,     0.0f     // top right
   - 0.5f,     0.5f,     0.0f     // top left 

};

const IndicesMatrix  CircleIndices
{
	   0,1,2,3,4,5,6,7   // Triangle 1
	   
};

 class VertexArrayObject 
{
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:

	ShapeData Shape;
	// this is version for unsigned int 
	// ID for VAO
	// ID for vertices  
	// ID for indices 
	vmuint ID, VAB, EAB;

};