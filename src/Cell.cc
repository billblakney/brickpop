#include <sstream>
#include "Cell.hh"

Cell::Cell()
{
  color = -1;
  group = 0;
}

Cell::~Cell()
{
}

std::string Cell::toString()
{
  std::stringstream sStr;
  sStr << color << "(" << group << ")";
  return sStr.str();
}

