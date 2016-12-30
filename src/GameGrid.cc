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

  Snapshot snapshot(tRows);

  snapshot.printBoard("\ninitial snapshot");
  std::cout << "num groups nontriv,triv: "
      << snapshot.groupList.getNumNonTrivialGroups() << ","
      << snapshot.groupList.getNumTrivialGroups() << std::endl;

  Snapshot tSnapshot1 = snapshot;

  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,5));
//  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,2));
  tSnapshot1.clearGroups();
  tSnapshot1.buildGroups();
  tSnapshot1.printBoard("\nnew groups after delete and rebuild groups");

  std::cout << "num groups nontriv,triv: "
      << tSnapshot1.groupList.getNumNonTrivialGroups() << ","
      << tSnapshot1.groupList.getNumTrivialGroups() << std::endl;
}
