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

  Snapshot tSnapshot1 = snapshot.deleteGroupAt(Location(5,5));
  tSnapshot1.printBoard("\nnew groups after delete and rebuild groups");
}
