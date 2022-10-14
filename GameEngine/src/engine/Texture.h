#pragma once
#include <string>

namespace GameEngine {
	class Texture
	{
	public:
		Texture(const std::string& path, int format);

		unsigned int getId() const;
		void bindTexture() const;
	protected:
	private:
		std::string _path;
		int _format;
		unsigned char* _data;
		int _width;
		int _height;
		int _nrChannels;
		unsigned int _id;

		unsigned int _generate2dTexture() const;
		void _initTextureOptions() const;
	};
}