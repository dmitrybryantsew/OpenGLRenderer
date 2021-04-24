#include "Window.hpp"
bool Window::shouldClose = false;
Window::Window()
{

	width = 800;
	height = 600;
	bufferWidth = 0, bufferHeight = 0;
    mainWindow = nullptr;


}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	bufferWidth = 0, bufferHeight = 0;
	mainWindow = nullptr;


}

int Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window properties

	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//allow modern extention features
	glewExperimental = GL_TRUE;
	// OpenGL profile without backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// OpenGL profile allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glViewport(0, 0, bufferWidth, bufferHeight);
	mainWindow = glfwCreateWindow(width, height, "Main window", nullptr, nullptr);
	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed...\n";
		glfwTerminate();
		return 1;
	}

	// OpenGL viewport dimensions
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//set callbacks
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed...\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        shouldClose = true;
    }

    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
        {
            thisWindow->keys[key] = true;
            std::cout << key << " was pressed\n";
        } else  if (action == GLFW_RELEASE){
            thisWindow->keys[key] = false;
            std::cout << key << " was released\n";
        }
    }
}

void Window::createCallbacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos) {
    auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(thisWindow->mouseFirstMoved)
    {
        thisWindow->lastX = xPos;
        thisWindow->lastY = yPos;
        thisWindow->mouseFirstMoved = false;
    }

    thisWindow->xChange = xPos - thisWindow->lastX;
    thisWindow->yChange = thisWindow->lastY - yPos;

    thisWindow->lastX = xPos;
    thisWindow->lastY = yPos;
}

const std::array<bool, 1024> &Window::getKeys() {
    return keys;
}

GLfloat Window::getXChange() {
    GLfloat oldXChange = xChange;
    xChange = 0;
    return oldXChange;
}

GLfloat Window::getYChange() {
    GLfloat oldYChange = yChange;
    yChange = 0;
    return oldYChange;
}

void Window::closeWindow() {
    glfwWindowShouldClose(mainWindow);
}


