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

  int groupSeqNum;

//  void setInitialNeighbors();

  void clearGroups(Snapshot &aSnapshot,GroupList &aGroups);
  GroupList buildGroups(Snapshot &aSnapshot);
  void buildGroup(Snapshot &aSnapshot,Location aLocation,Group &aGroup);
  void extendGroup(Snapshot &aSnapshot,Location aLocation,int aColor,Group &aGroup);

  void printBoard(Snapshot &aSnapshot,const char *aHeader = NULL);
  void printGroups(GroupList &aGroups,const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
