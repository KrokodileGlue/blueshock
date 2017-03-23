#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstdio>

#include "glm/glm.hpp"

namespace sia {

char* load_file(const char* path);
void quit();
glm::mat4 calc_projection_matrix(float fov, int width, int height);

}

#endif
