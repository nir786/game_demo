#include "../../include/engine/loop/loop.h"
#include "../../include/engine/window/window.h"
#include "../../include/glad/glad.h"
#include <GLFW/glfw3.h>

int main() {
  auto &game = GameWindow::getInstance();
  auto &loop = GameLoop::getInstance();
  loop.run();

  return 0;
}
