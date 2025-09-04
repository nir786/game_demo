#include "../../../include/engine/loop/loop.h"
#include "../../../include/engine/scene/sceneManeger.h"
#include <chrono>

auto &maneger = SceneManeger::getInstance();
const double fixedStep = 1.0f / 60.0f;
double acc = 0.0f;
void GameLoop::time_helper(cl::time_point &last, cl::time_point &now) {
  now = cl::now();
  std::chrono::duration<double> dt = now - last; // deltatime
  last = now;
  acc += dt.count();
  if (acc >= fixedStep) {
    maneger.scenes[maneger.currentScene]->LateUpdate();
    acc -= fixedStep;
  }
}

void GameLoop::run() {

  auto &game = GameWindow::getInstance();
  maneger.init();
  start();
  game.setWindow(true);

  auto last = cl::now();
  //*****imgui
  auto &atlasmaneger = ImageLoader::getInstance();
  atlasmaneger.Init_Atlas(atlasmaneger.player_atlas,
                          "/home/nir/demo/assetes/8d_charecter_proto.png");

  while (game.isOpen()) {
    glfwPollEvents();
    auto now = cl::now();
    time_helper(last, now);
    maneger.scenes[maneger.currentScene]->Update();
    maneger.scenes[maneger.currentScene]->LateUpdate();
    maneger.scenes[maneger.currentScene]->renderer();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(game.getWindow());
  }
}
void GameLoop::quit() {}

void GameLoop::start() {}
