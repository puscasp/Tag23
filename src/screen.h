/*
Visual display of buttons and graphical elements. Is kept as a group. Has a vertex buffer per screen.
*/
#ifndef SCREEN_H
#define SCREEN_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <uielement.h>
#include <unordered_map>
class screen{

	unsigned int screenEBO, screenVBO;
	std::vector<Index> screenIndexList;
	std::vector<Vertex> screenVertexList;
	//
	void returnEBO(GLuint* EBOptr, GLuint* VBOptr); 

	void onClick();
};


#endif





