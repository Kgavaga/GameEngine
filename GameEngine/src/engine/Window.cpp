#include "Window.h"
#include <iostream>
#include <thread>

namespace GameEngine
{
	Window* Window::pUserPointer = nullptr;

	Window::Window(const int width, const int height, const std::string& title)
		: _width(width), _height(height), _title(title), _pWindow(nullptr), 
		_pWindowLoop(nullptr), _lastGlfwTime(0.0), deltaTime(0),
		_lastMouseX(0), _lastMouseY(0)
	{
		pUserPointer = this;
	}

	void Window::start()
	{
		_pWindowLoop = new std::thread(&Window::_windowLoop, this);
		_pWindowLoop->join();
	}


	void Window::onWindowSizeChange(GLFWwindow* window, int width, int height)
	{
		_width = width;
		_height = height;
		glViewport(0, 0, _width, _height);
	}

	void Window::onMouseChange(GLFWwindow* window, double x, double y)
	{
		return;
	}

	void Window::onCreate()
	{
		return;
	}

	void Window::onUpdate(float delta)
	{
		return;
	}

	void Window::onDelete()
	{
		return;
	}

	void Window::processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, 1);
	}

	int Window::getWidth() const
	{
		return _width;
	}

	int Window::getHeight() const
	{
		return _height;
	}

	void Window::_initWindow()
	{
		glfwInit();
		_setStandardGlfwConfigurations();
		_pWindow = _createGlfwWindow(_width, _height, _title);
		// Make the context of the window the main context on the current thread
		glfwMakeContextCurrent(_pWindow);
		_loadGlad();
		// Configure the callback function for updating the viewport whenever the size of the window changes
		// (must be run after GLAD since the callback function is immediately called and contains a opengl function)
		glfwSetFramebufferSizeCallback(_pWindow, glfwFramebufferSizeCallback);

		glfwSetCursorPosCallback(_pWindow, mouse_callback);
		glfwSetInputMode(_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::_setStandardGlfwConfigurations() const
	{
		// Configure GLFW that it knows that opengl version 3 is being used
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Configure GLFW that it knows the Core Profile is being used
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	GLFWwindow* Window::_createGlfwWindow(const int width, const int height, const std::string& title) const
	{
		// Create a new window
		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			exit(1);
		}
		return window;
	}

	void Window::_loadGlad() const
	{
		// Let GLAD load the address of the OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout <<  "Failed to initialize GLAD\n";
			exit(1);
		}
	}

	void Window::_windowLoop()
	{
		_initWindow();

		onCreate();

		while (!glfwWindowShouldClose(_pWindow))
		{
			processInput(_pWindow);

			double currentGlfwTime = glfwGetTime();
			deltaTime = currentGlfwTime - _lastGlfwTime;
			onUpdate(deltaTime);
			_lastGlfwTime = currentGlfwTime;

			glfwSwapBuffers(_pWindow);
			glfwPollEvents();
		}
		glfwTerminate();

		onDelete();
	}


	void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		GameEngine::Window::pUserPointer->onWindowSizeChange(window, width, height);
	}
	
	void mouse_callback(GLFWwindow* window, double x, double y)
	{
		GameEngine::Window::pUserPointer->onMouseChange(window, x, y);
	}
}