#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

namespace sia {

class Camera {
public:
	Camera(double x, double y, double z) : pos(x, y, z) {}

	glm::mat4 getViewMatrix();
	glm::mat4 lookAt(glm::vec3 place);
	void setPos(glm::vec3 in_pos) { pos = in_pos; };
	void increasePos(glm::vec3 in_pos) { pos += in_pos; };

	float yaw = 0.0f, pitch = 0.0f;
private:
	glm::vec3 pos, up = glm::vec3(0, 1, 0), right = glm::vec3(1, 0, 0);
};

}

#endif
