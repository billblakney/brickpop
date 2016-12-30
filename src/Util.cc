#include <iostream>
#include <sstream>
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

std::string toString(std::vector<int> aVector)
{
  std::stringstream tStr;

  std::vector<int>::iterator tIter;
  for (tIter = aVector.begin(); tIter != aVector.end(); tIter++)
  {
    tStr << *tIter << " ";
  }

  return tStr.str();
}

}
