#include "GridUtil.hh"

namespace GridUtil {

Location getLocationNorth(Location aLocation)
{
  return getLocationNorth(aLocation.row,aLocation.col);
}

Location getLocationEast(Location aLocation)
{
  return getLocationEast(aLocation.row,aLocation.col);
}

Location getLocationSouth(Location aLocation)
{
  return getLocationSouth(aLocation.row,aLocation.col);
}

Location getLocationWest(Location aLocation)
{
  return getLocationWest(aLocation.row,aLocation.col);
}

Location getLocationNorth(int aRow,int aCol)
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

Location getLocationEast(int aRow,int aCol)
{
  if (GridUtil::isRightCol(aRow, aCol))
  {
    return Location();
  }
  else
  {
    return Location(aRow,aCol+1);
  }
}

Location getLocationSouth(int aRow,int aCol)
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

Location getLocationWest(int aRow,int aCol)
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


bool isTopLeftCorner(int aRow,int aCol)
{
  if (aRow == 0 && aCol == 0)
    return true;
  else
    return false;
}

bool isTopRightCorner(int aRow,int aCol)
{
  if (aRow == 0 && aCol == COLS-1)
    return true;
  else
    return false;
}

bool isBottomLeftCorner(int aRow,int aCol)
{
  if (aRow == ROWS-1 && aCol == 0)
    return true;
  else
    return false;
}

bool isBottomRightCorner(int aRow,int aCol)
{
  if (aRow == ROWS-1 && aCol == COLS-1)
    return true;
  else
    return false;
}

bool isTopRow(int aRow,int aCol)
{
  if (aRow == 0)
    return true;
  else
    return false;
}

bool isBottomRow(int aRow,int aCol)
{
  if (aRow == ROWS-1)
    return true;
  else
    return false;
}

bool isLeftCol(int aRow,int aCol)
{
  if (aCol == 0)
    return true;
  else
    return false;
}

void resetGrid()
{
}

bool isRightCol(int aRow,int aCol)
{
  if (aCol == COLS-1)
    return true;
  else
    return false;
}

}
