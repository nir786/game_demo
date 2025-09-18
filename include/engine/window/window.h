#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
  void framebuffer_call_back(GLFWwindow *, int ww, int hh) {
    auto &self = GameWindow::getInstance();
    std::cout << "projection call" << std::endl;
    self.width = ww;
    self.height = hh;
    glViewport(0, 0, ww, hh);

    float aspect = (float)self.width / (float)self.height;
    float aspectw = (float)self.height / (float)self.width;
    self.projection = glm::ortho(0.0f, (float)self.width, (float)self.height,
                                 0.0f, -1.0f, 1.0f);
  }

  GLFWwindow *getWindow();
  int getHeight();
  int getWidth();
  void setCallBack();
  bool isOpen() const;
  void setWindow(bool v);
  glm::mat4 getProjection() { return this->projection; }

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
      std::cout << "projection call" << std::endl;
      self.width = ww;
      self.height = hh;
      glViewport(0, 0, ww, hh);

      float aspect = (float)self.width / (float)self.height;
      float aspectw = (float)self.height / (float)self.width;
      self.projection = glm::ortho(0.0f, (float)self.width, (float)self.height,
                                   0.0f, -1.0f, 1.0f);
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
  glm::vec2 clip;
  GLFWwindow *window;
  int width, height;
  glm::mat4 projection;
};
