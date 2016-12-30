#include <iostream>
#include "Util.hh"

namespace Util {

void printVector(std::vector<int> &aVector,const char *aHeader)
{
  std::cout << aHeader << std::endl;

  std::vector<int>::iterator tIter;
  for (tIter = aVector.begin(); tIter != aVector.end(); tIter++)
  {
    std::cout << " " << *tIter;
  }
  std::cout << std::endl;
}

}
