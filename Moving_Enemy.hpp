#ifndef __MOVING__Enemy_H__
#define __MOVING__Enemy_H__

#include "Enemy.hpp"

const int MOVING_ENEMY_SPEED = 5;

class Moving_Enemy: public Enemy {
  public: Moving_Enemy(std::string _image_directory, int _width, int _height, int _x, int _y, int _map_column);

  void update(Window * window);

  private: int vy;
  Direction dir;

  void move(Window * window);
};

#endif