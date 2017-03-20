#ifndef MODEL_H
#define MODEL_H

#include "GL/glew.h"

class Model {
public:
	Model(GLfloat vertices[], int num_vertices, GLuint indices[], int num_indices);
	~Model();
	GLuint model_id, vbo, ebo;
	int num_indices, num_vertices;
};

#endif
