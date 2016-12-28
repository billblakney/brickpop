#ifndef CELL_HH_
#define CELL_HH_

#include <string>
#include "Location.hh"

#define NO_GROUP 0

class Cell
{
public:

  int color;

  int group;

  Cell();

  virtual ~Cell();

  std::string toString();
};

#endif /* CELL_HH_ */
