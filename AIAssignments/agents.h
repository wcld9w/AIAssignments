using namespace std;

#ifndef AGENTS
#define AGENTS

  #include <vector>
  #include <string>
  #include<cstdlib>
  #include "gameFile.h"
  vector<string> randomPlacement(puzzleBoard inputBoard);
  vector<string> PlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard); 
  vector<string> BFSPlacementTrueTargetScore(puzzleBoard inputBoard, int score = 7);
  vector<string> iterativeDeepDepthFirstSearch(puzzleBoard inputBoard, int targetScore = 7);
  vector<string> bestFirstSearch(puzzleBoard inputBoard, int targetScore = 12);
  //Helper functions for best first search
  vector<string> reduceScore(vector<string> board, int x, int y);
#endif
