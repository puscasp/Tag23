#ifndef  SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class shader {
public:
	unsigned int ID;
	
	shader(const char* vPath, const char* fPath) {
		/*------------
		//read shader source code
		*/
		std::string vCode;
		std::string fCode;

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			//open file
			vShaderFile.open(vPath);
			fShaderFile.open(fPath);
			std::stringstream vShaderStream, fShaderStream;
			//read file into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file
			vShaderFile.close();
			fShaderFile.close();
			//convert string to stream
			vCode = vShaderStream.str();
			fCode = fShaderStream.str();

		} catch (std::ifstream::failure e) {
			std::cout << "SHADER FILE READ ERROR" << std::endl;
		}

		//Convert to null-terminator version
		const char* vShaderCode = vCode.c_str();
		const char* fShaderCode = fCode.c_str();
			

		/*------------
		//compile shaders
		*/
		unsigned int vertex, fragment;
		int success;
		char log[512];

		//Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, log);
			std::cout << "VERTEX SHADER COMPILE ERROR\n" << log << std::endl;
		}

		//Fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, log);
			std::cout << "FRAGMENT SHADER COMPILE ERROR\n" << log << std::endl;
		}

		/*------------
		//Link shaders
		*/

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, log);
			std::cout << "SHADER LINKING ERROR\n" << log << std::endl;



		}
		
		/*------------
		//Cleanup
		*/

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	

	}

	void use() {
		glUseProgram(ID);
	}

	/*
		UNIFORM UTILS 
	
	*/


	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

};

#endif // ! SHADER_H