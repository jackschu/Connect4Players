#include "../src/board.h"
#include "../src/players/consecutivePlayer.h"
#include "../src/players/humanPlayer.h"
#include "../src/players/petersPlayer.h"
#include "../src/tile.h"
#include <cstdlib>
#include <iostream>

int handleGameOver(const Board &b);
int main() {
  bool human_first = false;
  auto human_tile = human_first ? Tile::BLACK :Tile::WHITE;
  auto computer_tile = !human_first ? Tile::BLACK :Tile::WHITE;
  Board b;
  Player * ph = new HumanPlayer(human_tile);
  //Player * pw = new PetersPlayer(Tile::WHITE);
  Player * pc = new ConsecutivePlayer(computer_tile);
  while (handleGameOver(b) < 0) {
    b.print();
	std::cout  << std::endl;

	if(!b.makeMove((human_first ? ph: pc)->getMove(b), human_first ? human_tile : computer_tile))
	  printf("bad move black\n");

	if(handleGameOver(b) >= 0)
	  break;
	
	b.print();
	std::cout  << std::endl;
	if(!b.makeMove((!human_first ? ph: pc)->getMove(b), !human_first ? human_tile : computer_tile)){
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
