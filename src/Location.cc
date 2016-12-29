#include <sstream>
#include "Location.hh"

#define ROWS 10 //TODO where
#define COLS 10 //TODO where

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
  if (row >= 0 && row < ROWS
   && col >= 0 && col < COLS)
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
