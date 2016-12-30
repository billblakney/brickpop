#ifndef GAMEGRID_HH_
#define GAMEGRID_HH_

#include <vector>
#include "brickpop_const.h"
#include "Cell.hh"
#include "Group.hh"
#include "Snapshot.hh"

class GameGrid
{
public:

  GameGrid();

  virtual ~GameGrid();

  void buildGrid();

  void resetGrid();

private:
};

#endif /* GAMEGRID_HH_ */
