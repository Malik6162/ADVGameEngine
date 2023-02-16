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


// useful for shape data and VAOs Matrices
typedef vector <float> PositionMatrix;
typedef vector <vmuint> IndicesMatrix;


// this struct will handle matrices 
struct ShapeData
{
	vector<float> PositionMatrix;
	vector <vmuint> IndicesMatrix;
};

 