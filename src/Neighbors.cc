#include <cstdlib>
#include "Neighbors.hh"

Neighbors::Neighbors()
{
  init();
}

Neighbors::Neighbors(const Neighbors &aNeighbors)
{
}

Neighbors::Neighbors(Cell *aTop,Cell*aBottom,Cell *aLeft,Cell *aRight)
{
  top = aTop;
  bottom = aBottom;
  left = aLeft;
  right = aRight;
}

Neighbors::~Neighbors()
{
}

void Neighbors::init()
{
  top = NULL;
  bottom = NULL;
  left = NULL;
  right = NULL;
}

