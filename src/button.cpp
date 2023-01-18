
#include <stdlib.h>


#include "button.h"

button::button(std::vector<Vertex> verts, std::vector<Index> indices, Vertex newverts[]) {

	int numnewverts = sizeof(newverts) / sizeof(Vertex);


	/*
	* 
	* Adds verts to vert array, modifies indices accordingly.
	* 
		Please note: this entire idea is STUPID!! It is BAD PRACTICE to f around with memory using side effects, and logic using gotos.
		If there are problems it is because THE PROGRAMMER, (Paul Puscas), is a BABOON!!!!
	*/
	for (int j = 0; j < numnewverts; ++j) { //iterate through every new vertex


		for (int i = 0; i < verts.size(); ++i) { //compare to every old vertex
			if (verts[i].x == newverts[j].x && verts[i].y == newverts[j].y && verts[i].z == newverts[j].z) {

			//	indices.push_back(i);


				//++(*indlen);
				//indices = (int*)realloc(indices, sizeof(int) * (*indlen));
				//indices[*indlen - 1] = i;

				goto endloop; //bounce
			}
		}

		//the following only happen s if a given vertex is new:

		//++(*vertlen); 
		//verts = (float*)realloc(verts, sizeof(float) * (*vertlen));
		//verts[*vertlen - 1] = newverts[j];

		//++(*indlen);
		//indices = (int*)realloc(indices, sizeof(int) * (*indlen));
		//indices[*indlen - 1] = *vertlen;

	endloop:;
	}


	/*
	
	
	*/





}

void button::setOnClick(void* f) {
	func = &f;
}

void* button::getOnClick() {
	return func;
}

bool button::isPressed(double x, double y) {
	return false;
}


int button::containsVert(float* list, int listlen, float v) {
	for (int i = 0; i < listlen; ++i) {
		if (list[i] == v)
			return i;
	}

	return -1;
}