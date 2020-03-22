#pragma once
#include "tile.h"
#include <bitset>
#include <iostream>
#include <vector>

class Board {
public:
  const static int BOARD_WIDTH = 7;
  const static int WIN_LEN = 4;
  const static int BOARD_HEIGHT = 6;

  Board();
  void print();
  bool checkWin(Tile player);
  // return if succeed, col is 0 indexed
  bool makeMove(int column, Tile player);
  bool unmakeMove(int column);

private:
  Tile board[BOARD_HEIGHT * BOARD_WIDTH] = {Tile::EMPTY};
  int nextEmpty[BOARD_WIDTH] = {};
  std::bitset<BOARD_HEIGHT * BOARD_WIDTH> toBitset(Tile match);
  static std::vector<std::bitset<BOARD_HEIGHT * BOARD_WIDTH>> initializeWinlist();
  const static std::vector<std::bitset<BOARD_HEIGHT * BOARD_WIDTH>>& getWinlist();
};


