#ifndef CAMERA_H
#define CAMERA_H

#include "glm.hpp"

class Camera {
public:
	Camera(double x, double y, double z);
	~Camera();
	glm::mat4 getViewMatrix();
	void setPos(glm::vec3 in_pos) { pos = in_pos; };
	void increasePos(glm::vec3 in_pos) { pos += in_pos; };
private:
	glm::vec3 pos;
};

#endif
