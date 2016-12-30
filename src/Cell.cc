#include <sstream>
#include "Cell.hh"

Cell::Cell()
{
  empty = true;
  color = NO_COLOR;
  group = NO_GROUP;
}

Cell::~Cell()
{
}

std::string Cell::toLongString()
{
  std::stringstream tStr;
  if (!empty)
  {
    tStr << color << "(" << group << ")";
  }
  else
  {
    tStr << "-(-)";
  }
  return tStr.str();
}

std::string Cell::toString()
{
  std::string tStr;
  if (!empty)
  {
    tStr += color;
  }
  else
  {
    tStr += '-';
  }
  return tStr;
}

