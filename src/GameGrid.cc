#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "brickpop_const.h"
#include "GridUtil.hh"
#include "GameGrid.hh"
#include "Util.hh"

static bool debug = false;

GameGrid::GameGrid()
{
}

GameGrid::~GameGrid()
{
}

void GameGrid::solve(std::string (&aColors)[ROWS])
{
  Snapshot snapshot(aColors);
  if (debug)
    snapshot.printBoard("\ninitial snapshot");

//#define TEST1
//#define TEST2
#ifdef TEST1
  Snapshot tSnapshot1 = snapshot.deleteGroupAt(Location(5,5));
  tSnapshot1.printBoard("\nsnapshot after delete");
#endif
#ifdef TEST2
  Snapshot tNextSnapshot = snapshot.deleteGroup(0);
  tNextSnapshot.printBoard("\nsnapshot after delete first group");
#endif

  std::vector<int> tGroupsReduced;

  int tReturn = reduce(snapshot,tGroupsReduced);

  if (tReturn == 0)
  {
    Util::printVector(tGroupsReduced,"Solve SUCCEEDED");
    replay(snapshot,tGroupsReduced);
  }
  else if (tReturn == 1)
  {
    Util::printVector(tGroupsReduced,"Solve failed");
  }
}

void GameGrid::replay(Snapshot aSnapshot,std::vector<int> aGroupsReduced)
{
  Snapshot tSnapshot = aSnapshot;
  tSnapshot.printBoard("Original board:");

  int i = 0;
  while (aGroupsReduced.size() > 0)
  {
    int tGroupIndex = aGroupsReduced.back();
    aGroupsReduced.pop_back();
    tSnapshot = tSnapshot.deleteGroup(tGroupIndex);
    std::cout << "Step " << ++i << std::endl;
    tSnapshot.printBoard();
  }
}

int GameGrid::reduce(Snapshot &aSnapshot,std::vector<int> &aGroupsReduced)
{
  for (int i = 0; i < aSnapshot.groupList.size(); i++)
  {
    if (aSnapshot.groupList[i].locations.size() < 2) //TODO
      continue;

    aGroupsReduced.push_back(i);

    Snapshot tNextSnapshot = aSnapshot.deleteGroup(i);
    if (debug)
      tNextSnapshot.printBoard();

    if (tNextSnapshot.isGridEmpty())
    {
      if (debug)
        Util::printVector(aGroupsReduced,"SOLVED!!!");
      return 0;
    }
    else if (tNextSnapshot.groupList.getNumNonTrivialGroups() < 1)
    {
      if (debug)
        Util::printVector(aGroupsReduced,"HIT DEAD END");
      aGroupsReduced.pop_back();
    }
    else
    {
      if (debug)
        Util::printVector(aGroupsReduced,"Continuing with solve");
      int tReturn = reduce(tNextSnapshot,aGroupsReduced);
      if (tReturn == 0)
        return 0;
      else
        aGroupsReduced.pop_back();
    }
  }
  return 1;
}
