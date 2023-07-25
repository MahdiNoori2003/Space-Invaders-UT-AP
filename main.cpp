#include<iostream>

#include<vector>

#include "Game.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  srand(time(NULL));
  Game game("Star Wars");
  game.run(argv[1]);

  return 0;
}