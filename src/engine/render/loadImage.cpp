#include "../../../include/engine/render/loadImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../include/engine/stb_image.h"
#include <GL/gl.h>
void ImageLoader::Init_Atlas(Atlas &atlas, const char *path) {
  int channels;
  unsigned char *data =
      stbi_load(path, &atlas.width, &atlas.height, &channels, 4);

  if (!data) {
    std::cerr << "Faild to load atlas\n"
              << path << "\n"
              << stbi_failure_reason() << std::endl;
    exit(1);
  }

  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas.width, atlas.height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

} // load from set path
