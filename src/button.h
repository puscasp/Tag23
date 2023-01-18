#ifndef BUTTON_H
#define BUTTON_H
#include <vector>
#include "types.h"

class button {
public:


	button(std::vector<Vertex> vertices, std::vector<Index> indices, Vertex newverts[]);

	bool isPressed(double x, double y);

	void setOnClick(void* f);

	void* getOnClick();

private:

	void* func;

	int containsVert(float* list, int listlen, float v);
};

#endif
