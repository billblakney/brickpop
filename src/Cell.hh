#ifndef CELL_HH_
#define CELL_HH_

#include <string>
#include "Location.hh"

#define NUM_COLORS 4

#define NO_GROUP 0
#define NO_COLOR -1

class Cell
{
public:

  bool empty;

  int color;

  int group;

  Cell();

  virtual ~Cell();

  std::string toString();
};

#endif /* CELL_HH_ */
