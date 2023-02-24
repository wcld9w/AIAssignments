#include "agents.h"
#include "gameFile.h"

using namespace std;

vector<string> randomPlacement(puzzleBoard inputBoard)
{
  int numOfCows = inputBoard.getHayBales();
  vector<string> workingBoard = inputBoard.getBoard();
  vector<cords> grassTileList;

  //Get a lit of all the open grass tiless
  for (int i = 0; i < inputBoard.getBoardSize(); i++)
  {
    for (int j = 0; j < inputBoard.getBoardSize(); j++)
    {
      if (workingBoard[i][j] == '.')
      {
        cords tempCords = { i, j };
        grassTileList.push_back(tempCords);
      }
    }
  }
  //Pick tiles until we no longer need any
  int numOfCowsRemaining = numOfCows;
  while (numOfCowsRemaining != 0)
  {
    int pickedCordNum = rand() % grassTileList.size();
    cords pickedCords = grassTileList[pickedCordNum];
    workingBoard[pickedCords.x][pickedCords.y] = 'C';
    grassTileList.erase(grassTileList.begin() + pickedCordNum);
    numOfCowsRemaining--; 
  }

  return workingBoard;
}


vector<string> BFSPlacement(puzzleBoard inputBoard)
{
  int numOfCows = inputBoard.getHayBales();

  vector<string> workingBoard = inputBoard.getBoard();
  vector<cords> grassTileList;

  //Get a lit of all the open grass tiless
  for (int i = 0; i < inputBoard.getBoardSize(); i++)
  {
    for (int j = 0; j < inputBoard.getBoardSize(); j++)
    {
      if (workingBoard[i][j] == '.')
      {
        cords tempCords = { i, j };
        grassTileList.push_back(tempCords);
      }
    }
  }



}