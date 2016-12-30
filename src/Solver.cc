#include "Solver.hh"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "brickpop_const.h"
#include "GridUtil.hh"
#include "Util.hh"

static int reduce_counter; // number of calls to reduce
static bool debug = false; // detailed debug of solve
static bool trace_reduce = false; // print one line per reduce call
static int trace_reduce_period = 100000;

Solver::Solver()
{
}

Solver::~Solver()
{
}

void Solver::solve(std::string (&aColors)[ROWS])
{
  Board snapshot(aColors);
  if (debug)
    snapshot.printBoard("\ninitial snapshot");

//#define TEST1
//#define TEST2
#ifdef TEST1
  Board tSnapshot1 = snapshot.deleteGroupAt(Location(5,5));
  tSnapshot1.printBoard("\nsnapshot after delete");
#endif
#ifdef TEST2
  Board tNextSnapshot = snapshot.deleteGroup(0);
  tNextSnapshot.printBoard("\nsnapshot after delete first group");
#endif

  std::vector<int> tGroupsReduced;

  int tReturn = reduce(snapshot,tGroupsReduced);

  if (tReturn == 0)
  {
    std::cout << "Solve SUCCEEDED: " << Util::toString(tGroupsReduced);
    replay(snapshot,tGroupsReduced);
  }
  else if (tReturn == 1)
  {
    std::cout << "Solve failed: " << Util::toString(tGroupsReduced);
  }
}

void Solver::replay(Board aSnapshot,std::vector<int> aGroupsReduced)
{
  Board tSnapshot = aSnapshot;
  tSnapshot.printBoard("Original board:");

  int i = 0;
  while (aGroupsReduced.size() > 0)
  {
    int tGroupIndex = aGroupsReduced.front();
    aGroupsReduced.erase(aGroupsReduced.begin());
    std::cout << "Step " << ++i << ": deleting groupId "
        << tSnapshot.getGroupIdFromIndex(tGroupIndex) << std::endl;
    tSnapshot = tSnapshot.deleteGroup(tGroupIndex);
    tSnapshot.printBoard();
  }
}

int Solver::reduce(Board &aSnapshot,std::vector<int> &aGroupsReduced)
{
  if (trace_reduce)
  {
    ++reduce_counter;
    if (reduce_counter%trace_reduce_period ==0)
      std::cout << reduce_counter << ": " << Util::toString(aGroupsReduced) << std::endl;
  }

  for (int i = 0; i < aSnapshot.groupList.size(); i++)
  {
    if (aSnapshot.groupList[i].locations.size() < 2) //TODO
      continue;

    aGroupsReduced.push_back(i);

    Board tNextSnapshot = aSnapshot.deleteGroup(i);
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
