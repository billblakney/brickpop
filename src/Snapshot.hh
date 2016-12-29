#ifndef SNAPSHOT_HH_
#define SNAPSHOT_HH_

#include "brickpop_const.h"
#include "Cell.hh"
#include "Group.hh"

class Snapshot
{
public:

  Cell grid[ROWS][COLS];

  std::vector<Group> groups;

  Snapshot();

  virtual ~Snapshot();
};

#endif /* SNAPSHOT_HH_ */
