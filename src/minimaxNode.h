#pragma once
#include "board.h"
#include "tile.h"
#include <climits>
#include <time.h> 
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
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
  // after this time, all traversals act as end-nodes
  time_t soft_deadline;
  static int traversed;
private:

  const static long INF = 10000;
  const static bool randomize_check_order = true;
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
