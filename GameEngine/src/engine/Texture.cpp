#include "Texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

GameEngine::Texture::Texture(const std::string& path, int format)
	:_path(path), _format(format)
{
	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(_path.c_str(), &_width, &_height, &_nrChannels, 0);
	if (_data) 
	{
		_id = _generate2dTexture();
		_initTextureOptions(); // No individuality possible
		glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _data);
		glGenerateMipmap(GL_TEXTURE_2D); // Should be an option
	}
	else
	{
		std::cout << "Couldn't load texture\n";
		exit(1);
	}
	stbi_image_free(_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int GameEngine::Texture::getId() const
{
	return _id;
}

void GameEngine::Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

unsigned int GameEngine::Texture::_generate2dTexture() const
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	return texture;
}

void GameEngine::Texture::_initTextureOptions() const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
