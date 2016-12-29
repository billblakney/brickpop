#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "brickpop_const.h"
#include "GameGrid.hh"

GameGrid::GameGrid()
{
  groupSeqNum = NO_GROUP;
}

GameGrid::~GameGrid()
{
}

void GameGrid::buildGrid()
{
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell &tCell = snapshot.grid[r][c];
      tCell.empty = false;
      tCell.color = 'a' + c; //TODO
      tCell.group = NO_GROUP;
    }
  }

  snapshot.grid[9][5].color = 'x';
  snapshot.grid[8][5].color = 'x';
  snapshot.grid[0][5].color = 'y';
  snapshot.grid[1][5].color = 'y';

  printBoard(snapshot,"before groups");

snapshot.groupList = buildGroups(snapshot);
  printBoard(snapshot,"\ninitial snapshot");

  std::cout << "num groups nontriv,triv: "
      << snapshot.groupList.getNumNonTrivialGroups() << ","
      << snapshot.groupList.getNumTrivialGroups() << std::endl;

  Snapshot tSnapshot1 = snapshot;
  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,5));
//  tSnapshot1.deleteGroupAt(tSnapshot1.groupList,Location(5,2));
  clearGroups(tSnapshot1,tSnapshot1.groupList);
tSnapshot1.groupList = buildGroups(tSnapshot1);
  printBoard(tSnapshot1,"\nnew groups after delete and rebuild groups");

  std::cout << "num groups nontriv,triv: "
      << tSnapshot1.groupList.getNumNonTrivialGroups() << ","
      << tSnapshot1.groupList.getNumTrivialGroups() << std::endl;
}

void GameGrid::clearGroups(Snapshot &aSnapshot,GroupList &aGroups)
{
  groupSeqNum = NO_GROUP; //TODO

  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
      aSnapshot.grid[r][c].group = NO_GROUP;

  aGroups.clear();
}

GroupList GameGrid::buildGroups(Snapshot &aSnapshot)
{
  GroupList tGroups;

  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Location tLocation(r,c);
      Cell &tCell = aSnapshot.grid[r][c];
      if (!tCell.empty && tCell.group == NO_GROUP)
      {
        int tGroupIdx = ++groupSeqNum;
        tCell.group = tGroupIdx;
        Group tGroup(tGroupIdx);
        tGroup.addLocation(tLocation);
        buildGroup(aSnapshot,tLocation,tGroup);
        tGroups.push_back(tGroup);
      }
    }
  }

  return tGroups;
}

Location GameGrid::getLocationNorth(Location aLocation)
{
  return getLocationNorth(aLocation.row,aLocation.col);
}

Location GameGrid::getLocationEast(Location aLocation)
{
  return getLocationEast(aLocation.row,aLocation.col);
}

Location GameGrid::getLocationSouth(Location aLocation)
{
  return getLocationSouth(aLocation.row,aLocation.col);
}

Location GameGrid::getLocationWest(Location aLocation)
{
  return getLocationWest(aLocation.row,aLocation.col);
}

Location GameGrid::getLocationNorth(int aRow,int aCol)
{
  if (isTopRow(aRow, aCol))
  {
    return Location();
  }
  else
  {
    return Location(aRow-1,aCol);
  }
}

Location GameGrid::getLocationEast(int aRow,int aCol)
{
  if (isRightCol(aRow, aCol))
  {
    return Location();
  }
  else
  {
    return Location(aRow,aCol+1);
  }
}

Location GameGrid::getLocationSouth(int aRow,int aCol)
{
  if (isBottomRow(aRow, aCol))
  {
    return Location();
  }
  else
  {
    return Location(aRow+1,aCol);
  }
}

Location GameGrid::getLocationWest(int aRow,int aCol)
{
  if (isLeftCol(aRow, aCol))
  {
    return Location();
  }
  else
  {
    return Location(aRow,aCol-1);
  }
}


bool GameGrid::isTopLeftCorner(int aRow,int aCol)
{
  if (aRow == 0 && aCol == 0)
    return true;
  else
    return false;
}

bool GameGrid::isTopRightCorner(int aRow,int aCol)
{
  if (aRow == 0 && aCol == COLS-1)
    return true;
  else
    return false;
}

bool GameGrid::isBottomLeftCorner(int aRow,int aCol)
{
  if (aRow == ROWS-1 && aCol == 0)
    return true;
  else
    return false;
}

bool GameGrid::isBottomRightCorner(int aRow,int aCol)
{
  if (aRow == ROWS-1 && aCol == COLS-1)
    return true;
  else
    return false;
}

bool GameGrid::isTopRow(int aRow,int aCol)
{
  if (aRow == 0)
    return true;
  else
    return false;
}

bool GameGrid::isBottomRow(int aRow,int aCol)
{
  if (aRow == ROWS-1)
    return true;
  else
    return false;
}

bool GameGrid::isLeftCol(int aRow,int aCol)
{
  if (aCol == 0)
    return true;
  else
    return false;
}

bool GameGrid::isRightCol(int aRow,int aCol)
{
  if (aCol == COLS-1)
    return true;
  else
    return false;
}

void GameGrid::resetGrid()
{
}

void GameGrid::buildGroup(Snapshot &aSnapshot,Location aLocation,Group &aGroup)
{
  Cell &tCell = aSnapshot.grid[aLocation.row][aLocation.col];

  if (tCell.empty)
  {
    return;
  }

  int tColor = tCell.color;

//  std::cout << "building group for cell row,col,color,group: "
//      << aCell->location.row << "," << aCell->location.col << ","
//      << aCell->color << "," << aCell->group << std::endl;

  Location tLocation;

  tLocation = getLocationNorth(aLocation);
  extendGroup(aSnapshot,tLocation,tColor,aGroup);

  tLocation = getLocationEast(aLocation);
  extendGroup(aSnapshot,tLocation,tColor,aGroup);

  tLocation = getLocationSouth(aLocation);
  extendGroup(aSnapshot,tLocation,tColor,aGroup);

  tLocation = getLocationWest(aLocation);
  extendGroup(aSnapshot,tLocation,tColor,aGroup);
}

void GameGrid::extendGroup(Snapshot &aSnapshot,Location aLocation,int aColor,Group &aGroup)
{
  if (aLocation.isValid())
  {
    Cell &tCell = aSnapshot.grid[aLocation.row][aLocation.col];
    if (!tCell.empty && tCell.group == NO_GROUP)
    {
      if (tCell.color == aColor)
      {
        tCell.group = aGroup.id;
        aGroup.addLocation(aLocation);
        buildGroup(aSnapshot,aLocation,aGroup);
      }
    }
  }
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
