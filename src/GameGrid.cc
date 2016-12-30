#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "brickpop_const.h"
#include "GridUtil.hh"
#include "GameGrid.hh"

GameGrid::GameGrid()
{
}

GameGrid::~GameGrid()
{
}

void GameGrid::buildGrid()
{
#if 0
  std::string tRows[10] = {
      "abcdexghij",
      "abcdexghij",
      "abcdefghij",
      "abcdefghij",
      "abcdefghij",
      "abcdefghij",
      "abcdefghij",
      "abcdefghij",
      "abcdeyghij",
      "abcdeyghij"
  };
#endif
#if 1
  std::string tRows[10] = {
      "abcdexghij",
      "abcdexghij",
      "abcdefghij",
      "abjjefghij",
      "abjjefghij",
      "abcdefghij",
      "abcdefgmij",
      "abcdefgmmm",
      "abcdeyghij",
      "abcdeyghij"
  };
#endif

  Snapshot snapshot(tRows);
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
    printVector(tGroupsReduced,"Solve SUCCEEDED");
  else if (tReturn == 1)
    printVector(tGroupsReduced,"Solve failed");
}

int GameGrid::reduce(Snapshot &aSnapshot,std::vector<int> &aGroupsReduced)
{
  for (int i = 0; i < aSnapshot.groupList.size(); i++)
  {
    if (aSnapshot.groupList[i].locations.size() < 2) //TODO
      continue;

    aGroupsReduced.push_back(i);

    Snapshot tNextSnapshot = aSnapshot.deleteGroup(i);
//    tNextSnapshot.printBoard();

    if (tNextSnapshot.isGridEmpty())
    {
      printVector(aGroupsReduced,"SOLVED!!!");
      return 0;
    }
    else if (tNextSnapshot.groupList.getNumNonTrivialGroups() < 1)
    {
      printVector(aGroupsReduced,"HIT DEAD END");
      aGroupsReduced.pop_back();
    }
    else
    {
      printVector(aGroupsReduced,"Continuing with solve");
      int tReturn = reduce(tNextSnapshot,aGroupsReduced);
      if (tReturn == 0)
        return 0;
      else
        return 1;
    }
  }
  return 1;
}

void GameGrid::printVector(std::vector<int> &aVector,const char *aHeader)
{
  std::cout << aHeader << std::endl;

  std::vector<int>::iterator tIter;
  for (tIter = aVector.begin(); tIter != aVector.end(); tIter++)
  {
    std::cout << " " << *tIter;
  }
  std::cout << std::endl;
}
