#include "board.h"
#include "players/consecutivePlayer.h"
#include "players/humanPlayer.h"
#include "players/petersPlayer.h"
#include "tile.h"
#include <cstdlib>
#include <iostream>

int handleGameOver(const Board &b);
int main() {
  Board b;
  Player * pb = new HumanPlayer(Tile::BLACK);
  Player * pw = new PetersPlayer(Tile::WHITE);
  //Player * pw = new ConsecutivePlayer(Tile::WHITE);
  while (handleGameOver(b) < 0) {
    b.print();
	std::cout  << std::endl;

	if(!b.makeMove(pb->getMove(b), Tile::BLACK))
	  printf("bad move black\n");

	if(handleGameOver(b) >= 0)
	  break;
	
	b.print();
	std::cout  << std::endl;
    if(!b.makeMove(pw->getMove(b), Tile::WHITE)){
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
