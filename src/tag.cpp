#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

#include <shader.h>
#include <types.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void click_callback(GLFWwindow* window, int button, int action, int mods);
double x, y;


int main() {
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


	glViewport(0, 0, 800, 600);


	Vertex v1 = { 0.5, 0.5 };
	Vertex v2 = { 0.5, -0.5 };
	Vertex v3 = { -0.5, -0.5 };
	Vertex v4 = { -0.5, 0.5 };

	std::vector<Vertex> vertices = { v1, v2, v3, v4 };

	std::vector<unsigned int> indices = {
		0,1,3,
		1,2,3
	};

	/*
	Index i1 = { 0,1,3 };
	Index i2 = { 1,3,2 };


	std::vector<Index> indices = {i1,i2};
	*/


	/*float vertices[] =
	{
		0.5,0.5,0.0,
		0.5,-0.5,0.0,
		-0.5,-0.5,0.0,
		-0.5,0.5,0.0
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};*/




	/*
	VBO, VAO, EBO
	*/

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//what kind of magic
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbindes vbo (for what purpose?)
	glBindVertexArray(0); //unbindes vao (again, why?), and why not ebo?


	/*
	* SHADERS
	*/
	shader testShader("C:/Users/Paul/Desktop/Tag23/src/shaders/vtest.vs", "C:/Users/Paul/Desktop/Tag23/src/shaders/ftest.fs");



	/* ----------
	MOUSE INPUT
	*/
	
	glfwSetMouseButtonCallback(window, click_callback);


	/*
			RENDER LOOP BODY (per frame)
	*/
	while (!glfwWindowShouldClose(window)) {
		processInput(window);


		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Shading

		testShader.use();



		//Drawing
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate();
	return 0;
}

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
	}

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
