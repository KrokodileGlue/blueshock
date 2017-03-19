#include "util.h"
#include "Log.h"

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
				std::cerr << "file " << path << " could not be read." << std::endl;
			} else {
				buf[new_len++] = '\0';
			}
		}

		fclose(file);
	} else {
		std::cerr << "file " << path << " could not be opened." << std::endl;
		exit(EXIT_FAILURE);
	}

	return buf;
}

void blueshock_quit()
{
	log(LogLevel::INFO) << "shutting down";
	dump_log();
	exit(EXIT_SUCCESS);
}
