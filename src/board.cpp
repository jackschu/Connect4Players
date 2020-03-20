#include "board.h"

Board::Board() {}

void Board::print() {
  for (int i = this->BOARD_HEIGHT - 1; i >= 0; i--) {
    printf("%d: ", i);
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

bool Board::checkWin(Tile player) {
  auto status = this->toBitset(player);
  for (const auto &win_cond : this->getWinlist())
    if ((status & win_cond).count() == WIN_LEN)
      return true;
  return false;
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

  board[BOARD_WIDTH * nextEmpty[column] + column] = player;
  nextEmpty[column]++;

  return true;
}

std::bitset<Board::BOARD_HEIGHT * Board::BOARD_WIDTH>
Board::toBitset(Tile match) {
  std::bitset<BOARD_HEIGHT * BOARD_WIDTH> out;
  for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
    out[i] = this->board[i] == match;
  return out;
}

std::vector<std::bitset<Board::BOARD_HEIGHT * Board::BOARD_WIDTH>>
Board::initializeWinlist() {
  std::vector<std::bitset<BOARD_HEIGHT *BOARD_WIDTH>> out = {};

  for (int i = 0; i < Board::BOARD_HEIGHT; i++) {
    for (int j = 0; j < Board::BOARD_WIDTH; j++) {
      std::bitset<BOARD_HEIGHT *BOARD_WIDTH> current = {};
      // horiz
      for (int k = 0; k < WIN_LEN; k++) {
        int y = i;
        int x = j + k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0)
          break;
        current.set(y * BOARD_WIDTH + x);
        if (k == WIN_LEN - 1)
          out.push_back(current);
      }

      // vert
      current.reset();
      for (int k = 0; k < WIN_LEN; k++) {
        int y = i + k;
        int x = j;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0)
          break;
        current.set(y * BOARD_WIDTH + x);

        if (k == WIN_LEN - 1)
          out.push_back(current);
      }

      // diag up right
      current.reset();
      for (int k = 0; k < WIN_LEN; k++) {
        int y = i + k;
        int x = j + k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0)
          break;
        current.set(y * BOARD_WIDTH + x);
        if (k == WIN_LEN - 1)
          out.push_back(current);
      }

      // diag up left
      current.reset();
      for (int k = 0; k < WIN_LEN; k++) {
        int y = i + k;
        int x = j - k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0)
          break;
        current.set(y * BOARD_WIDTH + x);
        if (k == WIN_LEN - 1)
          out.push_back(current);
      }
    }
  }
  return out;
}

std::vector<std::bitset<Board::BOARD_HEIGHT * Board::BOARD_WIDTH>>
Board::getWinlist() {
  static auto out = Board::initializeWinlist();
  return out;
}
