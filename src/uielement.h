#include <vector>;
#include <types.h>;
unsigned int *parentScreenVBO;
std::vector<unsigned int>vertexCoords;

class uiElement
{
	unsigned int* parentScreenVBO;
	std::vector<Vertex>elementCoords;
public:
	std::vector<Vertex>getVerts()
	{
		return elementCoords;
	}

};