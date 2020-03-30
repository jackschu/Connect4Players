#include "tile.h"

namespace tile {
  Tile flipTile(Tile targ){
	if(targ == Tile::BLACK) return Tile::WHITE;
	if(targ == Tile::WHITE) return Tile::BLACK;
	return Tile::EMPTY;
  }
}
