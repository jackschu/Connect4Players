#include "humanPlayer.h"

HumanPlayer::HumanPlayer(Tile player): Player(player) {};

int HumanPlayer::getMove(const Board &board){
  std::string player_str;
  int col;
  if(player == Tile::BLACK)
	player_str = "black";
  else
	player_str = "white";
  do{
	printf("You are %s Enter col 0-%d: ", player_str.c_str(), board.BOARD_WIDTH-1);
	std::cin >> col;
  }	while(!board.isLegalMove(col, player));
  return col;
}
