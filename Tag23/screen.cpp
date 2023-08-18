/*
Visual display of buttons and graphical elements. Is kept as a group. Has a vertex buffer per screen.
*/
#include <screen.h>
class screen {
	unsigned int screenEBO, screenVBO;

	std::vector<Vertex> screenVertexList;
	std::vector<int> screenIndexList;
	std::vector<uiElement> screenElementList;


public:
	//Compile all the verts in corresponding 
	void buildEBO(GLuint* EBOptr, GLuint* VBOptr) {
		std::unordered_map<Vertex,int> vertexTable;
		for (int i = 0; i < screenElementList.size(); ++i)
		{
			std::vector<Vertex>* elementVerts = &screenElementList[i].getVerts();
			for (int j = 0; j < (*elementVerts).size(); ++j)
			{
				if (vertexTable.count((*elementVerts)[j]) == 0) //unique
				{
					vertexTable.insert({ (*elementVerts)[j], vertexTable.size() + 1 });
					screenVertexList.push_back((*elementVerts)[j]);
				}
				screenIndexList.push_back(vertexTable[(*elementVerts)[j]]);
			}
		}
		
		glGenVertexArrays(1, EBOptr);
		glGenBuffers(1, VBOptr);

		glBindBuffer(GL_ARRAY_BUFFER, *VBOptr);
		glBufferData(GL_ARRAY_BUFFER, screenVertexList.size() * sizeof(Vertex), &screenVertexList[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBOptr);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, screenIndexList.size() * sizeof(unsigned int), &screenIndexList[0], GL_STATIC_DRAW);
	}


};







