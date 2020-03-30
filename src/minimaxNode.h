#pragma once
#include "board.h"
#include "tile.h"
#include <climits>
#include <cstdlib>
#include <vector>
class MinimaxNode {

public:
  MinimaxNode(bool is_maximizer, Board &board, Tile player, int depth = 0);
  long traverse();
  int getBestMove() const;
  Tile root_player;
private:
  static Tile flipTile(Tile targ);
  bool updateValue(long value);
  static int max_depth;
  bool is_maximizer;
  long value;
  Board &board;
  int depth;
  int best_move;
  Tile player;

};
