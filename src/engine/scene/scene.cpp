#include "../../../include/engine/scene/scene.h"
#include <GLFW/glfw3.h>

void MainMenuScene::OnSceneLoad() {
  std::cout << "starting scene" << std::endl;
}
void MainMenuScene::renderer() {
  std::cout << "rendering mainmanu" << std::endl;
}
void MainMenuScene::Update() {
  std::cout << " updating main manue" << std::endl;
}
void MainMenuScene::TickUpdate() {
  std::cout << "ticked update main menu" << std::endl;
}
void MainMenuScene::LateUpdate() {
  std::cout << "lateupdate main menu" << std::endl;
}
void MainMenuScene::OnSceneEnd() {
  std::cout << "MainMenuScene end" << std::endl;
}
