#include <iostream>

#include "glm/gtx/rotate_vector.hpp"

#include "Camera.h"

glm::mat4 Camera::lookAt(glm::vec3 place)
{
	glm::vec3 front(0, 0, 1);
	front = glm::rotateY(front, glm::radians(pitch));
	front = glm::rotateX(front, glm::radians(yaw));
	front = glm::normalize(front);

	return glm::lookAt(pos, place, up);
}

glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 front(0, 0, 1);
	front = glm::rotateY(front, glm::radians(pitch));
	front = glm::rotateX(front, glm::radians(yaw));
	front = glm::normalize(front);

	return glm::lookAt(pos, pos + front, up);
}
