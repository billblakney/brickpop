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
      tCell.empty = false;
      tCell.color = c; //TODO
      tCell.group = NO_GROUP;
    }
  }

  grid[9][5].color = 1;
  grid[8][5].color = 1;
  grid[0][5].color = 8;
  grid[1][5].color = 8;

  printBoard("before groups");

  buildGroups();
  printBoard("\nafter groups");

  deleteGroupAt(Location(5,5));
  printBoard("\nafter delete");

  clearGroups();
  buildGroups();
  printBoard("\nnew groups after delete");
}

void GameGrid::clearGroups()
{
  groupSeqNum = NO_GROUP; //TODO

  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
      grid[r][c].group = NO_GROUP;

  std::vector<Group*>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    Group *tGroup = *tIter;
    delete tGroup;
  }
  groups.clear();
}

void GameGrid::buildGroups()
{
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
        tGroup->addLocation(tLocation);
        buildGroup(tLocation,tGroup);
        groups.push_back(tGroup);
      }
    }
  }
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
        aGroup->addLocation(aLocation);
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
  Group *tGroup = getGroupAt(aLocation);
  if (tGroup == NULL)
  {
    std::cout << "ERROR: Couldn't find group at " << aLocation.toString() << std::endl;
  }
  else
  {
    std::cout << "Deleting group with id " << tGroup->id << " at " << aLocation.toString() << std::endl;
  }

  for (int tCol = 0; tCol < COLS; tCol++)
  {
    int tNumToDelete = tGroup->getNumToDeleteAtCol(tCol);
    if ( tNumToDelete > 0)
    {
std::cout << "number to delete for col" << tCol << " is " << tNumToDelete << std::endl;
      int tFirstToDelete = tGroup->getFirstToDeleteAtCol(tCol);
std::cout << "first to delete for col" << tCol << " is " << tFirstToDelete << std::endl;
      for (int tRow = tFirstToDelete; tRow >= 0; tRow--)
      {
        int tColor = getColorAt(Location(tRow-tNumToDelete,tCol));
std::cout << "new color is " << tColor << std::endl;
        grid[tRow][tCol].color = tColor;
        if (tColor == NO_COLOR)
        {
          grid[tRow][tCol].empty = true;
        }
      }
    }
  }
}

int GameGrid::getColorAt(Location aLocation)
{
  if (aLocation.isValid())
  {
    return grid[aLocation.row][aLocation.col].color;
  }
  else
  {
    return NO_COLOR;
  }
}

Group *GameGrid::getGroupAt(Location aLocation)
{
  std::vector<Group*>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    Group *tGroup = *tIter;

    int tRow = aLocation.row;
    int tCol = aLocation.col;

    if (tRow <= tGroup->boundaries[tCol][0]
     && tRow >= tGroup->boundaries[tCol][1])
    {
      return tGroup;
    }
  }
  return NULL;
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
