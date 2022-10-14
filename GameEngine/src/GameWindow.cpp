#include <iostream>
#include "GameWindow.h";
#include "engine/geometry/Geometry.h";
#include "engine/geometry/Cube.h";

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "engine/Texture.h"
#include "engine/geometry/AnyShape.h"
#include "engine/Camera.h"

const GameWindow::PROJECTION_TYPE GameWindow::DEFAULT_PROJECTION_TYPE = PROJECTION_TYPE::PERSPECTIVE;

GameWindow::GameWindow(const int width, const int height, const std::string& title)
	: Window(width, height, title), _pShader(nullptr), 
	_projectionType(DEFAULT_PROJECTION_TYPE),
	_view(1.0f), _projection(1.0f), _firstTimeUsingMouse(true)
{}

std::vector<GameEngine::Geometry*> cubes;
GameEngine::Shape::AnyShape* teapot;

GameEngine::Texture* texture;
GameEngine::Texture* texture2;

GameEngine::Camera* camera;

void GameWindow::onCreate()
{
	_initShader();
	_calculateProjectionMatrix();
	camera = new GameEngine::Camera(glm::vec3(0.0f));

	/*texture = new GameEngine::Texture("res/wall.jpg", GL_RGB);
	texture2 = new GameEngine::Texture("res/awesomeface.png", GL_RGBA);*/

	/*for (int i = 0; i < 5; i++) {
		cubes.push_back(new GameEngine::Shape::Cube(0.0f + i, 0.0f, -200.0f));
	}*/

	teapot = new GameEngine::Shape::AnyShape(0.0f, -3.0f, -5.0f, "res/mountains.obj");

	glEnable(GL_DEPTH_TEST);
}

glm::mat4 view = glm::mat4(1.0f);
void GameWindow::onUpdate(float deltaTime)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glActiveTexture(GL_TEXTURE0);
	texture->bindTexture();
	glActiveTexture(GL_TEXTURE1);
	texture2->bindTexture();*/

	_pShader->use();
	_pShader->setInt("texture1", 0);
	_pShader->setInt("texture2", 1);
	camera->getViewMatrix(view);
	_pShader->setMatrix4fv("view", glm::value_ptr(view), false);
	_pShader->setMatrix4fv("projection", glm::value_ptr(_projection), false);
	double currentTime = glfwGetTime();
	_pShader->setFloat("time", currentTime);

	//std::vector<GameEngine::Geometry*>::iterator iter;
	//for (iter = cubes.begin(); iter != cubes.end(); ++iter) {
	//	(*iter)->scale(1.0f, 1.0f, 1.0f);
	//	(*iter)->move(0.0f, 0.0f, -delta);
	//	(*iter)->render(_pShader);
	//	//cube->rotate(currentTime*100, 0.4f, 0.3f, 0.2f);
	//}
	
	//teapot->move(0.0f, 0.0f, -deltaTime);
	teapot->rotate(deltaTime , 0.0f, 1.0f, 0.0f);
	teapot->render(_pShader);
}
void GameWindow::onDelete()
{
}
void GameWindow::processInput(GLFWwindow* window)
{
	Window::processInput(window);
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) // Should be abstracted since this is exposing the window object
		glfwSetWindowShouldClose(window, 1);

	const float cameraSpeed = 50.0f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveInCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f), cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveInCameraDirection(glm::vec3(0.0f, 0.0f, -1.0f), cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveInCameraDirection(glm::vec3(1.0f, 0.0f, 0.0f), cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveInCameraDirection(glm::vec3(-1.0f, 0.0f, 0.0f), cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->translate(0.0f, -cameraSpeed, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->translate(0.0f, cameraSpeed, 0.0f);
}

void GameWindow::onWindowSizeChange(GLFWwindow* window, int width, int height)
{
	GameWindow::Window::onWindowSizeChange(window, width, height);
	_calculateProjectionMatrix();
}

void GameWindow::onMouseChange(GLFWwindow* window, double x, double y)
{
	if (_firstTimeUsingMouse) 
	{
		_lastMouseX = x;
		_lastMouseY = y;
		_firstTimeUsingMouse = false;
		return;
	}
	const float mouseSpeed = 10.0f * deltaTime; // adjust accordingly
	std::cout << x << y << "\n";
	float deltaX = _lastMouseX - x;
	float deltaY = _lastMouseY - y;

	camera->rotate(deltaY * mouseSpeed, -deltaX * mouseSpeed);

	_lastMouseX = x;
	_lastMouseY = y;
}

void GameWindow::setProjectionType(PROJECTION_TYPE projectionType)
{
	_projectionType = projectionType;
}

void GameWindow::_initShader()
{
	_pShader = new GameEngine::Shader("res/VertexShader.txt", "res/FragmentShader.txt");
}

void GameWindow::_calculateProjectionMatrix()
{
	switch (_projectionType) {
	case PROJECTION_TYPE::PERSPECTIVE:
		_projection = glm::perspective(glm::radians(90.0f), (float)getWidth() / (float)getHeight(), 0.1f, 500.0f);
		break;
	case PROJECTION_TYPE::ORTHOGRAPHIC:
		_projection = glm::ortho(0.0f, (float)getWidth() / 10, 0.0f, (float)getHeight() / 10, 0.1f, 500.0f);
		break;
	}
}