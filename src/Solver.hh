#ifndef SOLVER_HH_
#define SOLVER_HH_

#include <vector>
#include "brickpop_const.h"
#include "Board.hh"
#include "Cell.hh"
#include "Group.hh"

class Solver
{
public:

  Solver();

  virtual ~Solver();

  void solve(std::string (&aColors)[ROWS]);

  void replay(Board aSnapshot,std::vector<int> aGroupsReduced);

  void resetGrid();

private:

  int reduce(Board &aSnapshot,std::vector<int> &aGroupsReduced);
};

#endif /* SOLVER_HH_ */
