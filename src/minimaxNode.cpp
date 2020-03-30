#include "minimaxNode.h"

int MinimaxNode::max_depth = 5;

MinimaxNode::MinimaxNode(bool is_maximizer, Board &board, Tile player,
                         int depth)
    : is_maximizer(is_maximizer), board(board), depth(depth), player(player) {
  value = is_maximizer ? LONG_MIN : LONG_MAX;
}

long MinimaxNode::traverse() {
  if(board.checkWin(root_player)){
	updateValue(LONG_MAX);
	return this->value;
  }
  if(board.checkWin(MinimaxNode::flipTile(root_player))){
	updateValue(LONG_MIN);
	return this->value;
  }
  if(board.checkTie()){
	updateValue(0);
	return this->value;
  }
  
  if (depth == max_depth) {
	long opt = board.countConsecutive(root_player) - board.countConsecutive(MinimaxNode::flipTile(root_player));
	updateValue(opt);
	return this->value;
  }
  for (int move = 0; move < Board::BOARD_WIDTH; move++) {
    if(!board.makeMove(move, player, true)) continue;
    MinimaxNode child(!is_maximizer, board, MinimaxNode::flipTile(player), depth + 1);
	child.root_player = this->root_player;
    long opt = child.traverse();
	if(depth == 0) printf("move %d val %ld\n", move, opt);
    if (updateValue(opt))
      best_move = move;
    board.unmakeMove(move);
  }
  return this->value;
}
int MinimaxNode::getBestMove() const { printf("val %d\n", (int)this->value); return this->best_move;}
bool MinimaxNode::updateValue(long opt) {
  if (is_maximizer && opt > this->value) {
    this->value = opt;
    return true;
  } else if (!is_maximizer && opt < this->value) {
    this->value = opt;
    return true;
  }
  if( this->value == opt && bool(rand()%2)){
    return true;
  }
  return false;
}


Tile MinimaxNode::flipTile(Tile targ){
	if(targ == Tile::BLACK) return Tile::WHITE;
	if(targ == Tile::WHITE) return Tile::BLACK;
	return Tile::EMPTY;
}
