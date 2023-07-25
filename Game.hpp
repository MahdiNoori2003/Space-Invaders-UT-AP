#ifndef __Game_H__
#define __Game_H__

#include<iostream>

#include<vector>

#include<algorithm>

#include <fstream>

#include "rsdl.hpp"

#include "Bullet.hpp"

#include "Game_Characters.hpp"

#include "Player.hpp"

#include "Enemy.hpp"

#include "Moving_Enemy.hpp"

#include "Hostage.hpp"


const int PLAYER_WIDTH = 80;
const int PLAYER_HEIGHT = 40;
const int HOSTAGE_WIDTH = 60;
const int HOSTAGE_HEIGHT = 60;
const int ENEMY_WIDTH = 60;
const int ENEMY_HEIGHT = 60;
const int MOVING_ENEMY_WIDTH = 60;
const int MOVING_ENEMY_HEIGHT = 60;
const int MAP_BLOCK_WIDTH = 90;
const int MAP_BLOCK_HEIGHT = 90;
const int MAP_ROW_OFFSET = 50;
const int MAP_COLUMN_OFFSET = 40;
const int POWER_UP_PERCENTAGE = 40;
const int POWER_UP_WIDTH = 40;
const int POWER_UP_HEIGHT = 40;
const int POWER_UP_DURATION = 300;
const int POWER_UP_DURABILITY = 100;
const int ENEMY_SHOOT_COOLDOWN = 50;
const int GAME_LOOP_DELAY = 15;
const int END_LEVEL_DELAY = 1500;
const int QUIT_DELAY = 1200;
const std::string PLAYER_PIC = "assets/player.png";
const std::string PLAYER_WITH_SHIELD_PIC = "assets/player_with_shield.png";
const std::string HOSTAGE_PIC = "assets/green.png";
const std::string ENEMY_PIC = "assets/yellow.png";
const std::string MOVING_ENEMY_PIC = "assets/red.png";
const std::string SHIELD_PIC = "assets/shield.png";
const std::string BULLET_PIC = "assets/bullet.png";
const std::string WIN_SOUND = "assets/win.wav";
const std::string LOSE_SOUND = "assets/lose.wav";
const char MAP_EMPTY_SPACE_SIGN = '.';
const char MAP_ENEMY_SIGN = 'E';
const char MAP_MOVING_ENEMY_SIGN = 'M';
const char MAP_HOSTAGE_SIGN = 'S';

typedef struct {
  int num_of_rows;
  int num_of_columns;
}
Map;

class Game {
  public:
    Game(std::string _name);

  void run(std::string map_file_name);

  private:
    int window_height;
  int window_width;
  std::string name;
  Window * window;
  Player * player;
  Hostage * hostage;
  std::vector < Enemy * > enemies;
  Map map;
  std::vector < Power_Up * > power_ups;
  int num_of_levels;
  std::string difficulty;
  int enemies_shoot_cooldown;

  void quit();

  void update();

  void draw();

  void read_map(std::ifstream & map_file, int stage);

  void map_initializer(std::ifstream & map_file);

  bool has_intersection(Rectangle * A, Rectangle * B);

  void update_player();

  void update_enemies();

  void handle_events();

  void change_shooter_column();

  std::vector < int > find_random_columns(int count);

  void check_collisions();

  void enemies_check_collisions();

  void player_check_collisions();

  void power_ups_check_collisions();

  void power_up_generator(Enemy * dead_enemy);

  void update_power_ups();

  void game_initializer(std::ifstream & map_file);

  void end_level();
};

#endif