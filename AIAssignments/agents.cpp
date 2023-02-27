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

//Used to place the cows onto the board
vector<string> BFSPlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard)
{
  vector<string> temp = workingBoard;
  //For each cow we need to place
  for (int i = 0; i < cowPos.size(); i++)
  {
    //Places the cow where it needs to go
      //For each cow (i) use its int in the grass tile list to get associated cordinates
    temp[grassTileList[cowPos[i]].x][grassTileList[cowPos[i]].y] = 'C';
  }
  return temp;
}

//Breadth first search algorithm, assumes you must place each cow to achieve goal score so it shortcuts to having each cow on the board, finds highest possible score
vector<string> BFSPlacement(puzzleBoard inputBoard)
{
  int numOfCows = inputBoard.getHayBales();

  vector<string> workingBoard = inputBoard.getBoard();
  vector<cords> grassTileList = inputBoard.getGrassTileList();;
  vector<int> cowPos(inputBoard.getHayBales(), 0);
  //make list of cows with current positions
  for (int i = 0; i < cowPos.size(); i++)
  {
    //What this does is push each cow to the grass tile associated with its position (cow [0] to grass tile [0], cow [1] to grass tile [1])
    cowPos[i] = i;
  }
  //Now we start the actual loop

  vector<string> tempBoard;
  vector<string> currentTopBoard;
  bool canContinue = true;
  int currentMaxScore = INT_MIN;
  while (canContinue)
  {
    //check board score and update top score
    tempBoard = BFSPlaceCords(grassTileList, cowPos, workingBoard);
    if (currentMaxScore < getScore(tempBoard, inputBoard.getBoardSize()))
    {
      currentMaxScore = getScore(tempBoard, inputBoard.getBoardSize());
      currentTopBoard = tempBoard;
    }
    //Move cow n by 1 increment starting from last cow
    //When cow n reaches final slot increase n-1 by 1
      //Push following cows

    //Get the last cow in the list
    //If its not in final position
    if (cowPos[cowPos.size() - 1] != grassTileList.size() - 1)
    {
      //Move it forward one
      cowPos[cowPos.size() - 1] = cowPos[cowPos.size() - 1] + 1;
    }
    //Else
    else
    {
      int lastCowToPush = cowPos.size() - 1;
      //Check back recursivly for following final position cows
      while(lastCowToPush >= 0)
      {
        //This needs checked
        if (cowPos[lastCowToPush] != grassTileList.size()-1 - (cowPos.size() - 1 - lastCowToPush))
        {
          break;
        }
        lastCowToPush--;
      }
      //If all cows are at end, we exit
      if (lastCowToPush == -1) break;
      //Else find final cow at last position
        //Take cow previous and push forward one
      cowPos[lastCowToPush] += 1;
      //Push all cows for follow it
      for (int i = lastCowToPush+1; i < cowPos.size(); i++)
      {
        cowPos[i] = cowPos[i - 1] + 1;
      }

    }

  }
  return currentTopBoard;
}

vector<string> BFSPlacementTrue(puzzleBoard inputBoard)
{

}
vector<string> BFSPlacementTargetScore(puzzleBoard inputBoard, int score)
{

}
vector<string> BFSPlacementTrueTargetScore(puzzleBoard inputBoard, int score)
{

}





