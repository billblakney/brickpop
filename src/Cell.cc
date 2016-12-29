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

std::string Cell::toString()
{
  std::stringstream sStr;
  if (!empty)
  {
    sStr << color << "(" << group << ")";
  }
  else
  {
    sStr << "-(-)";
  }
  return sStr.str();
}

