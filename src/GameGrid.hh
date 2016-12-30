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

  void solve(std::string (&aColors)[ROWS]);

  void replay(Snapshot aSnapshot,std::vector<int> aGroupsReduced);

  void resetGrid();

  int reduce(Snapshot &aSnapshot,std::vector<int> &aGroupsReduced);

  void printVector(std::vector<int> &aVector,const char *aHeader = NULL);

private:
};

#endif /* GAMEGRID_HH_ */
