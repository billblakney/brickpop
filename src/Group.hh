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
  int boundaries[COLS][2]; //TODO note on indexing
  std::vector<Location> locations;
  Group(int id);
  virtual ~Group();
  void addLocation(Location aLocation);
  int getFirstToDeleteAtCol(int aCol);
  int getNumToDeleteAtCol(int aCol);
  std::string toString();
};

#endif /* GROUP_HH_ */
