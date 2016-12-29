#ifndef GROUP_HH_
#define GROUP_HH_

#include <string>
#include <vector>
#include "Location.hh"

#define COLS 10 //TODO

class Group
{
public:
  int id;
  std::vector<Location> locations;
  Group();
  Group(int id);
  virtual ~Group();
  bool isEmpty();
  void addLocation(Location aLocation);
  bool contains(Location aLocation);
  std::vector<int> getRowsForCol(int aCol);
  std::string toString();
};

#endif /* GROUP_HH_ */
