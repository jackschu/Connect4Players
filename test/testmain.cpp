#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "board.h"
#include "tile.h"

TEST_CASE("diagonal win", "[win check]"){
  Board b = Board();
  b.makeMove(3, Tile::BLACK); 
  b.makeMove(4, Tile::WHITE);
  b.makeMove(5, Tile::WHITE);
  b.makeMove(6, Tile::WHITE);

  b.makeMove(4, Tile::BLACK);
  b.makeMove(5, Tile::WHITE);
  b.makeMove(6, Tile::WHITE);
  
  b.makeMove(5, Tile::BLACK);
  b.makeMove(6, Tile::WHITE);
  
  b.makeMove(6, Tile::BLACK);
  b.print();
  REQUIRE(b.checkWin(Tile::WHITE) == false);
  REQUIRE(b.checkWin(Tile::BLACK) == true);
  
}
