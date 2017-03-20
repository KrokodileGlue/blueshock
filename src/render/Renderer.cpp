#include "Renderer.h"

#include <iostream>

void Renderer::render(const Model& model, Camera camera, glm::mat4 projection_matrix)
{
	shader_program.bind();
	shader_program.setUniformMatrix4fv("view_matrix", camera.getViewMatrix());
	shader_program.setUniformMatrix4fv("projection_matrix", projection_matrix);

	glBindVertexArray(model.model_id);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
