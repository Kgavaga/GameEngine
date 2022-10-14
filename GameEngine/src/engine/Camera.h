#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	class Camera
	{
	public:
		static const float STANDARD_YAW;

		Camera(const glm::vec3& position);

		void getViewMatrix(glm::mat4& vector) const;
		void rotate(float pitch, float yaw);
		void setRotation(float pitch, float yaw);
		void translate(float x, float y, float z);
		void setPosition(float x, float y, float z);
		void moveDirection(const glm::vec3& direction, float distance);
		void moveInCameraDirection(const glm::vec3& direction, float distance);

	protected:
	private:
		float _pitch;
		float _yaw;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;

		void _getDirectionVector(glm::vec3& vector, float pitch, float yaw);
	};
}