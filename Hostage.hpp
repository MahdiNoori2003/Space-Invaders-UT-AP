#ifndef __Hostage_H__
#define __Hostage_H__

#include "Game_Characters.hpp"

class Hostage: public Game_Characters {
  public: Hostage(std::string _image_directory, int _width, int _height, int _x, int _y);

  void update(Window * window);

  void shoot();
};

#endif