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

  printBoard(snapshot,"\ninitial snapshot");
  std::cout << "num groups nontriv,triv: "
      << snapshot.groupList.getNumNonTrivialGroups() << ","
      << snapshot.groupList.getNumTrivialGroups() << std::endl;

  Snapshot tSnapshot1 = snapshot;

  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,5));
//  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,2));
  tSnapshot1.clearGroups();
  tSnapshot1.buildGroups();
  printBoard(tSnapshot1,"\nnew groups after delete and rebuild groups");

  std::cout << "num groups nontriv,triv: "
      << tSnapshot1.groupList.getNumNonTrivialGroups() << ","
      << tSnapshot1.groupList.getNumTrivialGroups() << std::endl;
}

void GameGrid::printBoard(Snapshot &aSnapshot,const char *aHeader)
{
  if (aHeader != NULL)
  {
    std::cout << aHeader << std::endl;
  }
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell &tCell = aSnapshot.grid[r][c];
      std::cout << tCell.toString() << " ";
    }
    std::cout << std::endl;
  }
}

void GameGrid::printGroups(GroupList &aGroups,const char *aHeader)
{
  if (aHeader != NULL)
  {
    std::cout << aHeader << std::endl;
  }
  for (int i = 0; i < aGroups.size(); i++)
  {
    std::cout << aGroups[i].toString() << std::endl;
  }
}
