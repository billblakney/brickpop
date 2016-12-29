#ifndef GAMEGRID_HH_
#define GAMEGRID_HH_

#include <vector>
#include "brickpop_const.h"
#include "Cell.hh"
#include "Group.hh"
#include "Snapshot.hh"

class GameGrid
{
public:

  Snapshot snapshot;

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

  void clearGroups(Snapshot &aSnapshot);
  std::vector<Group> buildGroups(Snapshot &aSnapshot);
  void buildGroup(Snapshot &aSnapshot,Location aLocation,Group &aGroup);
  void extendGroup(Snapshot &aSnapshot,Location aLocation,int aColor,Group &aGroup);

  void deleteGroupAt(Snapshot &aSnapshot,std::vector<Group> &aGroup,Location aLocation);
  void deleteGroup(Snapshot &aSnapshot,Group &aGroup);
  Group getGroupAt(std::vector<Group> &aGroups,Location aLocation);
  int getColorAt(Snapshot &aSnapshot,Location aLocation);

  void printBoard(Snapshot &aSnapshot,const char *aHeader = NULL);
  void printGroups(std::vector<Group> &aGroups,const char *aHeader = NULL);
};

#endif /* GAMEGRID_HH_ */
