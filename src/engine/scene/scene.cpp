#include "../../../include/engine/scene/scene.h"
#include "../../../include/engine/render/macors.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void MainMenuScene::PushTextToSceneView(std::string text,
                                        RenderData &uiTextData,
                                        SceneElement &element) {
  tex.MakeString("Start", element.x, element.y, uiTextData.SceneView,
                 uiTextData.SceneViewInd, uiTextData.bufferEntryInd,
                 tex.monoFont);
}
void MainMenuScene::PushToSceneView(SceneElement &element,
                                    std::vector<float> &buffer,
                                    ImageLoader &loader,
                                    std::vector<unsigned int> &subbuffer,
                                    int &count) {
  loader.MakeQuad(element.x, element.y, 64.0f, 64.0f,
                  getSpriteUvs(element.spriteID), buffer);
  element.vecLoc = count * 4;
  loader.MakeQuadIndices((unsigned int)count * 4, subbuffer);
  count++;
  std::cout << count << ":bufferEntry" << std::endl;
}
/*push to scene view is a function that takes a buffer and pushes a sprite into
 * it it it also handles the subbuffer aka the indecies buffer and construct
 * something into it the point is to take some Scene element from the entity
 * arrey and render it
 * TODO if we have an entity arrey aka element render the entire list*/

void MainMenuScene::OnSceneLoad() {
  glGenVertexArrays(1, &UiLayerData.VAO);
  glGenBuffers(1, &UiLayerData.VBO);
  glGenBuffers(1, &UiLayerData.EBO);
  UiLayerData.shader = sh.Shaders[UI_SHADER];
  UiLayerData.textureAtlas = loader.player_atlas.id;
  UiLayerData.projLoc =
      glGetUniformLocation(sh.Shaders[UI_SHADER], "projection");
  UiLayerData.modelLoc = glGetUniformLocation(sh.Shaders[UI_SHADER], "model");
  UiLayerData.scaleLoc = glGetUniformLocation(sh.Shaders[UI_SHADER], "view");
  glGenVertexArrays(1, &UiTextLayerData.VAO);
  glGenBuffers(1, &UiTextLayerData.VBO);
  glGenBuffers(1, &UiTextLayerData.EBO);

  UiTextLayerData.shader = sh.Shaders[UI_TEXT_SHADER];
  UiTextLayerData.textureAtlas = tex.monoFont.AtlasID;
  UiTextLayerData.projLoc =
      glGetUniformLocation(sh.Shaders[UI_TEXT_SHADER], "projection");
  UiTextLayerData.scaleLoc =
      glGetUniformLocation(sh.Shaders[UI_TEXT_SHADER], "view");
  UiTextLayerData.colorLoc =
      glGetUniformLocation(sh.Shaders[UI_TEXT_SHADER], "textColor");

  view = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 1.0f));
  SceneElement button1;
  button1.spriteID = PLAYER_UP;
  button1.x = 64.0f;
  button1.y = 0.0f;
  PushToSceneView(button1, UiLayerData.SceneView, loader,
                  UiLayerData.SceneViewInd, UiLayerData.bufferEntry);

  SceneElement button2;
  button2.spriteID = PLAYER_UP;
  button2.x = 128.0f;
  button2.y = 0.0f;
  PushToSceneView(button2, UiLayerData.SceneView, loader,
                  UiLayerData.SceneViewInd, UiLayerData.bufferEntry);
  SceneElement buttontex;
  buttontex.spriteID = PLAYER_UP;
  buttontex.x = 0.0f;
  buttontex.y = 0.0f;
  PushToSceneView(buttontex, UiLayerData.SceneView, loader,
                  UiLayerData.SceneViewInd, UiLayerData.bufferEntry);
  SceneElement atlastext;
  atlastext.spriteID = FULL_TEXT_ATLAS;
  atlastext.x = 100.0f;
  atlastext.y = 100.0f;
  //  PushToSceneView(atlastext, UiLayerData.SceneView, loader,
  //                UiLayerData.SceneViewInd, UiLayerData.bufferEntry);
  SceneElement text;
  text.x = 100.0f;
  text.y = 100.0f;
  PushTextToSceneView("hello", UiTextLayerData, text);

  UiLayerData.projection = game.getProjection();
  UiTextLayerData.projection = game.getProjection();
}
/*onSceneLoad this is an extended function from the MainMenueScene its a
 * diffrent the reason why every scene has a inherited function for it is
 * because we want to be able to have a scripting lang and handle function calls
 * indevidually per scene such as every function that will have have the name
 * MainMenuOnLoad() in a lua script would be called here that way we keep it
 * modular also load is the first function to init parameter of the scene so
 * every init for parameters will be set here
 */
void MainMenuScene::renderer() {
  glClear(GL_COLOR_BUFFER_BIT);
  BuildFrame(UiLayerData);
  FlushFrame(UiLayerData);
  BuildTextFrame(UiTextLayerData);
  FlushTextFrame(UiTextLayerData);
  UiLayerData.projection = game.getProjection();
  UiTextLayerData.projection = game.getProjection();
}
/*the renderer function will hadnle our draw calls from the buffer this is the
 * last function that will be called in the loop it will render everything we
 * have in out buffer so updated logic moving parts will be rendered here */
void BuildFrame(RenderData &data) {

  glBindVertexArray(data.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
  glBufferData(GL_ARRAY_BUFFER, data.SceneView.size() * sizeof(float),
               data.SceneView.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               data.SceneViewInd.size() * sizeof(unsigned int),
               data.SceneViewInd.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}
/*build frame handles the building of the visual buffers that handles sprites
 * and other logic alike so well call build frame for each vbo each buffer for a
 * spasific element like an object uis and so on will be set each frame by this
 * call
 * TODO add build per paremeter to the function so we can call a spasific buffer
 * and set it */
void FlushFrame(RenderData &data) {
  glUseProgram(data.shader);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, data.textureAtlas);
  glUniform1i(glGetUniformLocation(data.shader, "atlas"), 0);
  //   std::cout << glm::to_string(game.getProjection()) << "renderer
  //   projection"
  //            << std::endl;
  glUniformMatrix4fv(data.projLoc, 1, GL_FALSE,
                     glm::value_ptr(data.projection));
  glUniformMatrix4fv(data.modelLoc, 1, GL_FALSE, glm::value_ptr(data.model));
  glUniformMatrix4fv(data.scaleLoc, 1, GL_FALSE, glm::value_ptr(data.view));
  glBindVertexArray(data.VAO);

  glDrawElements(GL_TRIANGLES, data.SceneViewInd.size(), GL_UNSIGNED_INT, 0);
}
/*flushframe is our actuall render it will flush whatever we passed to the
 * graphics card and flush it onto the screen */
void FlushTextFrame(RenderData &data) {
  glUseProgram(data.shader);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, data.textureAtlas);
  glUniform1i(glGetUniformLocation(data.shader, "atlas"), 0);
  glUniformMatrix4fv(data.projLoc, 1, GL_FALSE,
                     glm::value_ptr(data.projection));
  glUniform3fv(data.colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
  glUniformMatrix4fv(data.scaleLoc, 1, GL_FALSE, glm::value_ptr(data.view));
  glBindVertexArray(data.VAO);
  glDrawElements(GL_TRIANGLES, data.SceneViewInd.size(), GL_UNSIGNED_INT, 0);
}
int count = 0, countt = 0;
void BuildTextFrame(RenderData &data) {
  if (count == 0) {
    for (auto &a : data.SceneView) {

      std::cout << a << std::endl;

      count++;
    }
    std::cout << " " << std::endl;
  }
  if (countt == 0) {
    for (auto &a : data.SceneViewInd) {
      std::cout << a << std::endl;
      countt++;
    }
  }
  glBindVertexArray(data.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
  glBufferData(GL_ARRAY_BUFFER, data.SceneView.size() * sizeof(float),
               data.SceneView.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4,
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               data.SceneViewInd.size() * sizeof(unsigned int),
               data.SceneViewInd.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}
void MainMenuScene::Update() {}
/*this one is diffrent then the ticked update becuase there is no delta time
 * applied into it if we wanna set a timer or gather input it will be here also
 * collision we want responsiveness rather this will be called more often then
 * ticked update also in the scriping MainMenuUpdate()*/
void MainMenuScene::TickUpdate() {}
/*ticked update is locked to 60 fps this function will be called 60 times per
 * second it nullifies the need for delta time any calculations that would
 * require delta time would be called from here */
void MainMenuScene::LateUpdate() {}
/*late update is the same as update but will be called after late update if we
 * ever wanna apply something later like ui clicks and things like that it would
 * end up here */
void MainMenuScene::OnSceneEnd() {}
/*this function should free all the heap data we initialized in the onSceneLoad
 */
