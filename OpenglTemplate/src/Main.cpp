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
#include "Texture.h"




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK)
		std::cout << "error in glew" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	{	/* Loop until the user closes the window */
		GLfloat vertix[] = {
			-0.5f,-0.5f,0.0f, 0.0f,0.0f,
			0.5f,-0.5f,0.0f,  1.0f,0.0f,
			0.5f,0.5f,0.0f,   1.0f,1.0f,
			-0.5f,0.5f,0.0f,  0.0f,1.0f

		};
		GLuint indecies[] =
		{
			0,1,2,
			2,3,0

		};

		VertexArray va;
		VertexBuffer vb(vertix, sizeof(vertix));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indecies, 6);

		
	
	

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

		Texture tex("res/Textures/tex.png");
		tex.Bind();
		shader.Bind();
		shader.SetUniformMat4f("MVP", MVP);	
		shader.Unbind();
		Renderer renderer;
		float color_inc = 0.1;
		float red = 0.3,bg=0.5,a=1;
		int cnt = 0;
		while (!glfwWindowShouldClose(window))
		{
			cnt++;
			if(!(cnt%400))
			red += color_inc;
			if (red > 1)
				red = 0;
			/* Render here */
			renderer.Clear();

			
			va.Bind();
			ib.Bind();
			
			shader.Bind();
			shader.SetUniformMat4f("MVP", MVP);
			glUniform1i(shader.GetUniformLocation("u_texture"),0);
			//shader.SetUniformElements("color", 0.5f, 0.2f, 0.1f, 1.0f); //gives error
			
		//	glUniform4f(shader.GetUniformLocation("color"), red, bg, bg, a);
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