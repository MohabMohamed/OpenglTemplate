#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	
	window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "error in glew" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	{	/* Loop until the user closes the window */
		GLfloat vertix[] = {
			0.0f,1.0f,0.0f,
			1.0f,0.0f,0.0f,
			-1.0f,0.0f,0.0f,


		};
		GLuint indecies[] =
		{
			0,1,2

		};

		VertexArray va;
		VertexBuffer vb(vertix, sizeof(vertix));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indecies, 3);


		glm::mat4 ModelMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
		glm::mat4 MVP;
		unsigned int MatID;
		
		Shader shader("res/Shaders/Basic.shader");
		
		
		
		glm::mat4 translateMat = glm::translate(0.5f, -0.5f, 0.0f);
		glm::mat4 scaleMat = glm::scale(0.3f, 0.3f, 0.0f);

		ModelMatrix = translateMat* scaleMat;
		ViewMatrix = glm::lookAt(
			glm::vec3(0.0f, 0.5f, 3),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0, 1, 0)
		);
		ProjectionMatrix = glm::perspective(
			45.0f, 4.0f / 3.0f, 1.0f, 100.0f);
		MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;
		shader.Bind();
		shader.SetUniformMat4f("MVP", MVP);	
		shader.Unbind();
		Renderer renderer;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			//glDrawArrays(GL_TRIANGLES,0,3*6*6);

			
			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		
	}
	glfwTerminate();
	return 0;
}