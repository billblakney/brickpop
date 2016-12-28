#ifndef GROUP_HH_
#define GROUP_HH_

#include <string>
#include <vector>
#include "Location.hh"

class Group
{
public:
  int id;
  std::vector<Location> locations;
  Group(int id);
  virtual ~Group();
  std::string toString();
};

#endif /* GROUP_HH_ */
