#include <sstream>
#include "Group.hh"

Group::Group(int aId)
{
  id = aId;
}

Group::~Group()
{
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

