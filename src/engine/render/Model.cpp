#include "glm/gtc/matrix_transform.hpp"

#include "Model.h"
#include "Log.h"

glm::mat4 Model::getModelMatrix()
{
	glm::mat4 res;

	res = glm::translate(res, pos);
	res = glm::scale(res, glm::vec3(scale));
	
	res = glm::rotate(res, glm::radians(rot.x), glm::vec3(1, 0, 0));
	res = glm::rotate(res, glm::radians(rot.y), glm::vec3(0, 1, 0));
	res = glm::rotate(res, glm::radians(rot.z), glm::vec3(0, 0, 1));

	return res;
}
