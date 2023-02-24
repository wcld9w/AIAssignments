using namespace std;

#ifndef AGENTS
#define AGENTS

  #include <vector>
  #include <string>
  #include<cstdlib>
  #include "gameFile.h"
  vector<string> randomPlacement(puzzleBoard inputBoard);
  vector<string> BFSPlacement(puzzleBoard inputBoard);
#endif
