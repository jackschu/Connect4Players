#include "petersPlayer.h"

PetersPlayer::PetersPlayer(Tile player): Player(player) {};


namespace peters {
  /*DFS on board states to find best move*/
  int minimax(int depth, char **board, bool isMax, int rows, int columns);
  /*Used to evaulate the score for a given move*/
  int positionScore(char **board, int rows, int columns, int player);
  //Prints Board after Each Move
  void printBoard(char **board, int rows, int columns);
  //Handles adding player move to the board
  void playerMove(char **board, int playerC, int j, int rows, int columns, bool isComp);
  //Checks if move is valid
  int isValidMove(char **board, int rows, int columns, int c);
  //Checks to see if a player won in 2 player
  int checkWin(char **board, int rows, int columns);
  int calcBestMove(char **board, int rows, int columns);
}
void peters::printBoard(char** board, int rows, int columns){
  for (int q = 0; q < columns; q++){
    printf("|%d", q + 1);
  }
  printf("|\n");
  for (int i = 0; i < rows; i++) {
     for (int j = 0; j < columns; j++) {
      printf("|%c", board[i][j]);
     }
     printf("| \n");
  }
  return;
}

int peters::checkWin(char **board, int rows, int columns){
  int nir = 1;

  //horizontal win checkWin
  for (int i = rows - 1; i >= 0; i--) {
    for (int j = 0; j < columns; j++) {
      // printf("(1) (%d,%d) -> (%d,%d) ", i, j, i, j+1);
      // printf("%d == %d ", board[i][j], board[i][j+1]);
      // printf("nir = %d\n", nir);
      if (board[i][j] == board[i][j+1] && board[i][j] != ' ')
        nir++;
      else
        nir = 1;
      if (nir == 4 && board[i][j] == 'X')
        return 1000;
      if (nir == 4 && board[i][j] == 'O')
        return -1000;
    }
  }
  nir = 1;
  //vertical win check
  for (int j = 0; j < columns; j++) {
    for (int i = rows - 1; i > 0; i--) {
      // printf("(2) ");
      // printf("%d == %d ", board[i][j], board[i-1][j]);
      // printf("%d\n", nir);
      if (board[i][j] == board[i-1][j] && board[i][j] != ' ')
        nir++;
      else
        nir = 1;
      if (nir == 4 && board[i][j] == 'X')
        return 1000;
      if (nir == 4 && board[i][j] == 'O')
        return -1000;

    }
  }

  int d = std::min(rows, columns);
  int diag[d];
  memset(diag, 0, sizeof diag);
  int p = 0;

  //Positive diagonal win check
  for (int k = 0; k <= rows + columns - 2; k++){
    for (int j = 0; j <= k; j++){
      int i = k - j;
      if (i < rows && j < columns){
        diag[p] = board[i][j];
        p++;
      }
    }
    p = 0;
    for (int q = 0; q < rows; q++){
      // printf("%d-%d ", diag[q], nir);
      if (diag[q] == diag[q+1] && diag[q] != ' ' && diag[q] != 0)
        nir++;
      else
        nir = 1;
      if (nir == 4 && diag[q] == 'X')
        return 1000;
      if (nir == 4 && diag[q] == 'O')
        return -1000;

    }
    memset(diag, 0, sizeof diag);
    // printf("\n");
  }


  nir = 1;

  //Negative diagonal win check
  for (int i = rows - 1; i >= 0; i--){
    for (int j = 0; j < rows; j++){
      int k = i + j;
      if ((k < rows) && (j < columns)) {
        diag[p] = board[k][j];
        p++;
      }
	}
	p = 0;
	for (int q = 0; q < rows; q++){
	  if (diag[q] == diag[q+1] && diag[q] != ' ' && diag[q] != 0)
		nir++;
	  else
		nir = 1;
	  if (nir == 4 && diag[q] == 'X')
		return 1000;
	  if (nir == 4 && diag[q] == 'O')
		return -1000;
	}
    memset(diag, 0, sizeof diag);
  }


  for (int j = 1; j < columns; j ++){
    for (int i = 0; i < rows; i++){
      int k = j + i;
      if ((i < rows) && (k < columns)){
        diag[p] = board[i][k];
        p++;
      }
    }
    p = 0;
    for (int q = 0; q < rows; q++){
      if (diag[q] == diag[q+1] && diag[q] != ' ' && diag[q] != 0)
        nir++;
      else
        nir = 1;
      if (nir == 4 && diag[q] == 'X')
        return 1000;
      if (nir == 4 && diag[q] == 'O')
        return -1000;
    }
    memset(diag, 0, sizeof diag);
  }


  return -1;
}

  
int peters::calcBestMove(char **board, int rows, int columns){
  int bestMove = 0;
  int bestVal = -1000;
  for (int i = 0; i < columns; i++){
	if (isValidMove(board, rows, columns, i) == 1){
	  int mVal = minimax(rows*columns, board, true, rows, columns);
	  if (mVal > bestVal){
		bestMove = i;
		bestVal = mVal;
	  }
	}
  }

  return bestMove + 1;
}
  
int peters::minimax(int depth, char **boardCopy, bool isMax, int rows, int columns){
  int player;
  if (isMax == true) player = 0;
  if (isMax == false) player = 1;
  if (depth == 0)
	return checkWin(boardCopy, rows, columns);

  if (isMax == true) {
	int maxEval = -1000;
	for (int i = 1; i <= columns; i++){
	  if (isValidMove(boardCopy, rows, columns, i) == 1){
		playerMove(boardCopy, player, i, rows, columns, true);
		int eval = minimax(depth - 1, boardCopy, false, rows, columns);
		maxEval = std::max(maxEval, eval);
	  }
	}
	return maxEval;
  }

  if(isMax == false) {
	int minEval = 1000;
	for (int i = 1; i <= columns; i++){
	  if (isValidMove(boardCopy, rows, columns, i) == 1){
		playerMove(boardCopy, player, i, rows, columns, true);
		int eval = minimax(depth -1, boardCopy, true, rows, columns);
		minEval = std::min(minEval, eval);
	  }
	}
	return minEval;
  }
  printf("unreachable\n");
  return 0;
}


void peters::playerMove(char **board, int playerC, int j, int rows, int columns, bool isComp){

  int move = 0;
  while(move == 0){
	j = j - 1;
	if (isComp == false){
	  for(int i = rows - 1; i >= 0 ; i--){
		if (board[0][j] != ' ' || j >= columns || j < 0){  //Checks to make sure number is a valid move
		  printf("\nInvalid Move");
		  printf("\nChoose a new move: ");
		  scanf("%d", &j);
		  j = j -1;
		  i = rows;
		}
		else if (board[i][j] == ' '){
		  if (playerC == 0)
			board[i][j] = 'X';
		  if (playerC == 1)
			board[i][j] = 'O';
		  return;
		}
	  }
	}
	if (isComp == true){
	  for(int i = rows - 1; i >= 0 ; i--){
		if (board[i][j] == ' '){
		  if (playerC == 0){
			board[i][j] = 'X';
			move = 1;
		  }
		  if (playerC == 1){
			board[i][j] = 'O';
			move = 1;
		  }
		  return;
		}
	  }
	}
  }
  return;
}
  
int peters::isValidMove(char **board, int rows, int columns, int c){
  c = c - 1;
  for(int i = rows - 1; i >= 0 ; i--){
	if (board[0][c] != ' ' || c >= columns || c < 0){  //Checks to make sure number is a valid move
	  return 0;
	}
	else if (board[i][c] == ' '){

	  return 1;
	}
  }
  return -1;
}



int PetersPlayer::getMove(const Board &board){
  auto char_array = board.toChar();
  time_t now = time(0);
  peters::printBoard(char_array, Board::BOARD_HEIGHT, Board::BOARD_WIDTH);
  int out = peters::calcBestMove(char_array, Board::BOARD_HEIGHT, Board::BOARD_WIDTH) - 1;
  double elapsed = difftime(time(0), now);
  printf("peters player thought for %.3lf seconds\n", elapsed);
  
  for(int i = 0; i < Board::BOARD_HEIGHT; i++)	
	delete char_array[i];
  delete char_array;
  return out;
}
