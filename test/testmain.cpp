#define CATCH_CONFIG_MAIN
#include "board.h"
#include "minimaxNode.h"
#include "catch.hpp"
#include "tile.h"

TEST_CASE("diagonal win", "[win check]") {

  Board b = Board();
  MinimaxNode a(false, b, Tile::BLACK);
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
TEST_CASE("non-connectable count", "[consec check]") {
  Board b = Board();
  b.makeMove(0, Tile::BLACK);
  b.makeMove(6, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 1);
}
TEST_CASE("blocked doesnt count", "[blocked consec check]") {
  Board b = Board();
  b.makeMove(0, Tile::BLACK);
  b.makeMove(1, Tile::BLACK);
  b.makeMove(2, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 3);
  b.makeMove(3, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 1);
}

TEST_CASE("triangle acceptance", "[consec check]") {
  Board b = Board();
  b.makeMove(3, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 1);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 0);
  b.makeMove(4, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 1);
  b.makeMove(5, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 1);
  b.makeMove(6, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 1);

  b.makeMove(4, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 2);
  b.makeMove(5, Tile::WHITE);
  b.makeMove(6, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 2);

  b.makeMove(5, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 3);
  b.makeMove(6, Tile::WHITE);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 3);

  b.makeMove(6, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 4);
  REQUIRE(b.countConsecutive(Tile::WHITE) == 2);

  b.unmakeMove(6);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 3);

  b.makeMove(6, Tile::BLACK);
  REQUIRE(b.countConsecutive(Tile::BLACK) == 4);
}
