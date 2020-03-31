#pragma once
#include "board.h"
#include "tile.h"
#include <climits>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <vector>
class MinimaxNode {

public:
  MinimaxNode(bool is_maximizer, Board &board, Tile player, int depth = 0, long alpha = -MinimaxNode::INF, long beta = MinimaxNode::INF);
  long traverse();
  int getBestMove() const;
  Tile root_player;
  // max lower bound
  long alpha;
  // min upper bound
  long beta;
private:
  const static long INF = LONG_MAX;
  const static bool randomize_moves = false;
  static Tile flipTile(Tile targ);
  bool updateValue(long value);
  static int max_depth;
  bool is_maximizer;
  long value;
  Board &board;
  int depth;
  int best_move = -1;
  Tile player;
};
