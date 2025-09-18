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
  std::cout << glGetString(GL_VENDOR) << std::endl;
  std::cout << glGetString(GL_RENDERER) << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;
  auto &game = GameWindow::getInstance();
  maneger.init();

  game.framebuffer_call_back(game.getWindow(), game.getWidth(),
                             game.getHeight());
  start();
  game.setWindow(true);
  maneger.scenes[maneger.currentScene]->OnSceneLoad();
  auto last = cl::now();

  //*****imgui
  //  glDisable(GL_CULL_FACE);
  // glDisable(GL_DEPTH_TEST);
  glViewport(0, 0, game.getWidth(), game.getHeight());
  while (game.isOpen()) {
    glfwPollEvents();
    auto now = cl::now();
    time_helper(last, now);
    maneger.scenes[maneger.currentScene]->Update();
    maneger.scenes[maneger.currentScene]->LateUpdate();
    glClear(GL_COLOR_BUFFER_BIT);
    maneger.scenes[maneger.currentScene]->renderer();
    glfwSwapBuffers(game.getWindow());
  }
}

void GameLoop::quit() {}

void GameLoop::start() {
  auto &atlas_maneger = ImageLoader::getInstance();
  atlas_maneger.Init_Atlas(atlas_maneger.player_atlas,
                           "/home/nir/demo/assetes/8d_charecter_proto.png");
  auto &shader_manager = ShaderManeger::getInstance();
  shader_manager.InitShaders();

  auto &text_maneger = Text::getInstance();
  text_maneger.Init_text();
}
