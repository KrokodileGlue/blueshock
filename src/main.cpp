#define GLEW_STATIC

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Display.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Log.h"
#include "util.h"
#include "Camera.h"

int main(int argc, char* argv[])
{
	Display display(512, 512);
	
	glewExperimental = GL_TRUE;
	glewInit();

	Shader vert_shader(GL_VERTEX_SHADER, "res/shader/vert_shader.txt", "vertex shader");
	Shader frag_shader(GL_FRAGMENT_SHADER, "res/shader/frag_shader.txt", "fragment shader");
	ShaderProgram shader_program(vert_shader, frag_shader);
	Camera camera(0, 0, 0);

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float delta = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		camera.setPos(glm::vec3(sin(delta), 0.0, 0.0));
		display.update();

		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
		
		shader_program.bind();
		shader_program.setUniformMatrix4fv("view_matrix", camera.getViewMatrix());
		shader_program.setUniformMatrix4fv("projection_matrix", calc_projection_matrix(45.0f));
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		delta += 0.1;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	blueshock_quit();
	
	return 0;
}
