#ifndef LOCATION_HH_
#define LOCATION_HH_

class Location
{
public:
  int row;
  int col;
  Location();
  Location(int aRow,int aCol);
  Location(const Location &aLocation);
  virtual ~Location();
};

#endif /* LOCATION_HH_ */
