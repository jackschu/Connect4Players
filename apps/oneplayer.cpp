#include "board.h"
#include "minimaxNode.h"
#include "tile.h"
#include <cstdlib>
#include <iostream>

int handleGameOver(const Board &b);
int main() {
  Board b;
  int col = 7;
  while (handleGameOver(b) < 0) {
    b.print();
    do {
      printf("Enter col 0-%d: ", b.BOARD_WIDTH);
      std::cin >> col;
    } while (!b.makeMove(col, Tile::BLACK));

	MinimaxNode node(true, b, Tile::WHITE);
	node.root_player = Tile::WHITE;
	node.traverse();

    if(!b.makeMove(node.getBestMove(), Tile::WHITE)){
	  printf("bad move white\n");
    }
  }
}

int handleGameOver(const Board &b) {
  int out = -1;
  if (b.checkTie()) {
    printf("Tie game!\n");
    out = 0;
  } else if (b.checkWin(Tile::WHITE)) {
    printf("White wins!\n");
    out = 2;
  } else if (b.checkWin(Tile::BLACK)) {
    printf("Black wins!\n");
    out = 1;
  }
  if (out != -1)
    b.print();
  return out;
}
