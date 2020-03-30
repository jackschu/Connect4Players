#pragma once
#include "board.h"
#include "tile.h"
#include <climits>
#include <vector>
class MinimaxNode {

public:
  MinimaxNode(bool is_maximizer, Board &board, Tile player, int depth = 0);
  long traverse();

private:
  void updateValue(long value);
  static int max_depth;
  bool is_maximizer;
  long value;
  Board &board;
  int depth;
  int best_move;
  Tile player;
};
