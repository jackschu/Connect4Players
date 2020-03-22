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
  REQUIRE(b.checkWin(Tile::WHITE) == false);
  REQUIRE(b.checkWin(Tile::BLACK) == true);
  
  b.unmakeMove(6);
  REQUIRE(b.checkWin(Tile::BLACK) == false);

  b.makeMove(6, Tile::BLACK);
  REQUIRE(b.checkWin(Tile::BLACK) == true);
}
