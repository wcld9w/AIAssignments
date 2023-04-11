#include "agents.h"
#include "gameFile.h"

using namespace std;



vector<string> PlaceCords(vector<cords> grassTileList, vector<int> cowPos, vector<string> workingBoard)
{
  for (int i = 0; i < cowPos.size(); i++)
  {
    workingBoard[grassTileList[cowPos[i]].x][grassTileList[cowPos[i]].y] = 'C';
  }
  return workingBoard;
}


//Places cows randomly
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

//Places cows according to BFS principles
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
    int tempScore = getScore(PlaceCords(grassTileList, tempList, workingBoard), boardSize);
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

//Places cows according to ID-DFS
vector<string> iterativeDeepDepthFirstSearch(puzzleBoard inputBoard, int targetScore)
{
  //Variable declarations
   //Get the number of cows we have to place
  int maxNumOfCows = inputBoard.getHayBales();
  //Input a board that we can edit without messing with the input board
  vector<string> workingBoard = inputBoard.getBoard();
  //A variable to hold all the tiles we consider open
  vector<cords> grassTileList = inputBoard.getGrassTileList();;
  //Variable to store the size of the board to reduce calls
  int boardSize = inputBoard.getBoardSize();
  //Variable to hold the current depth
  int curDepth = 1;
  //This is where we get absolutly bonkers
    //-1 indicates that the cow is not placed
  vector<int> cowsList(inputBoard.getHayBales(), -1);
  int lastDepth = 0;
  //Iterative Deepening depth first search

  while (true)
  {
    int lastCow = -1;
    for (int i = 0; i < curDepth; i++)
    {
      if (cowsList[i] != -1) lastCow = i;
    }
    //Compare current cow num to desired depth
    if (lastCow+1 < curDepth) //This looks wacky, but because lastCow starts at 0 (array indices) we need this
    {
      //if we need to go deeper
      //add a cow to the list
      //This ternary operation is used to inline deal with the discrepency of first cow vs adding all subsiquent cows
      cowsList[lastCow + 1] = lastCow == -1 ? 0 : cowsList[lastCow] + 1;
        //We can always add cows to end because we check for this when we go backwards in depth(VERY IMPORTANT, this allows us to optimize the checks somewhat skipping some repeat states)
    }
    else
    {
      //if we need to stay at current level (deepest)
      if (cowsList[lastCow] == grassTileList.size() - 1) //This checks if the last cow is able to be incremented
      {
        //If we need to go back
         //Loop to next location in DFS (the next cow that can be incremented, this is a logic replacement for function calls ending recusively backwards)
        int lastValidLocation = -1;
        for (int i = lastCow; i >= 0; i--)
        {
          if (cowsList[i] != grassTileList.size() - (1 + (lastCow-i)))
          {
            lastValidLocation = i;
            break;
          }
        }

        if (lastValidLocation != -1)//We can go back to a certain cow
        {
          //Increment the cow that we can move
          cowsList[lastValidLocation]++;
          //Check if we can place all following cows, else we can skip the rest of this loop

            //Reset all cows following the one we can move
            for (int i = lastValidLocation+1; i < curDepth; i++)
            {
              cowsList[i] = -1;
            }
          
        }
        if (lastValidLocation == -1)
        {
          //Check if we can increase the depth without going over the allowed number of cows
          if (curDepth + 1 > maxNumOfCows)
          {
            //If we cant then exit
            cout << "Error, not enough cow locations to get target score in given board, returning empty board";
            return workingBoard;
          }
          else
          {
            //Else we reset the cow list
            for (int i = 0; i < cowsList.size(); i++)
            {
              cowsList[i] = -1;
            }
            //And increase the depth
            curDepth++;
          }

        }
        
      }
      else
      {
        //If we don't need to do anything other than move to the next state we move to the next state
        cowsList[lastCow] += 1;
      }

    }

    //This generates the list of all cows that we can place
    vector<int> tempList;
    for (int i = 0; i < cowsList.size(); i++)
    {
      if (cowsList[i] != -1) tempList.push_back(cowsList[i]);
    }
    //Then we check the scores without editing the working board
    int tempScore = getScore(PlaceCords(grassTileList, tempList, workingBoard), boardSize);
    //If the score is equal to or exceeds our desired amount 
    if (tempScore >= targetScore)
    {
      //We actually place the cows and return the board
      for (int i = 0; i < tempList.size(); i++)
      {
        workingBoard[grassTileList[cowsList[i]].x][grassTileList[cowsList[i]].y] = 'C';
      }
      return workingBoard;
    }
  }
  //This return isn't ever reached, but included beacuse C++ throws a fit if no return statement at the end of the function I think, IDK i never checked because its easy to add one line instead of testing
  return workingBoard;
}


int getScoreOfLocation(vector<string> board, int x, int y)
{ 
  if (board[x][y] != '.') return INT_MIN+50; //We add 50 beacuse otherwise we could get an int underflow error if we try to reduce the location
  vector<char> cards = checkCard(puzzleBoard(board.size(), board), board.size(), "@#", x, y);
  vector<char> surr = check3x3(puzzleBoard(board.size(), board), board.size(), "C", x, y);
  bool foundHay = false;
  bool foundPond = false;
  bool foundCow = false;
  if (customCount(cards, '@')) foundHay = true;
  if (customCount(cards,  '#')) foundPond = true;
  if (customCount(surr, 'C')) foundCow = true;
  return (foundHay ? (foundPond ? 3 : 1) : 0) - (foundCow * 3);
}

vector<vector<int>> generateIntBoard(vector<string> getBoard)
{
  vector<vector<int>> tempBoard;
  for (int i = 0; i < getBoard.size(); i++)
  {
    vector<int> curLine;
    for (int j = 0; j < getBoard.size(); j++)
    {
      curLine.push_back(getScoreOfLocation(getBoard, i, j));
    }
    tempBoard.push_back(curLine);
  }
  return tempBoard;
}

cords getBestScore(vector<vector<int>> valueBoard)
{
  cords tempCords(0,0);
  for (int i = 0; i < valueBoard.size(); i++)
  {
    for (int j = 0; j < valueBoard.size(); j++)
    {
      if (valueBoard[tempCords.x][tempCords.y] < valueBoard[i][j])
      {
        tempCords.x = i;
        tempCords.y = j;
      }
    }
  }
  return tempCords;
}

vector<string> bestFirstSearch(puzzleBoard inputBoard, int targetScore)
{
  vector<string> tempBoard = inputBoard.getBoard();
  //First give each position score
  vector<vector<int>> intBoard = generateIntBoard(inputBoard.getBoard());
  for (int i = 0; i < inputBoard.getHayBales(); i++)
  {
    cords bestLoc = getBestScore(intBoard);
    tempBoard[bestLoc.x][bestLoc.y] = 'C';
    puzzleBoard temp(tempBoard.size(), tempBoard);
    temp.printBoard();
    intBoard = generateIntBoard(tempBoard);
  }
  return tempBoard;
}