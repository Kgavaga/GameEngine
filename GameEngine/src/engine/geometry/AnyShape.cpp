#include "AnyShape.h"
#include <strstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

GameEngine::Shape::AnyShape::AnyShape(const glm::vec3& position, const std::string& filePath)
	: GameEngine::Geometry(position)
{
	_readObjFile(filePath);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(float), &_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(int), &_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GameEngine::Shape::AnyShape::AnyShape(float x, float y, float z, const std::string& filePath)
	:GameEngine::Shape::AnyShape(glm::vec3(x, y, z), filePath)
{
}

void GameEngine::Shape::AnyShape::render(const GameEngine::Shader* shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	GameEngine::Geometry::_calculateModelMatrix(model);
	shader->setMatrix4fv(GameEngine::Shader::MODEL_MATRIX_ATTRIBUTE_NAME, glm::value_ptr(model), false);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size()*2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void GameEngine::Shape::AnyShape::_readObjFile(const std::string& filePath)
{
	std::ifstream objFile;
	// ensure ifstream objects can throw exceptions:
	objFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		objFile.open(filePath);
		// read file's buffer contents into streams
		char line[128];
		while (!objFile.eof()) {
			objFile.getline(line, 128);
			std::strstream s;
			s << line;

			char junk;
			if (line[0] == 'v')
			{
				float v[3];
				s >> junk >> v[0] >> v[1] >> v[2];
				_vertices.push_back(v[0]);
				_vertices.push_back(v[1]);
				_vertices.push_back(v[2]);
			}

			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				_indices.push_back(f[0]-1);
				_indices.push_back(f[1]-1);
				_indices.push_back(f[2]-1);
			}
		}
		// close file handlers
		objFile.close();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::ANYSHAPE::FILE_NOT_SUCCESFULLY_READ: " << e.what() << "\n Maybe a newline at the very end of the file caused this error.\n";
		exit(1);
	}
}
