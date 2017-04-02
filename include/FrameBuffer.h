#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "GL/glew.h"

class FrameBuffer {
	GLuint framebuffer_id, texture_id, renderbuffer_id;
	int width, height;
public:
	FrameBuffer(int width, int height);
	GLuint getTexture() {
		return texture_id;
	}
	void resize(int width_in, int height_in);
	void bind();
	void unbind();
};

#endif
