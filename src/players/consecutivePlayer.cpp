#include "consecutivePlayer.h"

ConsecutivePlayer::ConsecutivePlayer(Tile player): Player(player) {};

int ConsecutivePlayer::getMove(const Board &board){
  auto copy_board = board;
  MinimaxNode node(true, copy_board, this->player);
  time_t now = time(0);
  node.root_player = this->player;
  node.soft_deadline = now + 2;
  node.traverse();
  double elapsed = difftime(time(0), now);
  printf("consec player thought for %.3lf seconds\n", elapsed);
  return node.getBestMove();
}
