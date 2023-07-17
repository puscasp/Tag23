/*
Visual display of buttons and graphical elements. Is kept as a group. Has a vertex buffer per screen.
*/
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <types.h>
#include <vector>
#include <uielement.h>


unsigned int screenEBO, screenVBO;


void returnEBO(GLuint *EBOptr, GLuint *VBOptr) {

	std::vector<Vertex> vertexList;
	std::vector<unsigned int> indexList;




	/*
	foreach uielement
		foreach vertex
		
			add to hashmap
			if unique: add to vertexlist
			add to indexlist
	
	
	*/




	glGenVertexArrays(1, EBOptr);
	glGenBuffers(1, VBOptr);

	glBindBuffer(GL_ARRAY_BUFFER, *VBOptr);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBOptr);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexList.size() * sizeof(unsigned int), &indexList[0], GL_STATIC_DRAW);
}








