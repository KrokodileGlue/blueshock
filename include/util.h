#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstdio>

#include "glm/glm.hpp"

char* load_file(const char* path);
void blueshock_quit();
glm::mat4 calc_projection_matrix(float fov, int width, int height);

#endif
