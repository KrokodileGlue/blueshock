#include "Renderer.h"

#include <sstream>
#include <iostream>

using namespace sia;

void Renderer::render(Model& model, Camera camera, glm::mat4 projection_matrix)
{
	shader_program.bind();
	shader_program.setUniformMatrix4fv("model_matrix", model.getModelMatrix());
	shader_program.setUniformMatrix4fv("view_matrix", camera.lookAt(glm::vec3(0, 7, 0)));
	shader_program.setUniformMatrix4fv("projection_matrix", projection_matrix);

	for (auto mesh : model.getMeshes()) {
		glBindVertexArray(mesh.getVAO());
		glEnableVertexAttribArray(0), glEnableVertexAttribArray(1), glEnableVertexAttribArray(3);

		std::vector<Texture> textures = mesh.getTextures();
		
		int num_diffuse = 0, num_specular = 0;
		for (unsigned int i = 0; i < textures.size(); i++) {
			int num = (textures[i].type == "texture_diffuse") ? num_diffuse++ : num_specular++;
			std::string uniform_name = textures[i].type + std::to_string(num);

			std::cout << "setting " << uniform_name << " to " << i << std::endl;

			shader_program.setUniform1i(uniform_name, i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glDrawElements(GL_TRIANGLES, mesh.getNumIndices(), GL_UNSIGNED_INT, 0);

		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glDisableVertexAttribArray(0), glDisableVertexAttribArray(1), glDisableVertexAttribArray(3);
		glBindVertexArray(0);
	}
}
