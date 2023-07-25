#ifndef __Enemy_H__
#define __Enemy_H__

#include "Game_Characters.hpp"


class Enemy: public Game_Characters {
  public: Enemy(std::string _image_directory, int _width, int _height, int _x, int _y, int _map_column);

  void shoot();

  void update(Window * window);

  int get_column() {
    return map_column;
  }

  protected: int map_column;
};

#endif