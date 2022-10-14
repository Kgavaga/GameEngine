#include "Cube.h"
#include <glad/glad.h>
#include "stb_image.h"
#include "../Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GameEngine::Shape::Cube::Cube()
	: GameEngine::Shape::Cube(0.0f, 0.0f, 0.0f)
{
}

GameEngine::Shape::Cube::Cube(const glm::vec3& position)
	: GameEngine::Geometry(position)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GameEngine::Shape::Cube::Cube(float x, float y, float z)
	:GameEngine::Shape::Cube(glm::vec3(x,y,z))
{
}

void GameEngine::Shape::Cube::render(const GameEngine::Shader* shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	GameEngine::Geometry::_calculateModelMatrix(model);
	shader->setMatrix4fv(GameEngine::Shader::MODEL_MATRIX_ATTRIBUTE_NAME, glm::value_ptr(model), false);

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
