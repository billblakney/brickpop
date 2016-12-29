#include <sstream>
#include "Group.hh"

Group::Group(int aId)
{
  id = aId;
  for (int i = 0; i < COLS; i++)
    for (int j = 0; j < 2; j++)
      boundaries[i][j] = -1;
}

Group::~Group()
{
}

void Group::addLocation(Location aLocation)
{
  locations.push_back(aLocation);
#ifdef OLD
  int tCol = aLocation.col;
  int tRow = aLocation.row;

  int &tCurrentBottom = boundaries[tCol][0];
  if (tCurrentBottom == -1 || tCurrentBottom < tRow)
  {
    tCurrentBottom = tRow;
  }

  int &tCurrentTop = boundaries[tCol][1];
  if (tCurrentTop == -1 || tCurrentTop > tRow)
  {
    tCurrentTop = tRow;
  }
#endif
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

#ifdef OLD
int Group::getFirstToDeleteAtCol(int aCol)
{
  return boundaries[aCol][0];
}

int Group::getNumToDeleteAtCol(int aCol)
{
  if (boundaries[aCol][0] != -1)
  {
    return (boundaries[aCol][0] - boundaries[aCol][1] + 1);
  }
  else
  {
    return 0;
  }
}
#endif

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
  tStr << std::endl;
  for (int i = 0; i < COLS; i++)
  {
    tStr << "col" << i << " bot,top: " << boundaries[i][0] << ", " << boundaries[i][1] << std::endl;
  }
  return tStr.str();
}

