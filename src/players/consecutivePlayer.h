#pragma once
#include "player.h"
#include "../minimaxNode.h"

class ConsecutivePlayer: public Player {
 public:
  ConsecutivePlayer(Tile player);
  virtual int getMove(const Board &board);
};
