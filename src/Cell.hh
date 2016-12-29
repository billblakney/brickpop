#ifndef CELL_HH_
#define CELL_HH_

#include <string>
#include "brickpop_const.h"
#include "Location.hh"

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
