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
      Cell *tCell = new Cell();

      tCell->color = c; //TODO

      tCell->group = 0;

      Location tLocation(r,c);
      Neighbors tNeighbors(NULL,NULL,NULL,NULL);

      tCell->origLocation = tLocation;
      tCell->origNeighbors = tNeighbors;

      tCell->location = tLocation;
      tCell->neighbors = tNeighbors; // will get overwrote later

      grid[r][c] = tCell;
    }
  }

  setInitialNeighbors();

  /*
   * Set the groups.
   */
  printBoard("before groups");

  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell *tCell = grid[r][c];
      if (tCell->group == NO_GROUP)
      {
        tCell->group = ++groupSeqNum;
        buildGroup(tCell);
      }
    }
  }

  printBoard("\nafter groups");
}

void GameGrid::setInitialNeighbors()
{
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell *tCell = grid[r][c];

      /*
       * Set neighbors for the general case, then clean up for the special
       * cases.
       */
      tCell->neighbors.top = grid[r-1][c];
      tCell->neighbors.right = grid[r][c+1];
      tCell->neighbors.bottom = grid[r+1][c];
      tCell->neighbors.left = grid[r][c-1];

      if (isTopLeftCorner(r,c)) // 0,0
      {
        tCell->neighbors.top = NULL;
        tCell->neighbors.left = NULL;
      }
      else if (isTopRightCorner(r,c)) // 0,COLS-1
      {
        tCell->neighbors.top = NULL;
        tCell->neighbors.right = NULL;
      }
      else if (isBottomLeftCorner(r,c)) // ROWS-1,0
      {
        tCell->neighbors.bottom = NULL;
        tCell->neighbors.left = NULL;
      }
      else if (isBottomRightCorner(r,c)) // ROWS-1,COLS-1
      {
        tCell->neighbors.right = NULL;
        tCell->neighbors.bottom = NULL;
      }
      else if (isTopRow(r,c))
      {
        tCell->neighbors.top = NULL;
      }
      else if (isBottomRow(r,c))
      {
        tCell->neighbors.bottom = NULL;
      }
      else if (isLeftCol(r,c))
      {
        tCell->neighbors.left = NULL;
      }
      else if (isRightCol(r,c))
      {
        tCell->neighbors.right = NULL;
      }
      else
      {
      }
    }
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

void GameGrid::buildGroup(Cell *aCell)
{
  int tColor = aCell->color;
  int tGroup = aCell->group;
//  std::cout << "building group for cell x,y,color,group: "
//      << aCell->location.row << "," << aCell->location.col << ","
//      << aCell->color << "," << aCell->group << std::endl;

  Cell *tCell;

  tCell = aCell->neighbors.top;
  extendGroup(tCell,tColor,tGroup);

  tCell = aCell->neighbors.right;
  extendGroup(tCell,tColor,tGroup);

  tCell = aCell->neighbors.bottom;
  extendGroup(tCell,tColor,tGroup);

  tCell = aCell->neighbors.left;
  extendGroup(tCell,tColor,tGroup);
}

void GameGrid::extendGroup(Cell *aCell,int aColor,int aGroup)
{
  if (aCell != NULL && aCell->group == NO_GROUP)
  {
    if (aCell->color == aColor)
    {
      aCell->group = aGroup;
      buildGroup(aCell);
    }
  }
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
      Cell *tCell = grid[r][c];
      std::cout << tCell->toString() << " ";
    }
    std::cout << std::endl;
  }
}
