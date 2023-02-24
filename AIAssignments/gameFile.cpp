#include "gameFile.h"

using namespace std;



int puzzleBoard::countHaybales()
{
  numOfHaybales = 0;
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      if (board[i][j] == '@') numOfHaybales++;
    }
  }
  return numOfHaybales;
}


puzzleBoard::puzzleBoard()
{
  cin >> boardSize;
  for (int i = 0; i < boardSize; i++)
  {
    string tempInput = "";
    cin >> tempInput;
    board.push_back(tempInput);
  }
  numOfHaybales = countHaybales();
}

puzzleBoard::puzzleBoard(int boardSizeInput)
{
  boardSize = boardSizeInput;
  for (int i = 0; i < boardSize; i++)
  {
    string tempInput = "";
    cin >> tempInput;
    board.push_back(tempInput);
  }
  numOfHaybales = countHaybales();
}

puzzleBoard::puzzleBoard(int boardSizeInput, vector<string> boardInput)
{
  board = boardInput;
  boardSize = boardSizeInput;
  numOfHaybales = countHaybales();
}

void  puzzleBoard::setBoard(vector<string> boardSet, int boardSizeSet)
{
  board = boardSet;
  boardSize = boardSizeSet;
}

void  puzzleBoard::printBoard()
{
  for (int i = 0; i < boardSize; i++)
  {
    cout << board[i] << endl;
  }
}

vector<string>  puzzleBoard::getBoard()
{
  return board;
}

int  puzzleBoard::getBoardSize()
{
  return boardSize;
}

int  puzzleBoard::getHayBales()
{
  return numOfHaybales;
}

char  puzzleBoard::getCordChar(cords desired)
{
  //First we check if the value is in the board
  if (desired.x >= 0 && desired.x < boardSize && desired.y >= 0 && desired.y < boardSize) return board[desired.x][desired.y];
  //If the desired square isn't inside the board we return null, this allows for some funky checking functionality
  return NULL;
}

vector<char> checkCard(puzzleBoard board, int boardSize, string checkList, int i, int j)
{
  vector<char> importantCharactersCard;
  string importantCharactersCardinalList = checkList;
  //I use this, frankly disgusting, for loop so that if new characters are needed to be checked it is a single line to add them
  for (int k = 0; k < 4; k++)
  {
    char tempChar;
    //Switch case to actually grab the correct cordinate
    switch (k)
    {
      //Inside each we check if the cord is valid by 
    case 0:
      tempChar = board.getCordChar(cords(i - 1, j));
      break;
    case 1:
      tempChar = board.getCordChar(cords(i + 1, j));
      break;
    case 2:
      tempChar = board.getCordChar(cords(i, j - 1));
      break;
    case 3:
      tempChar = board.getCordChar(cords(i, j + 1));
      break;

    }
    if (tempChar != NULL && importantCharactersCardinalList.find(tempChar) != string::npos)
    {
      importantCharactersCard.push_back(tempChar);
    }
  }
  return importantCharactersCard;
}

vector<char> check3x3(puzzleBoard board, int boardSize, string checkList, int i, int j)
{
  vector<char> importantCharactersBoth;
  string importantCharactersBothList = checkList;
  for (int k = 0; k < 8; k++)
  {
    char tempChar;
    //Switch case to actually grab the correct cordinate
    switch (k)
    {
      //Inside each we check if the cord is valid by 
    case 0:
      tempChar = board.getCordChar(cords(i - 1, j));
      break;
    case 1:
      tempChar = board.getCordChar(cords(i - 1, j + 1));
      break;
    case 2:
      tempChar = board.getCordChar(cords(i, j + 1));
      break;
    case 3:
      tempChar = board.getCordChar(cords(i + 1, j + 1));
      break;
    case 4:
      tempChar = board.getCordChar(cords(i + 1, j));
      break;
    case 5:
      tempChar = board.getCordChar(cords(i + 1, j - 1));
      break;
    case 6:
      tempChar = board.getCordChar(cords(i, j - 1));
      break;
    case 7:
      tempChar = board.getCordChar(cords(i - 1, j - 1));
      break;

    }
    if (tempChar != NULL && importantCharactersBothList.find(tempChar) != string::npos)
    {
      importantCharactersBoth.push_back(tempChar);
    }
  }
  return importantCharactersBoth;
}

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
        if (count(importantCharactersBoth.begin(), importantCharactersBoth.end(), 'C')) foundCow = true;
        if (count(importantCharactersCard.begin(), importantCharactersCard.end(), '@')) foundHay = true;
        if (count(importantCharactersCard.begin(), importantCharactersCard.end(), '#')) foundPond = true;

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