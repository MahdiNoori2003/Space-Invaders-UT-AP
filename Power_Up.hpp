#ifndef __Power_Up_H__
#define __Power_Up_H__

enum Power_up_type {
  shield,
  twice_bullet_speed
};

#include "rsdl.hpp"

class Power_Up {
  public:
    Power_Up(std::string _image_directory, Power_up_type _type, int _width, int _height, int _x, int _y, int _duration, int _durability);

  void draw(Window * window);

  void update();

  void update_in_use();

  bool is_active();

  bool can_be_in_screen();

  void destroy();

  Rectangle * get_shape() {
    return shape;
  }

  Power_up_type get_type() {
    return type;
  }

  private:
    std::string image_directory;
  Power_up_type type;
  Rectangle * shape;
  int duration;
  int durability;
  int width;
  int height;
  int x;
  int y;
};

#endif