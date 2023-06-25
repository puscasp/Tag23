#include <stdlib.h>


void button(float* verts, int* vertlen, int* indices, int* indlen, float newverts[]) {

	int numnewverts = sizeof(newverts) / sizeof(float);


	/*
	* 
	* Adds verts to vert array, modifies indices accordingly.
	* 
		Please note: this entire idea is STUPID!! It is BAD PRACTICE to f around with memory using side effects, and logic using gotos.
		If there are problems it is because THE PROGRAMMER, (Paul Puscas), is a BABOON!!!!
	*/
	for (int j = 0; j < numnewverts; ++j) { //iterate through every new vertex


		for (int i = 0; i < *vertlen; ++i) { //compare to every old vertex
			if (verts[i] == newverts[j]) {

				++(*indlen);
				indices = (int*)realloc(indices, sizeof(int) * (*indlen));
				indices[*indlen - 1] = i;

				goto endloop; //bounce
			}
		}

		//the following only happen s if a given vertex is new:

		++(*vertlen); 
		verts = (float*)realloc(verts, sizeof(float) * (*vertlen));
		verts[*vertlen - 1] = newverts[j];

		++(*indlen);
		indices = (int*)realloc(indices, sizeof(int) * (*indlen));
		indices[*indlen - 1] = *vertlen;

		endloop: ;
        
	}


	/*
	
	
	*/





}




int main() {


    float* verts = malloc(sizeof(float)*4*3);
    int* indices = malloc(sizeof(int)*2*3);


    int vertlen = 12, indlen = 6;


    verts[0] = 0.5;
    verts[1] = 0.5;
    verts[2] = 0;
    verts[3] = 0.5;
    verts[4] = -0.5;
    verts[5] = 0;
    verts[6] = -0.5;
    verts[7] = -0.5;
    verts[8] = 0;
    verts[9] = -0.5;
    verts[10] = 0.5;
    verts[11] = 0;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    button(verts,vertlen,indices,indlen,{-0.5,-0.5,0,1,0.5,0});

    
}