#pragma once

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <mutex>
#include <string>
using namespace std;

class GameWindow {
public:
  static GameWindow &getInstance(int w = 800, int h = 600,
                                 const std::string &title = "demo") {
    static GameWindow instance(w, h, title);

    return instance;
  }

  GLFWwindow *getWindow();
  int getHeight();
  int getWidth();
  void setCallBack();
  bool isOpen() const;
  void setWindow(bool v);

private:
  GameWindow(int w, int h, const string &title) {
    if (!glfwInit()) {
      cerr << "Failed to init glfw" << endl;
    }

    window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (window == NULL) {
      cout << "Failed to init GLFW window" << endl;
      return;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      cout << "Failed to initialize GLAD" << endl;
      return;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, int ww, int hh) {
      auto &self = GameWindow::getInstance();
      self.width = ww;
      self.height = hh;
      glViewport(0, 0, ww, hh);
    });

    width = w;
    height = h;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
  }

  ~GameWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
  };

  GLFWwindow *window;
  int width, height;
};
