#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../glad/glad.h"
#include "../render/loadImage.h"
#include "../render/shaderManager.h"
#include "../render/textManeger.h"
#include "../window/window.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
struct RenderData {
  std::vector<float> SceneView;
  std::vector<unsigned int> SceneViewInd;
  int bufferEntry = 0;
  unsigned int bufferEntryInd = 0;
  glm::mat4 projection = 0;
  glm::mat4 view = 1.0f;
  float zoom = 1.0f;
  glm::mat4 model = glm::mat4(1.0f);
  glm::vec4 color;
  GLint projLoc = 0, colorLoc = 0, modelLoc = 0, scaleLoc = 0;
  GLuint VAO = 0, VBO = 0, EBO = 0;
  GLuint textureAtlas, shader;
};
struct SceneElement {
  float x = 0, y = 0;
  int spriteID = 0;
  int vecLoc = 0;
};
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
  virtual void PushTextToSceneView(std::string text, RenderData &uiTextData,
                                   SceneElement &element) = 0;
  virtual void PushToSceneView(SceneElement &, std::vector<float> &,
                               ImageLoader &, std::vector<unsigned int> &,
                               int &) = 0;
};

class MainMenuScene : public Scene {
public:
  std::vector<float> SceneView;
  std::vector<unsigned int> SceneViewInd;
  ShaderManeger &sh = ShaderManeger::getInstance();
  Text &tex = Text::getInstance();
  GameWindow &game = GameWindow ::getInstance();
  ImageLoader &loader = ImageLoader::getInstance();
  std::unordered_map<std::string, SceneElement> SceneObjects;
  int bufferEntry = 0;
  glm::mat4 projection;
  glm::mat4 view;
  float zoom = 1.0f;
  glm::mat4 model = glm::mat4(1.0f);
  glm::vec4 color;
  GLint projLoc, colorLoc, modelLoc, scaleLoc;
  GLuint VAO, VBO, EBO;

  RenderData UiLayerData;
  RenderData UiTextLayerData;
  MainMenuScene() {}
  ~MainMenuScene() = default;
  void renderer() override;
  void OnSceneLoad() override;
  void Update() override;
  void TickUpdate() override;
  void LateUpdate() override;
  void OnSceneEnd() override;
  void PushTextToSceneView(std::string text, RenderData &uiTextData,
                           SceneElement &element) override;
  void PushToSceneView(SceneElement &, std::vector<float> &, ImageLoader &,
                       std::vector<unsigned int> &, int &) override;
};
void FlushFrame(RenderData &data);

void BuildFrame(RenderData &data);

void BuildTextFrame(RenderData &data);
void FlushTextFrame(RenderData &data);
