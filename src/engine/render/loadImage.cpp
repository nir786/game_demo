#include "../../../include/engine/render/loadImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../include/engine/stb_image.h"
#include <GL/gl.h>
void ImageLoader::Init_Atlas(Atlas &atlas, const char *path) {
  stbi_set_flip_vertically_on_load(true);
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

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas.width, atlas.height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  atlas.id = tex;
  stbi_image_free(data);

} // load from set path
/*takes an image and pushes it to the gpu for atlas map use
 * the ids would be saved in the atlas it was called on so we use this to init
 * an atlas and then we can go and render using that atlas*/

Sprite ImageLoader::GetUVs(int x, int y, int w, int h, int atlasW, int atlasH) {
  Sprite s;

  s.u0 = (float)x / atlasW;
  s.v0 = (float)y / atlasH;
  s.u1 = (float)(x + w) / atlasW;
  s.v1 = (float)(y + h) / atlasH;
  std::cout << atlasW << ":width " << atlasH << ":height" << std ::endl;
  std::cout << s.u0 << " " << s.v0 << " " << s.u1 << " " << s.v1 << std::endl;

  return s;
} //// take atlas w h from the atlas struct
/*get uvs will take the width and highet of the atlas we want and crop it to a
 single image then *it would return us a sprite with our desired uvs so we can
 generate the vertecies for and render in the scene*/
void ImageLoader::MakeQuad(float x, float y, float w, float h, const Sprite &uv,
                           std::vector<float> &buffer) {

  buffer.push_back(x);
  buffer.push_back(y);
  buffer.push_back(uv.u0);
  buffer.push_back(uv.v1);

  buffer.push_back(x + w);
  buffer.push_back(y);
  buffer.push_back(uv.u1);
  buffer.push_back(uv.v1);

  buffer.push_back(x + w);
  buffer.push_back(y + h);
  buffer.push_back(uv.u1);
  buffer.push_back(uv.v0);

  buffer.push_back(x);
  buffer.push_back(y + h);
  buffer.push_back(uv.u0);
  buffer.push_back(uv.v0);
  std::cout << x << " " << y << " " << w << " " << h << "quadbuilder"
            << std::endl;
}
/*make quad is the meat of our renderer it makes a quad and pushed it into the
 * vertex buffer for rendering*/
void ImageLoader::MakeQuadIndices(unsigned int id,
                                  std::vector<unsigned int> &buffer) {

  buffer.push_back(id);
  buffer.push_back(id + 1);
  buffer.push_back(id + 2);
  // first tri
  buffer.push_back(id + 2);
  buffer.push_back(id + 3);
  buffer.push_back(id);
}
/*makequadindecies workes the same as make quad but with the indecies buffer
 * TODO wrap all 3 function in one function before the scripting for example
 * addUiElement() this will add a ui element give us a handle saved in a buffer
 * with the cords and everthing*/
/*TODOS make auto change function for the cords meaning takes all the changed
 * elements from the scene and updates them in the buffer element was distroyed
 * = change and so on call it after update in the lateupdate so tickedupdate is
 * included as well and before the renderer */
