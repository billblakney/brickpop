#include <sstream>
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

bool Location::isValid()
{
  if (row != -1 && col != -1)
    return true;
  else
    return false;
}

std::string Location::toString()
{
  std::stringstream tStr;
  tStr << "(" << row << "," << col << ")";
  return tStr.str();
}
