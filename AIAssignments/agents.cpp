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


vector<string> BFSPlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard)
{
  for (int i = 0; i < cowPos.size(); i++)
  {
    workingBoard[grassTileList[cowPos[i]].x][grassTileList[cowPos[i]].y] = 'C';
  }
  return workingBoard;
}


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
    //First we score the current board, the initialized values work for this and is a neat cheat code for how it was initialized
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

    //Get if we can move a cow, the cows at the start of the list are the cows at the back of the line. we prioritize moving the cows at the back
    int canMove = -1;
    for (int i = 0; i < currentCowNum; i++)
    {
      if (cowsList[i] != grassTileList.size() - (1 + i) && canMove == -1)
      {
        canMove = i;
      }
    }
    //If we can move a cow then we should move it and push following cows to the end
    if (canMove != -1)
    {
      cowsList[canMove] += 1;
      for (int i = canMove - 1; i >= 0; i--) //Move all preceding cows to follow the just moved cow, this is done because all preceding cows can not move, according to BFS we reset to continue
      {
        cowsList[i] = cowsList[i + 1] + 1;
      }
    }
    else
    {
      //We need to add a new cow
      currentCowNum += 1;
      //Check if we have hit max number of cows
      if (currentCowNum > maxNumOfCows)
      {
        cout << "ERROR desired score not possible returning original board without cows";
        return workingBoard;
      }
      //If we can add a new cow, initalize the cow position array correctly
      for (int i = 0; i < currentCowNum; i++)
      {
        cowsList[i] = currentCowNum - (i + 1);
      }
    }
  }
  //This return isn't ever reached, but included beacuse C++ throws a fit if no return statement at the end of the function
  return workingBoard;
}



