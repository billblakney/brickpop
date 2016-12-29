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

int Snapshot::getNumTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    if (tIter->locations.size() == 1)
    {
      count++;
    }
  }
  return count;
}

int Snapshot::getNumNonTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    if (tIter->locations.size() > 1)
    {
      count++;
    }
  }
  return count;
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
