#ifndef __Player_H__
#define __Player_H__

#include "Game_Characters.hpp"

#include "Power_Up.hpp"

const int PLAYER_SPEED = 10;
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char SHOOT = ' ';

class Player: public Game_Characters {
  public: Player(std::string _image_directory, std::string _image_with_shield_directory, int _width, int _height, int _x, int _y);

  void shoot();

  void die();

  void handle_key_press(char key);

  void handle_key_release();

  void move(Window * window);

  void update(Window * window);

  void destroy_bullet(Bullet * bullet);

  void update_power_up();

  void deactivate_shield();

  void activate_shield();

  void deactivate_twice_speed();

  void activate_twice_speed();

  void activate_power_up(Power_Up * power_up);

  bool has_a_shield();

  void draw(Window * window);

  private: int vx;
  int vy;
  bool has_shield;
  bool has_twice_bullet_speed;
  Power_Up * power_up;
  std::string image_with_shield_directory;
};

#endif