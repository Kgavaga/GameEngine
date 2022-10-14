#pragma once
#include "engine/Window.h"
#include "engine/Shader.h"
#include <glm/glm.hpp>

class GameWindow : public GameEngine::Window {
public:
	static const enum class PROJECTION_TYPE
	{
		PERSPECTIVE, ORTHOGRAPHIC
	};
	static const PROJECTION_TYPE DEFAULT_PROJECTION_TYPE;

	GameWindow(const int width, const int height, const std::string& title);

	void onCreate() override;
	void onUpdate(float delta) override;
	void onDelete() override;
	void processInput(GLFWwindow* window) override;
	void onWindowSizeChange(GLFWwindow* window, int width, int height) override;
	void onMouseChange(GLFWwindow* window, double x, double y) override;
	void setProjectionType(PROJECTION_TYPE projectionType);

private:
	PROJECTION_TYPE _projectionType;
	GameEngine::Shader* _pShader;
	glm::mat4 _view;
	glm::mat4 _projection;
	bool _firstTimeUsingMouse;

	void _initShader();
	void _calculateProjectionMatrix();
};