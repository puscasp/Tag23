/*
Visual display of buttons and graphical elements. Is kept as a group. Has a vertex buffer per screen.
*/
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <types.h>
#include <vector>
#include <uielement.h>
#include <unordered_map>
class screen{

	unsigned int screenEBO, screenVBO;
	std::vector<Index> screenIndexList;
	std::vector<Vertex> screenVertexList;

	void returnEBO(GLuint* EBOptr, GLuint* VBOptr); 

};








