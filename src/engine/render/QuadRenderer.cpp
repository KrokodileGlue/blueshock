#include "QuadRenderer.h"

#include <iostream>

QuadRenderer::QuadRenderer()
	: vertex_shader(GL_VERTEX_SHADER, "res/shader/quad_vert.txt", "quad renderer vertex shader"),
	fragment_shader(GL_FRAGMENT_SHADER, "res/shader/quad_frag.txt", "quad renderer fragment shader"),
	shader_program(vertex_shader, fragment_shader)
{
	glGenVertexArrays(1, &quad_VAO);
	glGenBuffers(1, &quad_VBO);

	GLfloat quad_vertices[] = {
		// Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	glBindVertexArray(quad_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void QuadRenderer::render(GLuint texture)
{
	glDisable(GL_DEPTH_TEST);

	shader_program.bind();

	glBindVertexArray(quad_VAO);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}
