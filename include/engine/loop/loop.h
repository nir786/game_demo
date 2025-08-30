#pragma once
#include "../window/window.h"
#include <GLFW/glfw3.h>
#include <iostream>
/// refrence to the function vectors
/// each function add funciton to the data.h
/// after that use the updateloop to call all the function inside that buffer

using cl = std::chrono::steady_clock;

class GameLoop {
public:
  static GameLoop &getInstance() {
    static GameLoop instance;
    return instance;
  }
  void run();
  void quit();

private:
  GameLoop() = default;
  ~GameLoop() { quit(); }

  void time_helper(cl::time_point &last, cl::time_point &now);

  void start();
  void update();
  void timedUpdate();
  void lateUpdate();
};
