#include "Enemy.hpp"

using namespace std;

Enemy::Enemy(string _image_directory, int _width, int _height, int _x, int _y, int _map_column): Game_Characters(_image_directory, _width, _height, _x, _y) {
  map_column = _map_column;
}

void Enemy::shoot() {
  Bullet * new_bullet = new Bullet(Point((this -> shape -> x + (width / 2)), this -> shape -> y + 40), BULLET_SPEED, Down);
  this -> bullets.push_back(new_bullet);
}

void Enemy::update(Window * window) {
  this -> update_bullets(window);
}