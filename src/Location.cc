#include "Location.hh"

Location::Location()
{
  row = -1;
  col = -1;
}

Location::Location(const Location &aLocation)
{
  if (&aLocation != this)
  {
    row = aLocation.row;
    col = aLocation.col;
  }
}

Location::Location(int aRow,int aCol)
{
  row = aRow;
  col = aCol;
}

Location::~Location()
{
}
