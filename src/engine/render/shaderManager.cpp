#include "../../../include/engine/render/shaderManager.h"
#include <fstream>
#include <sstream>

std::string ShaderManeger::LoadFile(const char *path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Failed to load file\n" << path << std::endl;
  }
  std::stringstream buf;
  buf << file.rdbuf();
  return buf.str();
}

GLuint ShaderManeger::CompileShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shader, 512, nullptr, log);
    std::cerr << "Shader compile error:\n" << log << std::endl;
  }
  return shader;
}
GLuint ShaderManeger::CreateShaderProgram(const char *vertPath,
                                          const char *fragPath) {
  std::string vCode = LoadFile(vertPath);
  std::string fCode = LoadFile(fragPath);

  GLuint vShader = CompileShader(GL_VERTEX_SHADER, vCode.c_str());
  GLuint fShader = CompileShader(GL_FRAGMENT_SHADER, fCode.c_str());

  GLuint program = glCreateProgram();
  glAttachShader(program, vShader);
  glAttachShader(program, fShader);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(program, 512, nullptr, log);
    std::cerr << "Failed to link program \n" << log << std::endl;
  }
  glDeleteShader(vShader);
  glDeleteShader(fShader);

  return program;
}
void ShaderManeger::InitShaders() {

  Shaders[UI_SHADER] = CreateShaderProgram("/home/nir/demo/shaders/ui.vert",
                                           "/home/nir/demo/shaders/ui.frag");
  Shaders[UI_TEXT_SHADER] =
      CreateShaderProgram("/home/nir/demo/shaders/text/text.vert",
                          "/home/nir/demo/shaders/text/text.frag");
  std::cout << "ui shader : " << Shaders[UI_SHADER] << std::endl;
}
