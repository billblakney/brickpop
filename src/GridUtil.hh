#ifndef GRIDUTIL_HH_
#define GRIDUTIL_HH_

#include "brickpop_const.h"
#include "Location.hh"

namespace GridUtil
{
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

}



#endif /* SRC_GRIDUTIL_HH_ */
