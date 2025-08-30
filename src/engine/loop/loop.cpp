#include "../../../include/engine/loop/loop.h"
#include <chrono>

const double fixedStep = 1.0f / 60.0f;
double acc = 0.0f;
void GameLoop::time_helper(cl::time_point &last, cl::time_point &now) {
  now = cl::now();
  std::chrono::duration<double> dt = now - last; // deltatime
  last = now;
  acc += dt.count();
  if (acc >= fixedStep) {
    timedUpdate();
    acc -= fixedStep;
  }
}

void GameLoop::run() {
  auto &game = GameWindow::getInstance();
  start();
  game.setWindow(true);

  auto last = cl::now();

  double count;
  while (game.isOpen()) {
    auto now = cl::now();
    time_helper(last, now);

    update();

    lateUpdate();
    glfwSwapBuffers(game.getWindow());
    glfwPollEvents();
  }
}
void GameLoop::quit() {}

void GameLoop::start() {}
void GameLoop::update() {}
void GameLoop::timedUpdate() {}
void GameLoop::lateUpdate() {}
