#include "../../../include/engine/scene/sceneManeger.h"
#include <memory>

void SceneManeger::init() {
  std::unique_ptr<MainMenuScene> main = std::make_unique<MainMenuScene>();
  scenes.push_back(std::move(main));
}
