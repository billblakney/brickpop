#ifndef SNAPSHOT_HH_
#define SNAPSHOT_HH_

#include "brickpop_const.h"
#include "Cell.hh"
#include "GroupList.hh"

class Snapshot
{
public:

//  std::vector<Group> groups;
  GroupList groupList;

  Snapshot();

  Snapshot (std::string (&aRows)[10]);

  virtual ~Snapshot();

  bool isGridEmpty();

  Snapshot deleteGroup(int aIndex);

  Snapshot deleteGroupAt(Location aLocation);

  void deleteGroup(Group &aGroup);

  Group getGroupAt(GroupList &aGroups,Location aLocation);

  int getGroupIdFromIndex(int aGroupIndex);

  void printBoard(const char *aHeader = NULL);

  void printGroups(const char *aHeader = NULL);

private:

  Cell grid[ROWS][COLS];

  int groupSeqNum;

  Snapshot(Cell (&aGrid)[ROWS][COLS]);

  void buildGroups();
  void buildGroup(Location aLocation,Group &aGroup);
  void extendGroup(Location aLocation,int aColor,Group &aGroup);
  int getColorAt(Location aLocation);
  bool isColumnEmpty(int aCol);
  void normalizeColumns();
  void deleteColumn(int aCol);
  void clearGroups();
};

#endif /* SNAPSHOT_HH_ */
