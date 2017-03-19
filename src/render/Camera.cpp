#include "Camera.h"

#include "transform.hpp"

Camera::Camera(double x, double y, double z) : pos(x, y, z)
{
	
}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 cam = glm::translate(pos);
	return cam;
}
