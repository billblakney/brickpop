#include <iostream>
#include "Snapshot.hh"

Snapshot::Snapshot()
{
}

Snapshot::~Snapshot()
{
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

void Snapshot::deleteGroupAt(GroupList &aGroups,Location aLocation)
{
  Group tGroup = getGroupAt(aGroups,aLocation);

  if (tGroup.isEmpty())
  {
    std::cout << "ERROR: Couldn't find group at " << aLocation.toString() << std::endl;
    exit(1);
  }

//  std::cout << "Deleting group with id " << tGroup.id << " at " << aLocation.toString() << std::endl;

    deleteGroup(tGroup);
}

void Snapshot::deleteGroup(Group &aGroup)
{
  for (int tCol = 0; tCol < COLS; tCol++)
  {
    std::vector<int> tRowsToDelete = aGroup.getRowsForCol(tCol);

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
