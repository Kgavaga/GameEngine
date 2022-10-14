#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
#include <thread>

namespace GameEngine 
{
	class Window
	{

	public:
		static Window		*pUserPointer;

		Window(const int width, const int height, const std::string& title);

		void				start();
		virtual void		onWindowSizeChange(GLFWwindow* window, int width, int height);
		virtual void		onMouseChange(GLFWwindow* window, double x, double y);

	protected:
		double				deltaTime;
		float				_lastMouseX;
		float				_lastMouseY;

		virtual void		onCreate();
		virtual void		onUpdate(float delta);
		virtual void		onDelete();
		virtual void		processInput(GLFWwindow* window);
		int					getWidth() const;
		int					getHeight() const;

	private:
		int					_width;
		int					_height;
		std::string			_title;
		GLFWwindow			*_pWindow;
		std::thread			*_pWindowLoop;
		double				_lastGlfwTime;

		void				_initWindow();
		void				_setStandardGlfwConfigurations() const;
		GLFWwindow			*_createGlfwWindow(const int width, const int height, const std::string& title) const;
		void				_loadGlad() const;
		void				_windowLoop();
	};

	void					glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void					mouse_callback(GLFWwindow* window, double xpos, double ypos);
}
