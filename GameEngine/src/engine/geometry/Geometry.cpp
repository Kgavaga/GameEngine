#include "Geometry.h"

GameEngine::Geometry::Geometry(const glm::vec3& position)
	:_vao(0), _vbo(0), _ebo(0), _position(position),
	_scale(1.0f), _rotation(0.0f), _rotationDirection(1.0f)
{}

GameEngine::Geometry::Geometry(float x, float y, float z)
	:GameEngine::Geometry(glm::vec3(x,y,z))
{
}

GameEngine::Geometry::~Geometry()
{
}

void GameEngine::Geometry::_calculateModelMatrix(glm::mat4& modelMatrix) const
{
	modelMatrix = glm::translate(modelMatrix, _position);
	modelMatrix = glm::scale(modelMatrix, _scale);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation), _rotationDirection);
}

void GameEngine::Geometry::scale(float x, float y, float z)
{
	setScale(_scale.x + x, _scale.y + y, _scale.z + z);
}

void GameEngine::Geometry::setScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}

void GameEngine::Geometry::rotate(float rotation, float x, float y, float z)
{
	setRotation(_rotation + rotation, x, y, z);
}

void GameEngine::Geometry::setRotation(float rotation, float x, float y, float z)
{
	_rotation = rotation;
	_rotationDirection.x = x;
	_rotationDirection.y = y;
	_rotationDirection.z = z;
}

void GameEngine::Geometry::move(float x, float y, float z)
{
	setPosition(_position.x + x, _position.y + y, _position.z + z);
}

void GameEngine::Geometry::setPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}
