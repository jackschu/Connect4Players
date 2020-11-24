#include "minimaxNode.h"

int MinimaxNode::max_depth = 13;
int MinimaxNode::traversed = 0;

MinimaxNode::MinimaxNode(bool is_maximizer, Board &board, Tile player,
                         int depth, long alpha, long beta)
  : alpha(alpha), beta(beta), is_maximizer(is_maximizer), board(board), depth(depth), player(player) {
  value = is_maximizer ? -INF : INF;
}

long MinimaxNode::traverse() {
  MinimaxNode::traversed++;
  if(board.checkWin(root_player)){
	updateValue(INF);
	return this->value;
  }
  if(board.checkWin(MinimaxNode::flipTile(root_player))){
	updateValue(-INF);
	return this->value;
  }
  if(board.checkTie()){
	updateValue(0);
	return this->value;
  }
  if (depth == max_depth||(depth > 5 && difftime(time(0), MinimaxNode::soft_deadline) > 0)) {
	long opt = board.countConsecutive(root_player) - board.countConsecutive(MinimaxNode::flipTile(root_player));
	updateValue(opt);
	
	return this->value;
  }
  std::vector<int> moves(Board::BOARD_WIDTH);
  std::iota(moves.begin(), moves.end(), 0);
  if(randomize_check_order)
	std::random_shuffle(moves.begin(), moves.end());
  for (int move : moves){
	if(this->beta <= this->alpha) {	  
	  if(is_maximizer)
		updateValue(alpha);
	  else
		updateValue(beta);
	  return this->value;
	}
    if(!board.makeMove(move, player, true)) continue;
    MinimaxNode child(!is_maximizer, board, MinimaxNode::flipTile(player), depth + 1, alpha, beta);
	child.root_player = this->root_player;
	child.soft_deadline = this->soft_deadline;

	//if(depth == 0) printf("exploring at depth: %d move %d preval %ld beta %ld  alpha %ld\n", depth, move, value, beta, alpha);
	long opt = child.traverse();
    if (updateValue(opt))
      best_move = move;
    board.unmakeMove(move);
  }
  //printf("depth: %d move %d val %ld\n", depth, best_move, value);
  return this->value;
}

int MinimaxNode::getBestMove() const { printf("val %ld\n", this->value); return this->best_move;}

bool MinimaxNode::updateValue(long opt) {
  if (is_maximizer && opt > this->value) {
	// max nodes only touch lower bound (alpha)
	if(opt > alpha)
	  alpha = opt;
    this->value = opt;
    return true;
  } else if (!is_maximizer && opt < this->value) {
	if(opt < beta)
	  beta = opt;
    this->value = opt;
    return true;
  }
  if( best_move == -1 || (this->value == opt && bool(rand()%2)&& false)){
    return true;
  }
  return false;
}


Tile MinimaxNode::flipTile(Tile targ){
	if(targ == Tile::BLACK) return Tile::WHITE;
	if(targ == Tile::WHITE) return Tile::BLACK;
	return Tile::EMPTY;
}
