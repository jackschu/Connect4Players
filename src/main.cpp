#include "board.h"
#include "players/consecutivePlayer.h"
#include "minimaxNode.h"
#include "tile.h"
#include <iostream>
int main() {
  Board b = Board();
  Player * pb = new ConsecutivePlayer(Tile::WHITE);
// 5: -------
// 4: -------
// 3: ---O-X-
// 2: --XX-O-
// 1: -OXX-O-
// 0: OXOXXO-

	b.makeMove(0, Tile::WHITE); b.makeMove(1, Tile::BLACK); b.makeMove(2, Tile::WHITE); b.makeMove(3, Tile::BLACK); b.makeMove(4, Tile::BLACK); b.makeMove(5, Tile::WHITE);
  b.makeMove(1, Tile::WHITE); b.makeMove(2, Tile::BLACK); b.makeMove(3, Tile::BLACK); b.makeMove(5, Tile::WHITE);
  b.makeMove(2, Tile::BLACK); b.makeMove(3, Tile::BLACK); b.makeMove(5, Tile::WHITE);
  b.makeMove(3, Tile::WHITE); b.makeMove(5, Tile::BLACK);
	
  b.print();
  int move = pb->getMove(b);
  std::cout << move << std::endl;
  b.makeMove(move, Tile::WHITE);
  b.print();
  std::cout << b.checkWin(Tile::WHITE) << std::endl;
  std::cout << b.countConsecutive(Tile::WHITE) << std::endl;
}
