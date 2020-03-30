#include "minimaxNode.h"
int MinimaxNode::max_depth = 2;

MinimaxNode::MinimaxNode(bool is_maximizer, Board &board, Tile player,
                         int depth)
    : is_maximizer(is_maximizer), board(board), depth(depth), player(player) {
  value = is_maximizer ? std::LONG_MIN : std::LONG_MAX;
}

long MinimaxNode::traverse() {
  if (depth == max_depth) {
    // todo
    return 3;
  }
  for (int move = 0; move < Board::BOARD_WIDTH; move++) {
    board->makeMove(move, player);
    MinimaxNode child(!is_maximizer, board, tile::flipTile(player), depth + 1);
    long opt = child.traverse();
    if (updateValue(opt))
      best_move = move;
    board->unmakeMove(move, player);
  }
}

bool MinimaxNode::updateValue(long opt) {
  if (is_maximizer && opt > this->value) {
    this->value = opt;
    return true;
  } else if (!is_maximizer && opt < this->value) {
    this->value = opt;
    return true;
  }
  return false;
}
