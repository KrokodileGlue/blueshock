#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "GL/glew.h"

class FrameBuffer {
	GLuint framebuffer_id, texture_id, renderbuffer_id;
	int width, height;
	bool is_multisampled;
public:
	FrameBuffer(int width, int height, bool is_multisampled);
	GLuint getTexture() {
		return texture_id;
	}
	void blit(FrameBuffer& rhs);
	void resize(int width_in, int height_in);
	void bind();
	void unbind();
};

#endif
