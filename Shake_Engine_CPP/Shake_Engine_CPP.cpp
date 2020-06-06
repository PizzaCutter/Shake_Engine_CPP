#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char* argv[])
{
	// GLFW: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW: window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "SHAKE_ENGINE", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: load all openGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// LOAD SHADERS	
	Shader shader_01 = Shader("Shaders/shader01.vs", "Shaders/shader01.fs");
	Shader shader_02 = Shader("Shaders/shader01.vs", "Shaders/shader02.fs");

	// set-up vertex data and buffers and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Triangle1: bottom left 
		0.0f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,// Triangle1: bottom right 
		-0.25f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,// Triangle1: top

		0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,// Triangle2: bottom right
		0.25f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,// Triangle2: top

		0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f,// Triangle3: top
	};
	unsigned int indices[] = {
		0, 2, 1, // first triangle
		1, 4, 3, // second triangle
		5, 2, 4
	};

	float vertices_02[] = {
		0.0f, 0.5f, 0.0f,
		-0.25f, 0.0f, 0.0f,
		0.25f, 0.0f, 0.0f
	};
	unsigned int indices_02[] = {
		0, 1, 2
	};
	
	//VBO = vertex buffer object | VAO = vertex array object | EBO = element buffer object
	unsigned int VBO[2], VAO[2], EBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);

	glBindVertexArray(VAO[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//------------------------------------------------------
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_02), vertices_02, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_02), indices_02, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	
	int mode = 0;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		mode++;
		if(mode == 1)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else if(mode == 1000)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}else if(mode == 2000)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		mode = mode % 3000; 
		
		float timeValue = glfwGetTime();

		shader_01.use();
		shader_01.setFloat("ourVertexOffset", sin(timeValue) * 0.5f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shader_02.use();
		float redvalue = (cos(timeValue) / 2.0f) + 0.5f;
		float greenvalue = (sin(timeValue) / 2.0f) + 0.5f;
		shader_02.set4Float("ourColor", redvalue, greenvalue, 0.0f);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, EBO);

	glfwTerminate();
	return 0;
}
