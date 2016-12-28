#ifndef LOCATION_HH_
#define LOCATION_HH_

#include <string>

class Location
{
public:
  int row;
  int col;
  Location();
  Location(int aRow,int aCol);
  Location(const Location &aLocation);
  virtual ~Location();
  bool isValid();
  std::string toString();
};

#endif /* LOCATION_HH_ */
