#ifndef GAMEGRID_HH_
#define GAMEGRID_HH_

#include "Cell.hh"

#define ROWS 10
#define COLS 10

class GameGrid
{
public:

  Cell *grid[ROWS][COLS];

  GameGrid();

  virtual ~GameGrid();

  void buildGrid();

  void resetGrid();

private:

  int groupSeqNum;

  bool isTopLeftCorner(int aRow,int aCol);
  bool isTopRightCorner(int aRow,int aCol);
  bool isBottomLeftCorner(int aRow,int aCol);
  bool isBottomRightCorner(int aRow,int aCol);
  bool isTopRow(int aRow,int aCol);
  bool isBottomRow(int aRow,int aCol);
  bool isLeftCol(int aRow,int aCol);
  bool isRightCol(int aRow,int aCol);

  void setInitialNeighbors();

  void buildGroup(Cell *aCell);
  void extendGroup(Cell *aCell,int aColor,int aGroup);

  void deleteGroupAt(int aRow,int aCol);

  void printBoard(const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
