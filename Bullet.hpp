#ifndef __Bullet_H__
#define __Bullet_H__

#include "rsdl.hpp"

const int BULLET_SPEED = 8;

enum Direction {
  Up,
  Down,
  Left,
  Right
};

class Bullet {
  public:
    Bullet(Point _initial_pos, int _speed, Direction _dir);
  void update();
  void draw(Window * window);
  bool out_of_window(Window * Window);
  Rectangle * get_shape();
  private:
    int speed;
  Rectangle shape;
  Direction dir;
  void move();
};

#endif