#pragma once

#include "../../glad/glad.h"
#include "../window/window.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <unordered_map>
class Scene {
protected:
  std::unordered_map<int, std::function<void()>> keybinds;

public:
  Scene() {}
  virtual ~Scene() = default;
  virtual void renderer() = 0;
  virtual void OnSceneLoad() = 0;
  virtual void Update() = 0;
  virtual void TickUpdate() = 0;
  virtual void LateUpdate() = 0;
  virtual void OnSceneEnd() = 0;
};

class MainMenuScene : public Scene {
public:
  MainMenuScene() {}
  ~MainMenuScene() = default;
  void renderer() override;
  void OnSceneLoad() override;
  void Update() override;
  void TickUpdate() override;
  void LateUpdate() override;
  void OnSceneEnd() override;
};

class WorldScene : public Scene {

public:
  void renderer() override;
  void OnSceneLoad() override;
  void Update() override;
  void TickUpdate() override;
  void LateUpdate() override;
  void OnSceneEnd() override;
};

class DungeonScene : public Scene {

public:
  void renderer() override;
  void OnSceneLoad() override;
  void Update() override;
  void TickUpdate() override;
  void LateUpdate() override;
  void OnSceneEnd() override;
};

class PauseScene : public Scene {

public:
  void renderer() override;
  void OnSceneLoad() override;
  void Update() override;
  void TickUpdate() override;
  void LateUpdate() override;
  void OnSceneEnd() override;
};
