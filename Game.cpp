#include "Game.hpp"

using namespace std;

Game::Game(std::string _name) {
  name = _name;
}

void Game::run(string map_file_name) {
  ifstream map_file;
  map_file.open(map_file_name);
  map_initializer(map_file);
  for (int stage = 0; stage < num_of_levels; stage++) {
    enemies_shoot_cooldown = ENEMY_SHOOT_COOLDOWN;
    hostage = NULL;
    read_map(map_file, stage);
    if (stage == 0)
      window = new Window(window_width, window_height, name);
    player = new Player(PLAYER_PIC, PLAYER_WITH_SHIELD_PIC, PLAYER_WIDTH, PLAYER_HEIGHT, rand() % (window_width - PLAYER_WIDTH), window_height - PLAYER_HEIGHT);
    while (!enemies.empty()) {
      draw();
      update();
      delay(GAME_LOOP_DELAY);
    }
    end_level();
  }
  map_file.close();
  delete window;
}

void Game::draw() {
  window -> clear();
  player -> draw(window);
  for (auto power_up: power_ups)
    power_up -> draw(window);
  if (hostage != NULL)
    hostage -> draw(window);
  for (auto enemy: enemies)
    enemy -> draw(window);
  window -> update_screen();
}

void Game::update_player() {
  player -> update(window);
}

void Game::update_enemies() {
  if (this -> enemies_shoot_cooldown <= 0) {
    this -> change_shooter_column();
    this -> enemies_shoot_cooldown = ENEMY_SHOOT_COOLDOWN;
  }
  this -> enemies_shoot_cooldown--;
  for (int i = 0; i < enemies.size(); i++)
    enemies[i] -> update(window);
}

void Game::update() {

  this -> update_player();
  this -> update_enemies();
  this -> update_power_ups();
  this -> check_collisions();
  this -> handle_events();
}

void Game::enemies_check_collisions() {
  for (int i = 0; i < enemies.size(); i++) {

    if (has_intersection(enemies[i] -> get_shape(), player -> get_shape())) {
      this -> quit();
    }
    for (auto bullet: enemies[i] -> get_bullets()) {
      if (has_intersection(bullet -> get_shape(), player -> get_shape()) && !player -> has_a_shield()) {
        this -> quit();
      }
    }
    for (auto & bullet: player -> get_bullets()) {
      if (has_intersection(bullet -> get_shape(), enemies[i] -> get_shape())) {
        player -> destroy_bullet(bullet);
        power_up_generator(enemies[i]);
        enemies[i] -> die();
        delete enemies[i];
        enemies.erase(enemies.begin() + i);
      }
    }
  }
}

void Game::player_check_collisions() {
  if (hostage != NULL) {
    if (has_intersection(player -> get_shape(), hostage -> get_shape())) {
      this -> quit();
    }
    for (auto bullet: player -> get_bullets()) {
      if (has_intersection(bullet -> get_shape(), hostage -> get_shape())) {
        this -> quit();
      }
    }
  }
}

void Game::power_ups_check_collisions() {

  for (int i = 0; i < power_ups.size(); i++) {
    if (has_intersection(player -> get_shape(), power_ups[i] -> get_shape())) {
      player -> activate_power_up(power_ups[i]);
      power_ups.erase(power_ups.begin() + i);
    }
  }
}

void Game::check_collisions() {

  this -> enemies_check_collisions();
  this -> player_check_collisions();
  this -> power_ups_check_collisions();
}

bool Game::has_intersection(Rectangle * A, Rectangle * B) {

  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = A -> x;
  rightA = A -> x + A -> w;
  topA = A -> y;
  bottomA = A -> y + A -> h;

  leftB = B -> x;
  rightB = B -> x + B -> w;
  topB = B -> y;
  bottomB = B -> y + B -> h;

  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }

  return true;
}

void Game::handle_events() {
  while (window -> has_pending_event()) {
    Event event = window -> poll_for_event();
    switch (event.get_type()) {
    case Event::EventType::QUIT:
      this -> quit();
      break;
    case Event::EventType::KEY_PRESS:
      player -> handle_key_press(event.get_pressed_key());
      break;
    case Event::EventType::KEY_RELEASE:
      player -> handle_key_release();
      break;
    default:
      break;
    }
  }
}

void Game::quit() {
  player -> die();
  if (hostage != NULL) {
    hostage -> die();
    delete hostage;
  }
  delete player;
  for (int i = 0; i < power_ups.size(); i++) {
    power_ups[i] -> destroy();
    delete power_ups[i];
  }
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i] -> die();
    delete enemies[i];
  }
  window -> play_sound_effect(LOSE_SOUND);
  delay(QUIT_DELAY);
  delete window;
  exit(0);

}

void Game::end_level() {
  window -> play_sound_effect(WIN_SOUND);
  player -> die();
  delete player;
  if (hostage != NULL) {
    hostage -> die();
    delete hostage;
    hostage = NULL;
  }
  for (int i = 0; i < power_ups.size(); i++) {
    power_ups[i] -> destroy();
    delete power_ups[i];
  }
  power_ups.clear();
  window -> clear();
  window -> update_screen();
  delay(END_LEVEL_DELAY);
}

void Game::game_initializer(ifstream & map_file) {

  int col_Offset = MAP_COLUMN_OFFSET;
  char temp;

  for (int i = 0; i < map.num_of_rows; i++) {
    int row_Offset = MAP_ROW_OFFSET;
    for (int j = 0; j < map.num_of_columns; j++) {
      map_file >> temp;
      switch (temp) {
      case MAP_EMPTY_SPACE_SIGN:
        row_Offset += MAP_BLOCK_WIDTH;
        break;
      case MAP_ENEMY_SIGN:
        enemies.push_back(new Enemy(ENEMY_PIC, ENEMY_WIDTH, ENEMY_HEIGHT, row_Offset, col_Offset, j));
        row_Offset += MAP_BLOCK_WIDTH;
        break;
      case MAP_MOVING_ENEMY_SIGN:
        enemies.push_back(new Moving_Enemy(MOVING_ENEMY_PIC, MOVING_ENEMY_WIDTH, MOVING_ENEMY_HEIGHT, row_Offset, col_Offset, j));
        row_Offset += MAP_BLOCK_WIDTH;
        break;
      case MAP_HOSTAGE_SIGN:
        hostage = new Hostage(HOSTAGE_PIC, HOSTAGE_WIDTH, HOSTAGE_HEIGHT, row_Offset, col_Offset);
        row_Offset += MAP_BLOCK_WIDTH;
        break;
      default:
        break;
      }
    }
    col_Offset += MAP_BLOCK_HEIGHT;
  }
}

void Game::map_initializer(ifstream & map_file) {
  int rows, columns, levels;
  map_file >> rows >> columns >> levels;
  map.num_of_columns = columns;
  map.num_of_rows = rows;
  num_of_levels = levels;

  window_width = 2 * MAP_ROW_OFFSET + map.num_of_columns * MAP_BLOCK_WIDTH;
  window_height = 2 * MAP_COLUMN_OFFSET + map.num_of_rows * MAP_BLOCK_HEIGHT;
}

void Game::read_map(ifstream & map_file, int stage) {

  this -> game_initializer(map_file);

  string b;
  getline(map_file, b);
  getline(map_file, difficulty);
  if (stage != (num_of_levels - 1)) {
    getline(map_file, b);
  }

}

void Game::power_up_generator(Enemy * dead_enemy) {
  int temp = rand() % 100;
  if (temp > POWER_UP_PERCENTAGE)
    return;

  temp = rand() % 2;
  switch (temp) {
  case 0:
    power_ups.push_back(new Power_Up(SHIELD_PIC, shield, POWER_UP_WIDTH, POWER_UP_HEIGHT, dead_enemy -> get_shape() -> x,
      dead_enemy -> get_shape() -> y, POWER_UP_DURATION, POWER_UP_DURABILITY));
    break;
  case 1:
    power_ups.push_back(new Power_Up(BULLET_PIC, twice_bullet_speed, POWER_UP_WIDTH, POWER_UP_HEIGHT, dead_enemy -> get_shape() -> x,
      dead_enemy -> get_shape() -> y, POWER_UP_DURATION, POWER_UP_DURABILITY));
    break;
  default:
    break;
  }
}

void Game::update_power_ups() {
  for (int i = 0; i < power_ups.size(); i++) {
    power_ups[i] -> update();
    if (!power_ups[i] -> can_be_in_screen()) {
      power_ups.erase(power_ups.begin() + i);
      power_ups[i] -> destroy();
      delete power_ups[i];
    }
  }

}

vector < int > Game::find_random_columns(int count) {
  vector < int > random_columns;

  while (random_columns.size() < count) {
    int b = rand() % map.num_of_columns;
    if (!(find(random_columns.begin(), random_columns.end(), b) != random_columns.end())) {
      random_columns.push_back(b);
    }

  }
  return random_columns;
}

void Game::change_shooter_column() {
  vector < int > forbiden_columns;
  if (this -> difficulty == "Easy\r" || this -> difficulty == "Easy") {
    forbiden_columns = find_random_columns(3);
  }
  if (this -> difficulty == "Medium\r" || this -> difficulty == "Medium") {
    forbiden_columns = find_random_columns(2);
  }
  if (this -> difficulty == "Hard\r" || this -> difficulty == "Hard") {
    forbiden_columns = find_random_columns(1);
  }

  for (int i = 0; i < enemies.size(); i++) {
    bool can_shoot = true;
    for (auto column: forbiden_columns) {
      if (enemies[i] -> get_column() == column)
        can_shoot = false;
    }
    if (can_shoot)
      enemies[i] -> shoot();
  }

}