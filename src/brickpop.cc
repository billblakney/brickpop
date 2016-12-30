#include <iostream>
#include "GameGrid.hh"

static std::string colors[ROWS];

void readColors(const char *fname);

int main(int argc,char **argv)
{
  readColors(argv[1]);
	GameGrid tGameGrid;
	tGameGrid.solve(colors);
	return 0;
}

#include <fstream>
#include <string>

void readColors(const char *fname)
{
  std::ifstream file(fname);
  std::string str;
  int i = 0;
  while (i < ROWS && std::getline(file, str))
  {
    std::cout << "setting i,str " << i << "," << str << std::endl;
    colors[i++] = str;
  }
}
