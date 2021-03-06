#pragma once
#include <iostream>
#include <string>
#include "player.h"
#include "minimaxNode.h"

class HumanPlayer: public Player {
 public:
  HumanPlayer(Tile player);
  virtual int getMove(const Board &board);
};
