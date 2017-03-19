#include "Camera.h"

#include "rotate_vector.hpp"
#include <iostream>

glm::mat4 Camera::getViewMatrix()
{
	//std::cout << "pitch: " << pitch << "yaw: " << yaw << "\n";
	glm::vec3 front(0, 0, 1);
	front = glm::rotateY(front, glm::radians(pitch));
	front = glm::rotateX(front, glm::radians(yaw));
	front = glm::normalize(front);
	//std::cout << "pos: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
	//std::cout << "front: " << front.x << ", " << front.y << ", " << front.z << "\n";
	return glm::lookAt(pos, pos + front, up);
}
