/*add macros for sprites here the templat is as follows
 * make sure when adding macros youre keeping the right
 * size for the images otherwise wrong image will render
 * */
#include "loadImage.h"
#include "textManeger.h"
#include <iostream>
enum SpriteID { PLAYER_UP, PLAYER_UP_LEFT, PLAYER_UP_RIGHT, FULL_TEXT_ATLAS };

inline Sprite getSpriteUvs(int id) {
  ImageLoader load = ImageLoader::getInstance();
  std::cout << "faggot" << std::endl;
  switch (id) {
  case PLAYER_UP_RIGHT:
    return load.GetUVs(64, 96, 32, 32, load.player_atlas.width,
                       load.player_atlas.height);
  case PLAYER_UP:
    return load.GetUVs(32, 96, 32, 32, load.player_atlas.width,
                       load.player_atlas.height);
  case PLAYER_UP_LEFT:
    return load.GetUVs(0, 96, 32, 32, load.player_atlas.width,
                       load.player_atlas.height);
  default:
    return load.GetUVs(0, 0, 512, 512, 512, 512);
  }
}
