#include "util.h"
#include "Log.h"
#include "Display.h"

#include <matrix_transform.hpp>

char* load_file(const char* path)
{
	char* buf = NULL;
	FILE* file = fopen(path, "r");

	if (file) {
		if (fseek(file, 0L, SEEK_END) == 0) {
			long len = ftell(file);
			if (len == -1) return NULL;

			buf = (char*)malloc(len + 1);

			if (fseek(file, 0L, SEEK_SET) != 0)
				return NULL;

			size_t new_len = fread(buf, 1, len, file);
			if (ferror(file) != 0) {
				log(LogLevel::WARNING) << "attempted to load file \"" << path << "\" which could not be read";
				return NULL;
			} else {
				buf[new_len++] = '\0';
			}
		}

		fclose(file);
	} else {
		log(LogLevel::WARNING) << "attempted to load file \"" << path << "\" which could not be opened";
		return NULL;
	}

	return buf;
}

void blueshock_quit()
{
	log(LogLevel::INFO) << "shutting down";
	dump_log();
	exit(EXIT_SUCCESS);
}

glm::mat4 calc_projection_matrix(float fov, int width, int height)
{
	return glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 10.0f);
}
