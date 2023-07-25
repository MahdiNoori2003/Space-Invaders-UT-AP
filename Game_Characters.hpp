#ifndef __Character_H__
#define __Character_H__

#include "rsdl.hpp"

#include <vector>

#include "Bullet.hpp"

class Game_Characters {
  public:
    Game_Characters(std::string _image_directory, int _width, int _height, int _x, int _y);

  virtual void shoot() = 0;

  void update_bullets(Window * window);

  Rectangle * get_shape() {
    return this -> shape;
  }

  void die();

  std::vector < Bullet * > get_bullets() {
    return this -> bullets;
  }

  virtual void update(Window * window) = 0;

  void draw_bullets(Window * window);

  void draw(Window * window);

  protected:
    Rectangle * shape;
  std::vector < Bullet * > bullets;
  std::string image_directory;
  int width;
  int height;
  int x;
  int y;
};

#endif