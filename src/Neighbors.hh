#ifndef NEIGHBORS_HH_
#define NEIGHBORS_HH_

class Cell;

class Neighbors
{
public:
  Cell *top;
  Cell *bottom;
  Cell *left;
  Cell *right;

  Neighbors();
  Neighbors(const Neighbors &aNeighbors);
  Neighbors(Cell *aTop,Cell*aBottom,Cell *aLeft,Cell *aRight);
  virtual ~Neighbors();
private:
  void init();
};

#endif /* NEIGHBORS_HH_ */
