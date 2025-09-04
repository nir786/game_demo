#pragma once

#include "../window/window.h"
#include "scene.h"
#include <memory>
#include <vector>
class SceneManeger {
public:
  int currentScene = 0;
  std::vector<std::unique_ptr<Scene>> scenes;

  static SceneManeger &getInstance() {
    static SceneManeger instance;
    return instance;
  }
  void init();

private:
  SceneManeger() = default;
};
