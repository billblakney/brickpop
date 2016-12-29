/*
 * Snapshot.cc
 *
 *  Created on: Dec 28, 2016
 *      Author: Bill
 */

#include "Snapshot.hh"

Snapshot::Snapshot()
{
}

Snapshot::~Snapshot()
{
}

int Snapshot::getNumTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    if (tIter->locations.size() == 1)
    {
      count++;
    }
  }
  return count;
}

int Snapshot::getNumNonTrivialGroups()
{
  int count = 0;

  std::vector<Group>::iterator tIter;
  for (tIter = groups.begin(); tIter != groups.end(); tIter++)
  {
    if (tIter->locations.size() > 1)
    {
      count++;
    }
  }
  return count;
}

