#ifndef GAMEGRID_HH_
#define GAMEGRID_HH_

#include <vector>
#include "Cell.hh"
#include "Group.hh"

#define ROWS 10
#define COLS 10

class GameGrid
{
public:

  Cell grid[ROWS][COLS];

  std::vector<Group*> groups;

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

  void clearGroups();
  void buildGroups();
  void buildGroup(Location aLocation,Group *aGroup);
  void extendGroup(Location aLocation,int aColor,Group *aGroup);

  void deleteGroupAt(Location aLocation);
  Group *getGroupAt(Location aLocation);
  int getColorAt(Location aLocation);

  void printBoard(const char *aHeader = NULL);
  void printGroups(const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
