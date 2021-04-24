#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#pragma once
class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool isOpen() { return !shouldClose; }
	void closeWindow();
	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

    const std::array<bool, 1024> &getKeys();

    GLfloat getXChange();

    GLfloat getYChange();

private:
    //private data
	GLFWwindow* mainWindow;
    static bool shouldClose;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	std::array<bool, 1024> keys = {};
	//mouseData
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	//private functions
    void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double  xPos, double  yPos);
};