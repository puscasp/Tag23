#include <vector>;
#include<map>;
#include<shader.h>
#include <cstdlib>;
#include <GLFW\glfw3.h>
typedef struct {
	float x, y, r,g,b,a;

} Vertex;

typedef struct {
	unsigned int p1, p2, p3;
} Index;

typedef struct{
	float b, m, l;
	Vertex* v1, * v2;
} line;

typedef struct {
	Vertex v1, v2, v3;
} triangle;



typedef void** voidArray; //UsedN for input/output lists of unknown size/type
typedef void(*ocfunc)(voidArray, voidArray); 

typedef struct {
	std::vector<triangle> triList;
	ocfunc onClick;
	voidArray onClickInput;
	voidArray onClickOutput;

} uiElement;

typedef struct {
	std::vector<uiElement> elementList;
	GLuint VBO, VAO, EBO;
	std::map<Vertex, int> vertexIndexTable; 
	std::vector<int> indices;
	std::vector<Vertex> v;
	shader screenshader;
	//for rendering ONLY! for onclicks, iterate foreach uielement foreach triangle and check using angle trick

} screen;





//Comparison operator used to vertexIndexTable (std::map) to be able to compare elements. Obeys a Strict Weak Ordering.
inline
bool operator<(Vertex const& lhs, Vertex const& rhs) 
{
	return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}
