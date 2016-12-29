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

  virtual ~Snapshot();

  void deleteGroupAt(GroupList &aGroup,Location aLocation);
  void deleteGroup(Group &aGroup);
  Group getGroupAt(GroupList &aGroups,Location aLocation);
  int getColorAt(Location aLocation);

  bool isColumnEmpty(int aCol);

  void normalizeColumns();

private:

  void deleteColumn(int aCol);
};

#endif /* SNAPSHOT_HH_ */
