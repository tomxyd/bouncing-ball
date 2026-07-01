#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <glad/glad.h>
#include "helper_library.h"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(const char* filepath);
	void bind_texture() const;
private:
	bool load_from_file(const char* filepath);
	int width{};
	int height{};
	int nr_channels{};
	unsigned int texture{};
	unsigned char* data = NULL;

};

#endif