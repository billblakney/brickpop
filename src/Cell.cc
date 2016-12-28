#include <sstream>
#include "Cell.hh"

Cell::Cell()
{
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

