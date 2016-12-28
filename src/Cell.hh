#ifndef CELL_HH_
#define CELL_HH_

#include <string>
#include "Location.hh"
#include "Neighbors.hh"

#define NO_GROUP 0

class Cell
{
public:

  int color;

  int group;

  Location origLocation;
  Neighbors origNeighbors;

  Location location;
  Neighbors neighbors;

  Cell();
  virtual ~Cell();

  std::string toString();
};

#endif /* CELL_HH_ */
