#include <iostream>
#include "GridUtil.hh"
#include "Snapshot.hh"
#include "Util.hh"

Snapshot::Snapshot()
{
  groupSeqNum = NO_GROUP;
}

Snapshot::Snapshot(std::string (&aRows)[10])
{
  groupSeqNum = NO_GROUP;

  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Cell &tCell = grid[r][c];
      tCell.empty = false;
      tCell.color = aRows[r][c];
      tCell.group = NO_GROUP;
    }
  }

  buildGroups();
}

/*
 * Constructor to build snapshot starting with...
 */
Snapshot::Snapshot(Cell (&aGrid)[ROWS][COLS])
{
  groupSeqNum = NO_GROUP;
  memcpy(grid, aGrid, sizeof(aGrid));
}

Snapshot::~Snapshot()
{
}

bool Snapshot::isGridEmpty()
{
  for (int i = 0; i < COLS; i++)
  {
    if (!isColumnEmpty(i))
      return false;
  }
  return true;
}

Snapshot Snapshot::deleteGroup(int aIndex)
{
  if (aIndex < 0 || aIndex >= groupList.size())
  {
    std::cout << "ERROR: Group index is invalid" << std::endl;
    exit(1);
  }

  Snapshot tSnapshot(grid);

  Group tGroup = groupList[aIndex];

  tSnapshot.deleteGroup(tGroup);
  tSnapshot.buildGroups();

  return tSnapshot;
}

//TODO checks for valid 2+ group
Snapshot Snapshot::deleteGroupAt(Location aLocation)
{
  Snapshot tSnapshot(grid);

  Group tGroup = getGroupAt(groupList,aLocation);

  if (tGroup.isEmpty())
  {
    std::cout << "ERROR: Couldn't find group at " << aLocation.toString() << std::endl;
    exit(1);
  }

//  std::cout << "Deleting group with id " << tGroup.id << " at " << aLocation.toString() << std::endl;

    tSnapshot.deleteGroup(tGroup);
    tSnapshot.buildGroups();

    return tSnapshot;
}

void Snapshot::clearGroups()
{
  groupSeqNum = NO_GROUP; //TODO

  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
      grid[r][c].group = NO_GROUP;

  groupList.clear();
}

void Snapshot::buildGroups()
{
  clearGroups();

  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      Location tLocation(r,c);
      Cell &tCell = grid[r][c];
      if (!tCell.empty && tCell.group == NO_GROUP)
      {
        int tGroupIdx = ++groupSeqNum;
        tCell.group = tGroupIdx;
        Group tGroup(tGroupIdx);
        tGroup.addLocation(tLocation);
        buildGroup(tLocation,tGroup);
        groupList.push_back(tGroup);
      }
    }
  }
}

void Snapshot::buildGroup(Location aLocation,Group &aGroup)
{
  Cell &tCell = grid[aLocation.row][aLocation.col];

  if (tCell.empty)
  {
    return;
  }

  int tColor = tCell.color;

//  std::cout << "building group for cell row,col,color,group: "
//      << aCell->location.row << "," << aCell->location.col << ","
//      << aCell->color << "," << aCell->group << std::endl;

  Location tLocation;

  tLocation = GridUtil::getLocationNorth(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = GridUtil::getLocationEast(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = GridUtil::getLocationSouth(aLocation);
  extendGroup(tLocation,tColor,aGroup);

  tLocation = GridUtil::getLocationWest(aLocation);
  extendGroup(tLocation,tColor,aGroup);
}

void Snapshot::extendGroup(Location aLocation,int aColor,Group &aGroup)
{
  if (aLocation.isValid())
  {
    Cell &tCell = grid[aLocation.row][aLocation.col];
    if (!tCell.empty && tCell.group == NO_GROUP)
    {
      if (tCell.color == aColor)
      {
        tCell.group = aGroup.id;
        aGroup.addLocation(aLocation);
        buildGroup(aLocation,aGroup);
      }
    }
  }
}

bool Snapshot::isColumnEmpty(int aCol)
{
  return (grid[ROWS-1][aCol].empty ? true:false);
}

void Snapshot::normalizeColumns()
{
  for (int tCol = COLS-2; tCol >= 0; tCol--)
  {
    if (isColumnEmpty(tCol))
    {
      deleteColumn(tCol);
    }
  }
}

/*
 * TODO can improve performance by keeping track of number of columns deleted
 * and not repeating empty end columns.
 */
void Snapshot::deleteColumn(int aCol)
{
  for (int tCol = aCol; tCol < COLS-1; tCol++)
  {
    for (int tRow = 0; tRow < ROWS; tRow++)
    {
      grid[tRow][tCol].empty = grid[tRow][tCol+1].empty;
      grid[tRow][tCol].color = grid[tRow][tCol+1].color;
    }
  }

  for (int tRow = 0; tRow < ROWS; tRow++)
  {
    grid[tRow][COLS-1].empty = true;
    grid[tRow][COLS-1].color = NO_COLOR;
  }
}

void Snapshot::deleteGroup(Group &aGroup)
{
  for (int tCol = 0; tCol < COLS; tCol++)
  {
    std::vector<int> tRowsToDelete = aGroup.getRowsForCol(tCol);
//Util::printVector(tRowsToDelete,"to delete:");

    std::vector<int>::iterator tIter;
    for (tIter = tRowsToDelete.begin(); tIter != tRowsToDelete.end(); tIter++ )
    {
      for (int tRow = *tIter; tRow >= 0; tRow--)
      {
        int tColor = getColorAt(Location(tRow-1,tCol));
//std::cout << "new color is " << tColor << std::endl;
        grid[tRow][tCol].color = tColor;
        if (tColor == NO_COLOR)
        {
          grid[tRow][tCol].empty = true;
        }
      }
    }
  }

  normalizeColumns();
}

int Snapshot::getColorAt(Location aLocation)
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

Group Snapshot::getGroupAt(GroupList &aGroups,Location aLocation)
{
  Group tGroup;

  int tRow = aLocation.row;
  int tCol = aLocation.col;

  GroupList::iterator tIter;
  for (tIter = aGroups.begin(); tIter != aGroups.end(); tIter++)
  {
    if (tIter->contains(aLocation))
    {
      tGroup = *tIter;
    }
  }

  if (tGroup.isEmpty())
  {
    std::cout << "ERROR: couldn't get group at "
        << tRow << "," << tCol << std::endl;
    exit(1);
  }

  return tGroup;
}

void Snapshot::printBoard(const char *aHeader)
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
  std::cout << "num groups nontriv,triv: "
      << groupList.getNumNonTrivialGroups() << ","
      << groupList.getNumTrivialGroups() << std::endl;
}

void Snapshot::printGroups(const char *aHeader)
{
  if (aHeader != NULL)
  {
    std::cout << aHeader << std::endl;
  }
  for (int i = 0; i < groupList.size(); i++)
  {
    std::cout << groupList[i].toString() << std::endl;
  }
}
