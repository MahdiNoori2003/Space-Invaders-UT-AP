#include "Power_Up.hpp"

using namespace std;

Power_Up::Power_Up(string _image_directory, Power_up_type _type, int _width, int _height, int _x, int _y, int _duration, int _durability) {
  image_directory = _image_directory;
  width = _width;
  height = _height;
  x = _x;
  y = _y;
  duration = _duration;
  durability = _durability;
  type = _type;
  shape = new Rectangle(x, y, width, height);
}

void Power_Up::draw(Window * window) {
  window -> draw_img(image_directory, * shape);
}

void Power_Up::update() {
  if (duration < 0) {
    duration = 0;
  }
  duration--;
}

void Power_Up::update_in_use() {
  if (durability < 0) {
    durability = 0;
  }
  durability--;
}

void Power_Up::destroy() {
  delete shape;
}

bool Power_Up::is_active() {
  if (this -> durability > 0)
    return true;

  return false;
}

bool Power_Up::can_be_in_screen() {
  if (this -> duration > 0)
    return true;

  return false;
}