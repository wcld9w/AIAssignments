#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "agents.h"
#include "gameFile.h"

using namespace std;

//The function used to run when in grading mode
void runner()
{
  //We know we are going to get an input board size so get it and construct the board
  int boardSize = 0;
  cin >> boardSize;
  puzzleBoard temp(boardSize);

  //We are currently only doing random placement so runt he random placement and set it to the current board
  temp.setBoard(BFSPlacementTrueTargetScore(temp, 7), temp.getBoardSize());
  //Now we output what is needed for the grading
  cout << boardSize << endl;
  temp.printBoard();
  cout << getScore(temp, temp.getBoardSize());

}

//I use a function labeled runner because I am thinking about adding some logic to the main function to differenciate between running for grading and testing, currently not implemented but this makes it easier to implement in the future
int main()
{
  runner();

  return 0;
}
