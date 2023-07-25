#include"Bullet.hpp"


Bullet::Bullet(Point _initial_pos, int _speed, Direction _dir): shape(_initial_pos, 6, 6) {
  speed = _speed;
  dir = _dir;
}

void Bullet::update() {
  this -> move();
}

void Bullet::draw(Window * window) {
  window -> fill_rect(shape, YELLOW);

}

bool Bullet::out_of_window(Window * window) {
  if (this -> shape.y < 0 || this -> shape.y > window -> get_height()) {
    return true;
  }

  return false;
}

Rectangle * Bullet::get_shape() {
  return &this -> shape;
}

void Bullet::move() {
  if (dir == Up)
    shape.y -= speed;
  if (dir == Down)
    shape.y += speed;
}