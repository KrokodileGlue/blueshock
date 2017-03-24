#include "engine/io/TextureLoader.h"

#include "engine/Log.h"
#include "stb_image.h"

GLuint load_texture(const std::string& path)
{
	int width, height, bpp;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 3);
	if (!data) {
		log(LogLevel::WARNING) << "could not load image \"" << path << "\"";
		return -1;
	}

	log(LogLevel::DEBUG1) << "loading image \"" << path << "\", dimensions: " << width << ", " << height;

	GLuint id;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
	
	return id;
}
