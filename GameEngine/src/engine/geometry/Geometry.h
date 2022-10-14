#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Shader.h"

namespace GameEngine {
	class Geometry {
	public:
		Geometry(const glm::vec3& position);
		Geometry(float x, float y, float z);

		~Geometry();

		virtual void render(const GameEngine::Shader* shader) = 0;
		void scale(float x, float y, float z);
		void setScale(float x, float y, float z);
		void rotate(float rotation, float x, float y, float z);
		void setRotation(float rotation, float x, float y, float z);
		void move(float x, float y, float z);
		void setPosition(float x, float y, float z);

	protected:
		unsigned int _vao, _vbo, _ebo;
		glm::vec3 _scale;
		float _rotation;
		glm::vec3 _rotationDirection;
		glm::vec3 _position;

		void _calculateModelMatrix(glm::mat4& modelMatrix) const;
	private:
	};
}