#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "GameWindow.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main()
{
	GameWindow window(SCR_WIDTH, SCR_HEIGHT, "HelloShader");
	window.start();
    return 0;
}
