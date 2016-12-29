#ifndef SRC_GROUPLIST_HH_
#define SRC_GROUPLIST_HH_

#include <vector>
#include "Group.hh"

class GroupList : public std::vector<Group>
{
public:
  GroupList();
  virtual ~GroupList();
  int getNumTrivialGroups();
  int getNumNonTrivialGroups();
};

#endif /* SRC_GROUPLIST_HH_ */
