#include "Texture.h"


Texture::Texture()
{

}

Texture::~Texture()
{
    stbi_image_free(data);
}

Texture::Texture(const char* filepath)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_CLAMP_TO_BORDER (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!load_from_file(filepath))
		Tomxy::error("failed to load image");
}

bool Texture::load_from_file(const char* filepath)
{
	data = stbi_load(filepath, &width, &height, &nr_channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        return true;
    }
	else
		return false;
}

void Texture::bind_texture() const
{
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);
}