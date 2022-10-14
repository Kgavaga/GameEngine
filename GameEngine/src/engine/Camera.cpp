#include "Camera.h"
#include <glm/trigonometric.hpp>

const float GameEngine::Camera::STANDARD_YAW = -90.0f;

GameEngine::Camera::Camera(const glm::vec3& position)
	: _pitch(0.0f), _yaw(STANDARD_YAW),
	_cameraPos(position), _cameraFront(0.0f, 0.0f, -1.0f),
	_cameraUp(0.0f, 1.0f, 0.0f)
{
}

void GameEngine::Camera::getViewMatrix(glm::mat4& matrix) const
{
	matrix = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

void GameEngine::Camera::rotate(float pitch, float yaw)
{
	setRotation(_pitch + pitch, _yaw + yaw);
}

void GameEngine::Camera::setRotation(float pitch, float yaw)
{
	_pitch = pitch;
	_yaw = yaw;
	if (_pitch > 89.0f) 
	{
		_pitch = 89.0f;
	}
	else if(_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}
	_getDirectionVector(_cameraFront, _pitch, _yaw);
}

void GameEngine::Camera::translate(float x, float y, float z)
{
	setPosition(_cameraPos.x + x, _cameraPos.y + y, _cameraPos.z + z);
}

void GameEngine::Camera::setPosition(float x, float y, float z)
{
	_cameraPos.x = x;
	_cameraPos.y = y;
	_cameraPos.z = z;
}

void GameEngine::Camera::moveDirection(const glm::vec3& direction, float distance)
{
}

void GameEngine::Camera::moveInCameraDirection(const glm::vec3& direction, float distance)
{
	glm::vec3 right = glm::cross(_cameraFront, _cameraUp);
	glm::vec3 up = glm::cross(right, _cameraFront);
	glm::vec3 normDirection = glm::normalize(
		direction.x * right + direction.y * up + direction.z * _cameraFront);
	_cameraPos += normDirection * distance;
}

void GameEngine::Camera::_getDirectionVector(glm::vec3& vector, float pitch, float yaw)
{
	vector = glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);
}

