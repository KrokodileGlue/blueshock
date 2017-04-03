#include "FrameBuffer.h"

#include "Log.h"

FrameBuffer::FrameBuffer(int width, int height, bool is_multisampled) :
	width(width),
	height(height),
	is_multisampled(is_multisampled)
{
	log(LogLevel::INFO) << "creating a frame buffer object (" << width << ", " << height << "): is multisampled? " << (is_multisampled ? "yes" : "no");

	glGenTextures(1, &texture_id);

	glGenFramebuffers(1, &framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (is_multisampled) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture_id, 0);

		glGenRenderbuffers(1, &renderbuffer_id);

		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_id);
	} else {
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);

		glGenRenderbuffers(1, &renderbuffer_id);
		
		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_id);
	}

	GLint stat;
	
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &stat);
	log(LogLevel::DEBUG2) << "GL_RENDERBUFFER_SAMPLES: " << std::to_string(int(stat));

	glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_SAMPLES, &stat);
	log(LogLevel::DEBUG2) << "GL_TEXTURE_SAMPLES: " << std::to_string(int(stat));

	std::string error_str = "";
	bool error_occurred = true;
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch (status) {
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		error_str = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		error_str = "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		error_str = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		error_str = "GL_FRAMEBUFFER_UNSUPPORTED";
		break;
	case GL_FRAMEBUFFER_COMPLETE:
		error_str = "GL_FRAMEBUFFER_COMPLETE";
		error_occurred = false;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		error_str = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
		break;
	default:
		error_str = "unknown error status: " + std::to_string(int(status));
		break;
	}

	if (error_occurred)
		log(LogLevel::WARNING) << "could not create framebuffer object: " << error_str;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::resize(int width_in, int height_in)
{
	width = width_in, height = height_in;
	
	if (is_multisampled) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	} else {
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::blit(FrameBuffer& rhs)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer_id);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, rhs.framebuffer_id);

	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT */, GL_NEAREST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}
