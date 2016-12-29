#include "GroupList.hh"

GroupList::GroupList()
{
}

GroupList::~GroupList()
{
}

int GroupList::getNumTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = begin(); tIter != end(); tIter++)
  {
    if (tIter->locations.size() == 1)
    {
      count++;
    }
  }
  return count;
}

int GroupList::getNumNonTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = begin(); tIter != end(); tIter++)
  {
    if (tIter->locations.size() > 1)
    {
      count++;
    }
  }
  return count;
}
