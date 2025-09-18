#pragma once
#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
/// make macors for shader types

#define UI_SHADER 0
#define SPRITE_SHADER 1
#define UI_TEXT_SHADER 2
class ShaderManeger {
public:
  GLuint Shaders[3];

  static ShaderManeger &getInstance() {
    static ShaderManeger instance;
    return instance;
  }
  std::string LoadFile(const char *path);

  GLuint CompileShader(GLenum type, const char *source);
  GLuint CreateShaderProgram(const char *vertPath, const char *fragPath);
  void InitShaders();

private:
  ShaderManeger() = default;
};
