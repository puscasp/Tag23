#define _USE_MATH_DEFINES
#define WIDTH 800
#define HEIGHT 600

#include <types.h>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


//Geometry Utils
line drawline(Vertex v1, Vertex v2);
triangle makeTriangle(Vertex v1, Vertex v2, Vertex v3);
bool containsPoint(triangle t, Vertex v);
Vertex normalizeCoords(Vertex v);

//Screen
void screen_onclick(screen* s, int x, int y);
void updateScreenDrawTable(screen* s, bool wipe = false);
void buildScreenBuffers(screen* s);

//UiElement
uiElement generateUiElement(Vertex verts[], int nverts, unsigned int* s, ocfunc ocptr, voidArray in, voidArray out);


//Shaders
unsigned int generateShader(const char* vPath, const char* fPath, void* vArgs, void* fArgs);
void activateShaders(screen* s);
