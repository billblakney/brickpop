#ifndef SNAPSHOT_HH_
#define SNAPSHOT_HH_

#include "brickpop_const.h"
#include "Cell.hh"
#include "GroupList.hh"

class Snapshot
{
public:

  Cell grid[ROWS][COLS];

//  std::vector<Group> groups;
  GroupList groupList;

  Snapshot();

  Snapshot (std::string (&aRows)[10]);

  virtual ~Snapshot();

  void clearGroups();
  void buildGroups();
  void buildGroup(Location aLocation,Group &aGroup);
  void extendGroup(Location aLocation,int aColor,Group &aGroup);

  Snapshot deleteGroupAt(Location aLocation);
  void deleteGroup(Group &aGroup);
  Group getGroupAt(GroupList &aGroups,Location aLocation);
  int getColorAt(Location aLocation);

  bool isColumnEmpty(int aCol);

  void normalizeColumns();

  void printBoard(const char *aHeader = NULL);

  void printGroups(const char *aHeader = NULL);

private:

  int groupSeqNum;

  void deleteColumn(int aCol);
};

#endif /* SNAPSHOT_HH_ */
