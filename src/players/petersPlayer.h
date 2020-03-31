#pragma once
#include "player.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
class PetersPlayer: public Player {
 public:
  PetersPlayer(Tile player);
  virtual int getMove(const Board &board);
};
