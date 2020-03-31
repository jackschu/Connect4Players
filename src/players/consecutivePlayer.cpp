#include "consecutivePlayer.h"

ConsecutivePlayer::ConsecutivePlayer(Tile player): Player(player) {};

int ConsecutivePlayer::getMove(const Board &board){
  auto copy_board = board;
  MinimaxNode node(true, copy_board, this->player);
  node.root_player = this->player;
  node.traverse();
  return node.getBestMove();
}
