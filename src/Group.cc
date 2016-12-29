#include <sstream>
#include "Group.hh"

Group::Group()
{
  id = -1;
}

Group::Group(int aId)
{
  id = aId;
}

Group::~Group()
{
}

bool Group::isEmpty()
{
  return ((locations.size()==0) ? true:false);
}

void Group::addLocation(Location aLocation)
{
  locations.push_back(aLocation);
}

bool Group::contains(Location aLocation)
{
  std::vector<Location>::iterator tIter;
  for (tIter = locations.begin(); tIter != locations.end(); tIter++)
  {
    if (tIter->row == aLocation.row
     && tIter->col == aLocation.col)
      return true;
  }
  return false;
}

std::vector<int> Group::getRowsForCol(int aCol)
{
  std::vector<int> tCols;

  std::vector<Location>::iterator tIter;
  for (tIter = locations.begin(); tIter != locations.end(); tIter++)
  {
    if (tIter->col == aCol)
      tCols.push_back(tIter->row);
  }
  return tCols;
}

std::string Group::toString()
{
  std::stringstream tStr;
  tStr << "id=" << id << ":";
  std::vector<Location>::iterator tIter;
  for (tIter = locations.begin(); tIter != locations.end(); tIter++)
  {
    Location tLocation = *tIter;
    tStr << " " << tLocation.toString();
  }
  return tStr.str();
}

