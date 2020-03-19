#pragma once
#include <iostream>
#include <bitset>

#include "tile.h"

class Board {
public:
  const static int BOARD_WIDTH = 7;
  const static int BOARD_HEIGHT = 6;
  
  Board();
  void print();
  bool checkWin(int player);
  // return if succeed, col is 0 indexed
  bool makeMove(int column, Tile player);

private:
  Tile board[BOARD_HEIGHT * BOARD_WIDTH] = {Tile::EMPTY};
  int nextEmpty[BOARD_WIDTH] = {};
};
