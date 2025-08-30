#include "../../../include/engine/window/window.h"
#include <GLFW/glfw3.h>

GLFWwindow *GameWindow::getWindow() { return window; }

// loop conditions
void GameWindow::setWindow(bool v) { glfwSetWindowShouldClose(window, v); }
bool GameWindow::isOpen() const { return glfwWindowShouldClose(window); }

// get functions

int GameWindow::getHeight() { return width; }

int GameWindow::getWidth() { return height; }
