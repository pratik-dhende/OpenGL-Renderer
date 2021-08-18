#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& textureImage) {
	std::cout << "Texture constructor." << std::endl;
	
	int width1, height1, numComponents1;

	// Flip the image on load.
	stbi_set_flip_vertically_on_load(1);

	// Load the image and store it in the form of unsigned char.
	stbi_uc* textureData1 = stbi_load(textureImage.c_str(), &width1, &height1, &numComponents1, 4);

	// Generate some space for textures in GPU.
	glGenTextures(1, &m_texture);

	// Bind the texture to the target.
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Set the parameter if pixel gets out of range.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis.

	// Set the parameters for magnification and minification.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification.

	if (textureData1 != NULL) {

		// Put the data into the the texture0.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);

		// Automatically generate mipmaps for the textures.
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "ERROR: FAILED TO LOAD THE IMAGE: " << textureImage << std::endl;
	}
	
	// Delete the image memory.
	stbi_image_free(textureData1);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);

	std::cout << "Texture destructor." << std::endl;
}

void Texture::bind(unsigned int unit) {
	// Set the active texture.
	glActiveTexture(GL_TEXTURE0 + unit);

	// Bind the active texture to the target.
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

