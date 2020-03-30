#include "board.h"

Board::Board() {}

void Board::print() const {
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

void Board::printBitset(std::bitset<BOARD_HEIGHT * BOARD_WIDTH> bs) {
  for (int i = Board::BOARD_HEIGHT - 1; i >= 0; i--) {
    printf("%d: ", i);
    for (int j = 0; j < Board::BOARD_WIDTH; j++) {
      switch (bs[i * BOARD_WIDTH + j]) {
      case 1:
        printf("X");
        break;
      case 0:
        printf("-");
        break;
      }
    }
    printf("\n");
 }
}

bool Board::checkTie() const {
  auto status = this->toBitset(Tile::BLACK) | this->toBitset(Tile::WHITE);
  return status.all();
}

bool Board::checkWin(Tile player) const {
  auto status = this->toBitset(player);
  for (const auto &win_cond : this->getWinlist())
    if ((status & win_cond).count() >= WIN_LEN)
      return true;
  return false;
}

int Board::countConsecutive(Tile player) const {
  auto status = this->toBitset(player);
  int out = 0;
  for (const auto &consec : this->getConsecutiveList()){
	int opt = 0;
	for(int ind : consec){
	  if(status[ind]) opt++;
	  else{
		out = std::max(opt, out);
		opt = 0;
	  }
	}
	out = std::max(out, opt);
  }
  return out;
}

bool Board::unmakeMove(int column) {
  if (column < 0 || column >= BOARD_WIDTH) {
    std::cerr << "[Error] column " << column << " is out of range" << std::endl;
    return false;
  }

  if (nextEmpty[column] == 0) {
    std::cerr << "[Error] column " << column << " is empty" << std::endl;
    return false;
  }
  nextEmpty[column]--;
  board[BOARD_WIDTH * nextEmpty[column] + column] = Tile::EMPTY;
  return true;
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
Board::toBitset(Tile match) const {
  std::bitset<BOARD_HEIGHT * BOARD_WIDTH> out;
  for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++)
    out[i] = this->board[i] == match;
  return out;
}

std::vector<std::bitset<Board::BOARD_HEIGHT * Board::BOARD_WIDTH>>
Board::initializeWinlist(bool consecutive_counter) {
  std::vector<std::bitset<BOARD_HEIGHT *BOARD_WIDTH>> out = {};
  int max_loop = consecutive_counter ? Board::BOARD_HEIGHT + Board::BOARD_WIDTH : Board::WIN_LEN;
  for (int i = 0; i < Board::BOARD_HEIGHT; i++) {
    for (int j = 0; j < Board::BOARD_WIDTH; j++) {
	  if(consecutive_counter && i!=0 && j!=0 && i!=BOARD_HEIGHT-1 && j!=BOARD_WIDTH-1)
		continue;
		
      std::bitset<BOARD_HEIGHT *BOARD_WIDTH> current = {};
      // horiz
      for (int k = 0; k < max_loop; k++) {
        int y = i;
        int x = j + k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0){
		  if(consecutive_counter)
			out.push_back(current);
          break;
		}
        current.set(y * BOARD_WIDTH + x);
        if (k == max_loop - 1)
          out.push_back(current);
      }

      // vert
      current.reset();
      for (int k = 0; k < max_loop; k++) {
        int y = i + k;
        int x = j;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0){
		  if(consecutive_counter)
			out.push_back(current);
		  break;
		}
        current.set(y * BOARD_WIDTH + x);

        if (k == max_loop - 1)
          out.push_back(current);
      }

      // diag up right
      current.reset();
      for (int k = 0; k < max_loop; k++) {
        int y = i + k;
        int x = j + k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0){
		  if(consecutive_counter)
			out.push_back(current);
          break;
		}
        current.set(y * BOARD_WIDTH + x);
        if (k == max_loop - 1)
          out.push_back(current);
      }

      // diag up left
      current.reset();
      for (int k = 0; k < max_loop; k++) {
        int y = i + k;
        int x = j - k;
        if (y >= BOARD_HEIGHT || x >= BOARD_WIDTH || x < 0 || y < 0){
		  if(consecutive_counter)
			out.push_back(current);
          break;
		}
        current.set(y * BOARD_WIDTH + x);
        if (k == max_loop - 1)
          out.push_back(current);
      }
    }
  }
  if(consecutive_counter){
	std::unordered_set<std::bitset<BOARD_HEIGHT * BOARD_WIDTH>> s( out.begin(), out.end() );
	out.assign( s.begin(), s.end() );
	for(int i = 0; i < out.size(); i++){
	  for(int j = 0; j < out.size(); j++){
		if(i==j) continue;
		// removes i if i is a subset of j
		if((out[i] | out[j]).count() == out[j].count()){
		  out.erase(out.begin()+i);
		  i--;
		  break;
		}
	  }
	}
  }
  return out;
}

std::vector<std::vector<int>>
Board::initializeConsecutiveList(){
  auto bitlist = Board::initializeWinlist(true);
  static std::vector<std::vector<int>> out;
  for(auto &elem  : bitlist){
	std::vector<int> out_part;
	for(int i = 0; i < elem.size(); i++)
	  if(elem[i]) out_part.push_back(i);
	out.push_back(out_part);
  }
  return out;
}

const std::vector<std::bitset<Board::BOARD_HEIGHT * Board::BOARD_WIDTH>> &
Board::getWinlist() {
  static auto out = Board::initializeWinlist();
  return out;
}

const std::vector<std::vector<int>> &
Board::getConsecutiveList() {
  static auto out = Board::initializeConsecutiveList();
  return out;
}
