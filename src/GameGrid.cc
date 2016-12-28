#include <cstddef>
#include <cstdlib>
#include <iostream>
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
      Cell &tCell = grid[r][c];
      tCell.color = c; //TODO
      tCell.group = 0;
    }
  }

  /*
   * Set the groups.
   */
  printBoard("before groups");

  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Location tLocation(r,c);
      Cell &tCell = grid[r][c];
      if (tCell.group == NO_GROUP)
      {
        int tGroupIdx = ++groupSeqNum;
        tCell.group = tGroupIdx;
        Group *tGroup = new Group(tGroupIdx);
        tGroup->locations.push_back(tLocation);
        buildGroup(tLocation,tGroup);
        groups.push_back(tGroup);
      }
    }
  }

  printBoard("\nafter groups");
  printGroups("\nGroups:");
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

void GameGrid::buildGroup(Location aLocation,Group *aGroup)
{
  Cell &tCell = grid[aLocation.row][aLocation.col];

  int tColor = tCell.color;

//  std::cout << "building group for cell row,col,color,group: "
//      << aCell->location.row << "," << aCell->location.col << ","
//      << aCell->color << "," << aCell->group << std::endl;

  Location tLocation;

  tLocation = getLocationNorth(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = getLocationEast(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = getLocationSouth(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = getLocationWest(aLocation);
  extendGroup(tLocation,tColor,aGroup);
}

void GameGrid::extendGroup(Location aLocation,int aColor,Group *aGroup)
{
  if (aLocation.isValid())
  {
    Cell &tCell = grid[aLocation.row][aLocation.col];
    if (tCell.group == NO_GROUP)
    {
      if (tCell.color == aColor)
      {
        tCell.group = aGroup->id;
        aGroup->locations.push_back(aLocation);
        buildGroup(aLocation,aGroup);
      }
    }
  }
}

void GameGrid::deleteGroupAt(Location aLocation)
{
#if 0
  if (aRow < 0 || aRow >= ROWS || aCol < 0 || aCol >= COLS)
  {
    std::cout "Invalid row,col: " << aRow << "," << aCol << std::endl;
    exit(1);
  }
#endif
}

void GameGrid::printBoard(const char *aHeader)
{
  if (aHeader != NULL)
  {
    std::cout << aHeader << std::endl;
  }
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell &tCell = grid[r][c];
      std::cout << tCell.toString() << " ";
    }
    std::cout << std::endl;
  }
}

void GameGrid::printGroups(const char *aHeader)
{
  if (aHeader != NULL)
  {
    std::cout << aHeader << std::endl;
  }
  for (int i = 0; i < groups.size(); i++)
  {
    std::cout << groups[i]->toString() << std::endl;
  }
}
