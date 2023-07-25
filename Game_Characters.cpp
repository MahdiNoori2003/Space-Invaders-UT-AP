#include "Game_Characters.hpp"

using namespace std;

Game_Characters::Game_Characters(string _image_directory, int _width, int _height, int _x, int _y) {
  image_directory = _image_directory;
  width = _width;
  height = _height;
  x = _x;
  y = _y;
  shape = new Rectangle(x, y, width, height);
}

void Game_Characters::update_bullets(Window * window) {
  for (int i = 0; i < this -> bullets.size(); i++) {
    bullets[i] -> update();
    if (bullets[i] -> out_of_window(window)) {
      delete this -> bullets[i];
      this -> bullets.erase(this -> bullets.begin() + i);
    }
  }
}
void Game_Characters::draw_bullets(Window * window) {
  for (auto bullet: this -> bullets) {
    bullet -> draw(window);
  }
}
void Game_Characters::draw(Window * window) {

  window -> draw_img(image_directory, * shape);
  this -> draw_bullets(window);
}

void Game_Characters::die() {
  delete shape;
  for (int i = 0; i < this -> bullets.size(); i++) {
    delete this -> bullets[i];
  }
}