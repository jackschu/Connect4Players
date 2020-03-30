#pragma once
#include "tile.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <unordered_set>
#include <vector>

class Board {
public:
  const static int BOARD_WIDTH = 7;
  const static int WIN_LEN = 4;
  const static int BOARD_HEIGHT = 6;

  Board();
  void print() const;
  static void printBitset(std::bitset<BOARD_HEIGHT * BOARD_WIDTH> bs);
  bool checkWin(Tile player) const;
  int countConsecutive(Tile player) const;
  bool checkTie() const;
  // return if succeed, col is 0 indexed
  bool makeMove(int column, Tile player);
  bool unmakeMove(int column);

private:
  Tile board[BOARD_HEIGHT * BOARD_WIDTH] = {Tile::EMPTY};
  int nextEmpty[BOARD_WIDTH] = {};
  std::bitset<BOARD_HEIGHT * BOARD_WIDTH> toBitset(Tile match) const;

  static std::vector<std::bitset<BOARD_HEIGHT * BOARD_WIDTH>>
  initializeWinlist(bool consecutive_counter = false);

  const static std::vector<std::bitset<BOARD_HEIGHT * BOARD_WIDTH>> &
  getWinlist();

  static std::vector<std::vector<int>> initializeConsecutiveList();
  const static std::vector<std::vector<int>> &getConsecutiveList();
};
