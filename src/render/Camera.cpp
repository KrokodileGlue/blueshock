#include "Camera.h"

#include "rotate_vector.hpp"
#include <iostream>

glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 front(0, 0, 1);
	front = glm::rotateY(front, glm::radians(pitch));
	front = glm::rotateX(front, glm::radians(yaw));
	front = glm::normalize(front);

	// NOTE: this needs to be changed back
	return glm::lookAt(pos, /*pos + front*/ glm::vec3(), up);
}
