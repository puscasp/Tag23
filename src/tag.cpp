#include "graphicFunctions.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void click_callback(GLFWwindow* window, int button, int action, int mods);

void clickmanager(GLFWwindow* window, int button, int action, int mods);
void oc_test(voidArray inPtr, voidArray outPtr);
double x, y;
screen* activeScreen;


void test(double* a, double* b)
{

	std::cout << "X(t): " << *a << " Y(t): " << *b << std::endl;
}


int main() {


	std::cout << "fingo" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Tag23", NULL, NULL); //must make context AS SOON as window is made
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glViewport(0, 0, WIDTH, HEIGHT);


	Vertex v1 = { 0, 0, 0.5,0,0,1};
	Vertex v2 = { 0.5,0,0.5,0,0,1};
	Vertex v3 = { 0.5, 0.5,0.5,0,0,1};

	Vertex v4 = { -0.5, -0.5, 0, 0.5, 0, 1 };
	Vertex v5 = { -0.5, 0, 0, 0.5, 0, 1 };
	Vertex v6 = { -0.3, 0.3, 0, 0.5, 0, 1 };
	//unsigned int shad = generateShader("C:/Users/Paul/Desktop/Tag23/src/shaders/vtest.vs", "C:/Users/Paul/Desktop/Tag23/src/shaders/ftest.fs", NULL, NULL);


	shader testShader("C:/Users/Paul/Desktop/Tag23/src/shaders/vtest.vs", "C:/Users/Paul/Desktop/Tag23/src/shaders/ftest.fs", NULL, NULL);


	Vertex verts[] = { v1,v2,v3 };
	Vertex verts2[] = { v4, v5, v6 };
	screen testScreen = { {}, NULL, NULL, NULL, {}, {}, {} };

	void* inputs[2] = { &x, &y };

	testScreen.elementList.push_back(generateUiElement( verts, 3, NULL, oc_test, inputs, NULL));
	std::cout << "testse" << std::endl;
	testScreen.screenshader = testShader;


	//testScreen.elementList.push_back(generateUiElement(verts2, 3, NULL, NULL, NULL, NULL));
	activeScreen = &testScreen;
	glfwSetMouseButtonCallback(window,clickmanager);


	
	updateScreenDrawTable(activeScreen);
	buildScreenBuffers(activeScreen);

	for (int i = 0; i < activeScreen->v.size(); ++i)
		std::cout << i << ": " << activeScreen->v[i].x << " " << activeScreen->v[i].y << std::endl;

	for (int i = 0; i < activeScreen->indices.size(); ++i)
		std::cout << i << ": " << activeScreen->indices[i] << std::endl;



	while (!glfwWindowShouldClose(window)) {
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		testShader.use();

		updateScreenDrawTable(activeScreen);
		glBindVertexArray(activeScreen->VAO);
		glDrawElements(GL_TRIANGLES, activeScreen->indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	exit(0);
	
}

//NEW UTILS

void oc_test(voidArray inPtr, voidArray outPtr)
{
	std::cout << "X: " << *(double*)inPtr[0] << " Y: " << *(double*)inPtr[1] << std::endl  << std::endl;
	//std::cout << "finX: " << *(int*)inPtr[0] << " finY: " << *(int*)inPtr[1] << std::endl;
}



void clickmanager(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		glfwGetCursorPos(window, &x, &y);
		screen_onclick(activeScreen, x, y);
	}

}


//OLD UTILS
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



void click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		glfwGetCursorPos(window, &x, &y);
		std::cout << "X: " << x << " Y: " << y << std::endl;
		test(&x, &y);
	}

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
