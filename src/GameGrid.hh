#ifndef GAMEGRID_HH_
#define GAMEGRID_HH_

#include "Cell.hh"

#define ROWS 10
#define COLS 10

class GameGrid
{
public:

  Cell grid[ROWS][COLS];

  GameGrid();

  virtual ~GameGrid();

  void buildGrid();

  void resetGrid();

private:

  int groupSeqNum;

  Location getLocationNorth(Location aLocation);
  Location getLocationEast(Location aLocation);
  Location getLocationSouth(Location aLocation);
  Location getLocationWest(Location aLocation);

  Location getLocationNorth(int aRow,int aCol);
  Location getLocationEast(int aRow,int aCol);
  Location getLocationSouth(int aRow,int aCol);
  Location getLocationWest(int aRow,int aCol);

  bool isTopLeftCorner(int aRow,int aCol);
  bool isTopRightCorner(int aRow,int aCol);
  bool isBottomLeftCorner(int aRow,int aCol);
  bool isBottomRightCorner(int aRow,int aCol);
  bool isTopRow(int aRow,int aCol);
  bool isBottomRow(int aRow,int aCol);
  bool isLeftCol(int aRow,int aCol);
  bool isRightCol(int aRow,int aCol);

//  void setInitialNeighbors();

  void buildGroup(Location aLocation);
  void extendGroup(Location aLocation,int aColor,int aGroup);

  void deleteGroupAt(Location aLocation);

  void printBoard(const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
