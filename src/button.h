#ifndef BUTTON_H
#define BUTTON_H


class button {
public:


	button(float* verts, int* vertlen, int* indices, int* indlen, float newverts[]);

	bool isPressed(double x, double y);

	void setOnClick(void* f);

	void* getOnClick();

private:

	void* func;

	int containsVert(float* list, int listlen, float v);
};

#endif
