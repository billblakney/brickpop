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

  Snapshot snapshot;

  GameGrid();

  virtual ~GameGrid();

  void buildGrid();

  void resetGrid();

private:

//  void setInitialNeighbors();

  void printBoard(Snapshot &aSnapshot,const char *aHeader = NULL);
  void printGroups(GroupList &aGroups,const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
