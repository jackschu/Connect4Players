#pragma once
#include "../board.h"
#include "../tile.h"
class Player {
public:
  Player(Tile player);
  virtual int getMove(const Board &board) = 0;
protected:
  Tile player;
};
