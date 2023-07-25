#include "Player.hpp"

using namespace std;

Player::Player(string _image_directory, string _image_with_shield_directory, int _width, int _height, int _x, int _y): Game_Characters(_image_directory, _width, _height, _x, _y) {
  vx = 0;
  vy = 0;
  power_up = NULL;
  has_shield = false;
  has_twice_bullet_speed = false;
  image_with_shield_directory = _image_with_shield_directory;
}

void Player::shoot() {

  int bullet_speed = BULLET_SPEED;

  if (has_twice_bullet_speed)
    bullet_speed *= 2;

  Bullet * new_bullet = new Bullet(Point((this -> shape -> x + (width / 2)), this -> shape -> y), bullet_speed, Up);
  this -> bullets.push_back(new_bullet);

}

void Player::update(Window * window) {
  if (this -> power_up != NULL)
    this -> update_power_up();
  this -> move(window);
  this -> update_bullets(window);
}

void Player::move(Window * window) {
  this -> shape -> x += vx;
  this -> shape -> y += vy;
  if (shape -> y < 0)
    shape -> y = 0;
  if (shape -> y > (window -> get_height() - height))
    shape -> y = (window -> get_height() - height);
  if (shape -> x < 0)
    shape -> x = 0;
  if (shape -> x > (window -> get_width() - width))
    shape -> x = (window -> get_width() - width);
}

void Player::handle_key_press(char key) {
  switch (key) {
  case UP:
    vx = 0;
    vy = -PLAYER_SPEED;
    break;
  case DOWN:
    vx = 0;
    vy = PLAYER_SPEED;
    break;
  case LEFT:
    vx = -PLAYER_SPEED;
    vy = 0;
    break;
  case RIGHT:
    vx = PLAYER_SPEED;
    vy = 0;
    break;
  case SHOOT:
    this -> shoot();
    break;
  default:
    break;
  }
}

void Player::handle_key_release() {
  vx = 0;
  vy = 0;
}

void Player::activate_power_up(Power_Up * power_up) {

  if (this -> power_up != NULL)
    return;

  this -> power_up = power_up;
  if (power_up -> get_type() == shield)
    this -> activate_shield();
  if (power_up -> get_type() == twice_bullet_speed)
    this -> activate_twice_speed();
}

void Player::activate_shield() {
  this -> has_shield = true;
}

void Player::deactivate_shield() {
  this -> has_shield = false;
}

void Player::activate_twice_speed() {
  this -> has_twice_bullet_speed = true;
}

void Player::deactivate_twice_speed() {
  this -> has_twice_bullet_speed = false;
}

bool Player::has_a_shield() {
  return has_shield;
}

void Player::update_power_up() {
  power_up -> update_in_use();
  if (!power_up -> is_active()) {

    if (power_up -> get_type() == shield)
      this -> deactivate_shield();
    if (power_up -> get_type() == twice_bullet_speed)
      this -> deactivate_twice_speed();
    power_up -> destroy();
    delete power_up;
    power_up = NULL;

  }
}

void Player::destroy_bullet(Bullet * bullet) {

  for (int i = 0; i < bullets.size(); i++) {
    if (bullet == bullets[i]) {
      delete bullets[i];
      bullets.erase(bullets.begin() + i);
    }
  }
}

void Player::die() {
  Game_Characters::die();
  if (power_up != NULL) {
    power_up -> destroy();
    delete power_up;
  }
}

void Player::draw(Window * window) {
  if (has_shield) {
    window -> draw_img(image_with_shield_directory, * shape);
    Game_Characters::draw_bullets(window);
  } else
    Game_Characters::draw(window);
}