#include "gameFile.h"

using namespace std;



//This function returns a list of all grass tiles
vector<cords> puzzleBoard::getGrassTileList()
{
  //Orignally all the functionality was stored in this function, but I moved it to another function that is more general to allow more functionality later if needed
  return getListOfTile('.');
}

//This function returns a list of all cords of the input character 
vector<cords> puzzleBoard::getListOfTile(char charToFind)
{
  //Make a list to store as we go
  vector<cords> tempList;
  //For each tile in the board
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      //Check if it is a desired character
      if (board[i][j] == charToFind)
      {
        //If it is then we make a temp variable and push it back, I could do this in one line but I don't think its needed
        cords tempCords = { i, j };
        tempList.push_back(tempCords);
      }
    }
  }
  return tempList;
}

//A simple function that iterates over all the tiles and counts the haybales
int puzzleBoard::countHaybales()
{
  //We can use a neat trick here with the get list of tile function, where if we find the cords of all the haybales we can just count the number of cords
  return getListOfTile('@').size();
}

//A constructor function for 0 arguments, generates a board from console
puzzleBoard::puzzleBoard()
{
  //Get the desired board size
  cin >> boardSize;
  //For each row in the board
  for (int i = 0; i < boardSize; i++)
  {
    //Get the input string
    string tempInput = "";
    cin >> tempInput;
    //and set it as the row for the board
    board.push_back(tempInput);
  }
  //Set the count of the haybales so we don't need to recalculate
  numOfHaybales = countHaybales();
}

//A constructor for 1 int argument equal to the desired board size
puzzleBoard::puzzleBoard(int boardSizeInput)
{
  //Set the board size from argument
  boardSize = boardSizeInput;
  //For each row in the board
  for (int i = 0; i < boardSize; i++)
  {
    //Get the input string
    string tempInput = "";
    cin >> tempInput;
    //and set it as the row for the board
    board.push_back(tempInput);
  }
  //Set the count of the haybales so we don't need to recalculate
  numOfHaybales = countHaybales();
}

//A constructor for a board, we require size for simplicity
puzzleBoard::puzzleBoard(int boardSizeInput, vector<string> boardInput)
{
  //Take inputs and assign to already existing information
  board = boardInput;
  boardSize = boardSizeInput;
  //Set the count of the haybales so we don't need to recalculate
  numOfHaybales = countHaybales();
}

//A simple board setter function
void  puzzleBoard::setBoard(vector<string> boardSet, int boardSizeSet)
{
  board = boardSet;
  boardSize = boardSizeSet;
}

//A function to print the board to console
void  puzzleBoard::printBoard()
{
  for (int i = 0; i < boardSize; i++)
  {
    cout << board[i] << endl;
  }
}

//A getter for the board
vector<string>  puzzleBoard::getBoard()
{
  return board;
}

//A getter for the board size
int  puzzleBoard::getBoardSize()
{
  return boardSize;
}

//A getter for the number of haybales
int  puzzleBoard::getHayBales()
{
  return numOfHaybales;
}

//A function utilized for getting the character at the specified cordinates
//If the cordinate requested is outside the board we return null, signaling that we are outside the board
char  puzzleBoard::getCordChar(cords desired)
{
  //First we check if the value is in the board
  if (desired.x >= 0 && desired.x < boardSize && desired.y >= 0 && desired.y < boardSize) return board[desired.x][desired.y];
  //If the desired square isn't inside the board we return null, this allows for some funky checking functionality
  return NULL;
}

//A function that checks certain cordinates for characters in a list that is passed in
vector<char> checkTiles(puzzleBoard board, int boardSize, string checkList, vector<cords> cordsToCheck)
{
  vector<char> listOfChars;
  for (int k = 0; k < cordsToCheck.size(); k++)
  {

    char tempChar;
    tempChar = board.getCordChar(cordsToCheck[k]);

    if (tempChar != NULL && checkList.find(tempChar) != string::npos)
    {
      listOfChars.push_back(tempChar);
    }
  }
  return listOfChars;
}


//A function that acts as an overhead for the check tiles function to specify we are looking at cardinal directions only
vector<char> checkCard(puzzleBoard board, int boardSize, string checkList, int i, int j)
{
  //A list of cordinates that we are looking for
  vector<cords> toCheck{ {i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1 } };
  
  return checkTiles(board, boardSize, checkList, toCheck);
}

//A function that acts as an overhead for the check tiles functio to specify we are looking in a 3x3 around the tile
vector<char> check3x3(puzzleBoard board, int boardSize, string checkList, int i, int j)
{
  //A list cordinates 3x3 around the tile we care about
  vector<cords> toCheck{ {i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1 }, {i - 1, j - 1},  {i - 1, j + 1},  {i + 1, j - 1},  {i + 1, j + 1} };
  
  return checkTiles(board, boardSize, checkList, toCheck);
}



//For some reason the linux machines on campus were giving errors about the c++ count() so I had to make a custom one for scoring purposes. 
int customCount(vector<char> fromCount, char toCount)
{
  int count = 0;
  for (int i = 0; i < fromCount.size(); i++)
  {
    if (fromCount[i] == toCount) count++;
  }
  return count;
}




//The actual scoring function
int getScore(puzzleBoard board, int boardSize)
{

  int totalScore = 0;
  //This is a double loop to check every tile to see if it contains an element we need to score for
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      //We need to score each cow
      if (board.getCordChar(cords(i,j)) == 'C')
      {
        //Ive made the following code so that in the future it is easy to add characters to specific direction sensing. 
        //First we check each cardinal direction
        
        vector<char> importantCharactersCard = checkCard(board, boardSize, "@#", i, j);
        

        //Then we check each direction surrounding the cow in a square, this is needed to check for cows. (both refers to diagnals and cardinals)
        vector<char> importantCharactersBoth = check3x3(board, boardSize, "C", i, j);;
        
        //Now that we have the lists we can actully score the cow
        //This is bool variable for if we have the cows
        bool foundCow = false;
        bool foundHay = false;
        bool foundPond = false;
        //We count the occurances and treat it as a bool, doing the equivalent of  >= 0, which works for what we currently need
        if (customCount(importantCharactersBoth, 'C')) foundCow = true;
        if (customCount(importantCharactersCard,  '@')) foundHay = true;
        if (customCount(importantCharactersCard, '#')) foundPond = true;

        //Associating the found with the scores, we seperate and put the actual scoring here as it makes it easy to not count multiple sets of hay
        int tempCowScore = 0;
        if (foundCow) tempCowScore -= 3;
        if (foundHay)
        {
          if (foundPond) tempCowScore += 3;
          else tempCowScore += 1;
        }
        //We add the score finally to the total, and we move on to the next hex
        totalScore += tempCowScore;
      }
    }
  }
  return totalScore;
}

int getScore(vector<string> board, int boardSize)
{
  puzzleBoard temp(boardSize, board);
  //temp.printBoard();
  //cout << " ---------------- " << endl;
  return getScore(temp, boardSize);
}