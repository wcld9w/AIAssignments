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

//Used to place the cows onto the board for easy scoring without editing the existing board
vector<string> PlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard)
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

//This is 
vector<string> BFSPlacementTrueTargetScore(puzzleBoard inputBoard, int score)
{
  //Variable declarations
   //Get the number of cows we have to place
  int maxNumOfCows = inputBoard.getHayBales();
  //Input a board that we can edit without messing with the input board
  vector<string> workingBoard = inputBoard.getBoard();
  //A variable to hold all the tiles we consider open
  vector<cords> grassTileList;
  //Variables to assist in breadth first search
  vector<int> cowsList(inputBoard.getHayBales(), 0);;
  int currentCowNum = 1;
  //Variable to store the size of the board to reduce calls
  int boardSize = inputBoard.getBoardSize();
  //Get a list of all the open grass tiless
  grassTileList = inputBoard.getGrassTileList();


  while (true)
  {
    //Check scores of current cow placement
      //First we generate a temporary list to store which cows we care about
    vector<int> tempList;
    for (int i = 0; i < currentCowNum; i++)
    {
      tempList.push_back(cowsList[i]);
    }
      //Then we check the scores without editing the working board
    int tempScore = getScore(BFSPlaceCords(grassTileList, tempList, workingBoard), boardSize);
      //If the score is equal to or exceeds our desired amount 
    if (tempScore >= score)
    {
      //We actually place the cows and return the board
      for (int i = 0; i < currentCowNum; i++)
      {
        workingBoard[grassTileList[cowsList[i]].x][grassTileList[cowsList[i]].y] = 'C';
      }
      return workingBoard;
    }
    //This gets the first cow in our list that can be moved
    int canMove = -1;
    for (int i = 0; i < currentCowNum; i++)
    {
      if (cowsList[0] != grassTileList.size() - (1 + i)) canMove = true;
    }
    //if its -1, we need to increase cow count, as we can not move any cows
    if(canMove == -1)
    {
      //This increases the cows
      currentCowNum += 1;
      //This is error handling if the number of cows exceeds maximum, prevents the code from going infinite as well if the input is not possible
      if (currentCowNum > maxNumOfCows)
      {
        cout << "Error, the given board can not have the needed score";
        return workingBoard;
      }
      //And this resets the cows to the correct location
      for (int i = 0; i < currentCowNum; i++)
      {
        cowsList[i] = currentCowNum - 1;
      }
    }
    //Else we just need to move the cow found forward, and cows previous to infront of it
    else
    {
      //For the cow that we can move, we move it forward one tile
      cowsList[canMove] += 1;
      //And for all following cows the move them to follow the previous cow
      for (int i = canMove - 1; i >= 0; i--)
      {
        cowsList[i] = cowsList[i+1] + 1;
      }
    }
  }


  return workingBoard;

}





