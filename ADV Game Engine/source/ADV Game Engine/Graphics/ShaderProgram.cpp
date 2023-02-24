#include "ADV Game Engine/Graphics/ShaderProgram.h"
#include "GL/glew.h"
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram()
{
	ProgramID = 0;
}



ShaderProgram::~ShaderProgram()
{

	for (vmuint VFShaderID : VFShaderIDs)
		// remove the shader from the program 
	{
		glDetachShader(ProgramID, VFShaderID);
		// delete ethe shader from the memory 
		glDeleteShader(VFShaderID);

	}
	// this will delete the program from openGL
	glDeleteProgram(ProgramID);

	cout << "Shader Program " << ProgramID << " has been destroyed..." << endl;
}



bool ShaderProgram::InitVFShader(VFShaderParams ShaderFilePaths)
{
	ProgramID = glCreateProgram();
	if (ProgramID < 1)
	{
		cout << "Shader Program | can't assign program ID " << endl;
		return false;
	}

	bool VShader = AttachShader(ShaderFilePaths.VertexShaderPath, ShaderTypes::Vertex);
	bool FShader = AttachShader(ShaderFilePaths.FragmentShaderPath, ShaderTypes::Fragment);

	if (!VShader || !FShader)
	{
		return false;
	}
	// fails the whole function if link() fails
	return Link();
}

void ShaderProgram::RunShader()
{

	glUseProgram(ProgramID);

}

void ShaderProgram::SetMet4(const char* ShaderVariable, glm::mat4 Value)
{
	// finding the uniform mat4 called shader variable and overwritting the value 
	glUniformMatrix4fv(
	glGetUniformLocation(ProgramID, ShaderVariable), 1, GL_FALSE, value_ptr(Value)
	);


}

bool ShaderProgram::AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type)
{
	// store the shader code 
	string ShaderCode;
	// store the file path in a file stream 
	ifstream FilePathstream(ShaderFilePath);

	// check if the stream found the file 

	if (!FilePathstream.is_open())
	{
		wclog << "Shader Program |" << ShaderFilePath << " not found. " << endl;
		return false;
	
	}

	// temporarily hold the shader for conversion in a string steam 

	stringstream RawShaderCode;

	// convert the file to a single string 
	RawShaderCode << FilePathstream.rdbuf();
	// convert it to a readable string 

	ShaderCode = RawShaderCode.str();

	// close the steam to the file 
	
	FilePathstream.close();

	// Initialize the shader ID variable for this specific shader 

	vmuint ShaderID = 0;

	// change what happen with the id depending on the type of the shader 

	switch (Type)
	{
	case ShaderTypes::Vertex :
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		VFShaderIDs[0] = ShaderID;
 	    break;

	case ShaderTypes::Fragment :
		ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		VFShaderIDs[1] = ShaderID;
		break;

	  default:
		break;
	}

	// put the string code into the character array 
	const char* ShaderCodePtr = ShaderCode.c_str();
	
	// add the shader code to the above shader the we have created 
	glShaderSource(ShaderID, 1, &ShaderCodePtr, NULL);

	// compil the shader 
	glCompileShader(ShaderID);

	// initializ a variable that will tell us if teh shader has any logs 

	int  LogLength = 0;

	// check if there are any logs them add them to the loglenght 

	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogLength);
     // print the log if there were any 
	if (LogLength > 0)
	{
		// store the message 
		vector<char> LogMessage(LogLength +1);
		// add the characters into the vector array 
		glGetShaderInfoLog(ShaderID, LogLength, NULL , &LogMessage[0]);

		// check if the compiled failed 

		int CompileStatus = GL_TRUE;

		// get the compile status 
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == GL_TRUE)
		{
			wclog << " Shader Program | compiler |" << ShaderFilePath <<
				" Compiled sucessfully with the following log: " << endl
			   << &LogMessage[0] << endl;

		}
		else
		{
			wclog << " Shader Program | compiler |" << ShaderFilePath <<
				" failed to compile with the following log: " << endl
				<< &LogMessage[0] << endl;
			return false;
		}
	}
	else
	{
		wclog << " Shader Program |" << ShaderFilePath << "Compiled Sucessfully with no logs." << endl;
	}
	// attach the shader to the program ID 

	  glAttachShader(ProgramID, ShaderID);
	  

	  return true;
}

bool ShaderProgram::Link()
{
	// add the program to openGL

	glLinkProgram(ProgramID);

	// check the link for logs and errors 
	int LogLength = 0;

	glGetShaderiv(ProgramID, GL_INFO_LOG_LENGTH, &LogLength);

	if (LogLength > 0)
	{
		vector<char> LogMessage(LogLength + 1);
 		glGetShaderInfoLog(ProgramID, LogLength, NULL, &LogMessage[0]);

		int CompileStatus = GL_TRUE;

 		glGetShaderiv(ProgramID, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == GL_TRUE)
		{
			wclog << " Shader Program | successfully linked with the following log : " << endl
				<< &LogMessage[0] << endl;
		}
		else
		{
			wclog << " Shader Program | Failed to linked with the following log : " << endl
				<< &LogMessage[0] << endl;
			return false;
		}
		 
	}
	else
	{
		wclog << " Shader Program | sucessfully linked with no logs : " << endl;
	}

	return true;
}
