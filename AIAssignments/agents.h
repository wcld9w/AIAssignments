using namespace std;

#ifndef AGENTS
#define AGENTS

  #include <vector>
  #include <string>
  #include<cstdlib>
  #include "gameFile.h"
  vector<string> randomPlacement(puzzleBoard inputBoard);
  vector<string> BFSPlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard); 
  vector<string> BFSPlacement(puzzleBoard inputBoard);
  vector<string> BFSPlacementTrue(puzzleBoard inputBoard);
  vector<string> BFSPlacementTargetScore(puzzleBoard inputBoard, int score);
  vector<string> BFSPlacementTrueTargetScore(puzzleBoard inputBoard, int score);
#endif
