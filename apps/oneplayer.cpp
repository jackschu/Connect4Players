#include "board.h"
#include "tile.h"
#include <iostream>
int handleGameOver(const Board &b);
int main() {
  Board b;
  bool black_move = true;
  int col = 7;
  while (handleGameOver(b) < 0) {

    b.print();
    do {
      printf("Enter col 0-%d: ", b.BOARD_WIDTH);
      std::cin >> col;

    } while (!b.makeMove(col, Tile::BLACK));

	

    black_move != black_move;
  }
}

int handleGameOver(const Board &b) {
  if (b.checkTie()) {
    printf("Tie game!\n");
    return 0;
  } else if (b.checkWin(Tile::WHITE)) {
    printf("White wins!\n");
    return 2;
  } else if (b.checkWin(Tile::BLACK)) {
    printf("Black wins!\n");
    return 1;
  }
  return -1;
}
