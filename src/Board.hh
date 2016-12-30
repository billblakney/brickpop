#ifndef BOARD_HH_
#define BOARD_HH_

#include "brickpop_const.h"
#include "Cell.hh"
#include "GroupList.hh"

class Board
{
public:

//  std::vector<Group> groups;
  GroupList groupList;

  Board();

  Board (std::string (&aRows)[10]);

  virtual ~Board();

  bool isGridEmpty();

  Board deleteGroup(int aIndex);

  Board deleteGroupAt(Location aLocation);

  void deleteGroup(Group &aGroup);

  Group getGroupAt(GroupList &aGroups,Location aLocation);

  int getGroupIdFromIndex(int aGroupIndex);

  void printBoard(const char *aHeader = NULL,int aFormat = 0);

  void printGroups(const char *aHeader = NULL);

private:

  Cell grid[ROWS][COLS];

  int groupSeqNum;

  Board(Cell (&aGrid)[ROWS][COLS]);

  void buildGroups();
  void buildGroup(Location aLocation,Group &aGroup);
  void extendGroup(Location aLocation,int aColor,Group &aGroup);
  int getColorAt(Location aLocation);
  bool isColumnEmpty(int aCol);
  void normalizeColumns();
  void deleteColumn(int aCol);
  void clearGroups();
};

#endif /* BOARD_HH_ */
