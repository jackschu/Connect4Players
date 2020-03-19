#include "board.h"

Board::Board() {}

void Board::print() {
  for (int i = 0; i < this->BOARD_HEIGHT; i++) {
    printf("%d: ", this->BOARD_HEIGHT - i);
    for (int j = 0; j < this->BOARD_WIDTH; j++) {
      switch (this->board[i * BOARD_WIDTH + j]) {
      case Tile::BLACK:
        printf("X");
        break;
      case Tile::WHITE:
        printf("O");
        break;
      case Tile::EMPTY:
        printf("-");
        break;
      }
    }
    printf("\n");
  }
}

bool Board::makeMove(int column, Tile player) {
  if (player == Tile::EMPTY) {
    std::cerr << "[Error] player is empty" << std::endl;
    return false;
  }

  if (column < 0 || column >= BOARD_WIDTH) {
    std::cerr << "[Error] column " << column << " is out of range" << std::endl;
    return false;
  }

  if (nextEmpty[column] >= BOARD_HEIGHT) {
    std::cerr << "[Error] column " << column << " is full" << std::endl;
    return false;
  }

  board[BOARD_HEIGHT * nextEmpty[column] + column] = player;
  nextEmpty[column]++;

  return true;
}
