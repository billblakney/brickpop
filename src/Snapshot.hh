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

  bool isColumnEmpty(int aCol);

  void normalizeColumns();

private:

  void deleteColumn(int aCol);
};

#endif /* SNAPSHOT_HH_ */
