#include "board.h"
#include "minimaxNode.h"
#include "tile.h"
#include <iostream>
int main() {
  Board b = Board();
  b.makeMove(3, Tile::BLACK);
  b.makeMove(3, Tile::WHITE);
  b.makeMove(3, Tile::WHITE);
  std::cout << b.checkWin(Tile::WHITE) << std::endl;
  b.makeMove(3, Tile::WHITE);
  b.makeMove(3, Tile::WHITE);
  b.print();
  std::cout << b.checkWin(Tile::WHITE) << std::endl;
  std::cout << b.countConsecutive(Tile::WHITE) << std::endl;
}
