#include "Renderer.h"

#include <iostream>

void Renderer::render(Model& model, Camera camera, glm::mat4 projection_matrix)
{
	shader_program.bind();
	shader_program.setUniformMatrix4fv("view_matrix", camera.getViewMatrix());
	shader_program.setUniformMatrix4fv("projection_matrix", projection_matrix);

	for (auto mesh : model.getMeshes()) {
		glBindVertexArray(mesh.getVAO());
		glDrawElements(GL_TRIANGLES, mesh.getNumIndices(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
