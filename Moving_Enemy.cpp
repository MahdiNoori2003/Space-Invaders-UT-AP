#include "Moving_Enemy.hpp"

using namespace std;

Moving_Enemy::Moving_Enemy(string _image_directory, int _width, int _height, int _x, int _y, int _map_column): Enemy(_image_directory, _width, _height, _x, _y, _map_column) {
  vy = MOVING_ENEMY_SPEED;
  int temp = rand() % 2;
  switch (temp) {
  case 0:
    dir = Right;
    break;
  case 1:
    dir = Left;
    break;
  default:
    break;
  }

}

void Moving_Enemy::update(Window * window) {

  Enemy::update(window);
  this -> move(window);
}

void Moving_Enemy::move(Window * window) {
  if (dir == Right) {
    shape -> x += this -> vy;
    if (this -> shape -> x >= (window -> get_width() - this -> shape -> w))
      dir = Left;
  }
  if (dir == Left) {
    shape -> x -= this -> vy;
    if (this -> shape -> x <= 0)
      dir = Right;
  }
}