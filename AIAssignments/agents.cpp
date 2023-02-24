#include "agents.h"
#include "gameFile.h"

using namespace std;

vector<string> randomPlacement(puzzleBoard inputBoard)
{
  //Variable declarations
    //Get the number of cows we have to place
  int numOfCows = inputBoard.getHayBales();
    //Input a board that we can edit without messing with the input board
  vector<string> workingBoard = inputBoard.getBoard();
    //A variable to hold all the tiles we consider open
  vector<cords> grassTileList;

  //Get a list of all the open grass tiless
  grassTileList = inputBoard.getGrassTileList();
  
  //Pick tiles until we no longer need any
  int numOfCowsRemaining = numOfCows;
    //While we can place cows
  while (numOfCowsRemaining != 0)
  {
    //Pick a random number from 0 to n, where n is equal to the number of grass tiles remaining
    int pickedCordNum = rand() % grassTileList.size();
    //Get the associated cordanites from the list and place a cow
    cords pickedCords = grassTileList[pickedCordNum];
    workingBoard[pickedCords.x][pickedCords.y] = 'C';
    //remove the tile from the list so we don't write multiple cows to the same tile
    grassTileList.erase(grassTileList.begin() + pickedCordNum);
    //We have placed a cow remove the tile
    numOfCowsRemaining--; 
  }

  return workingBoard;
}



//Unfinished function for puzzle assignment 2, started working on it then remebered I needed to actually submit assignment 1
vector<string> BFSPlacement(puzzleBoard inputBoard)
{
  int numOfCows = inputBoard.getHayBales();

  vector<string> workingBoard = inputBoard.getBoard();
  vector<cords> grassTileList;

  //Get a lit of all the open grass tiless
  grassTileList = inputBoard.getGrassTileList();
  //make list of cows with current positions
  //Move cow n by 1 increment starting from last cow
  //When cow n reaches final slot increase n-1 by 1
    //Push following cows
  //If at any point we reach final desired score, exit



  return workingBoard;
}





