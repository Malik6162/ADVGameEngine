#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vmuint;

class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;
typedef vector <VAOPtr> VAOStack;


class ShaderProgram;
typedef shared_ptr <ShaderProgram> ShaderPtr;


// useful for shape data and VAOs Matrices
typedef vector <float> PositionMatrix;
typedef vector <vmuint> IndicesMatrix;


// this struct will handle matrices 
struct ShapeData
{
	vector<float> PositionMatrix;
	vector <vmuint> IndicesMatrix;
};

// a list of geometric shapes availabe in VAO
enum class GeometricShapes
{
	Triangle = 0,
	Polygon,
	Circle

};

// store the paramater required to create a shader program

struct VFShaderParams
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;

};

// the type of shader that can be accepted in our program
enum  class ShaderTypes
{
	Vertex = 0,
	Fragment


};

 