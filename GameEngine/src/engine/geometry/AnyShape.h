#pragma once
#include "Geometry.h"
#include <vector>

namespace GameEngine 
{
	namespace Shape
	{
		class AnyShape : public GameEngine::Geometry
		{
		public:
			AnyShape(const glm::vec3& position, const std::string& filePath);
			AnyShape(float x, float y, float z, const std::string& filePath);

			void render(const GameEngine::Shader* shader) override;

		private:
			std::vector<float> _vertices{};
			std::vector<int> _indices{};

			void _readObjFile(const std::string& path);
		};
	}
}