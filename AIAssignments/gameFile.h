using namespace std;

#ifndef CORDS
#define CORDS
  struct cords {
    int x;
    int y;
    cords(int x, int y)
    {
      this->x = x;
      this->y = y;
    }
  };

#endif // !CORDS



#ifndef PUZZLEBOARD
#define PUZZLEBOARD
  #include <iostream>
  #include <vector>
  #include <string>
  #include <cstdlib>
  
  class puzzleBoard {
  private:
    vector<string> board;
    int boardSize;
    int numOfHaybales;

    int countHaybales();

  public:
    puzzleBoard();

    puzzleBoard(int boardSizeInput);
    puzzleBoard(int boardSizeInput, vector<string> boardInput);

    void setBoard(vector<string> boardSet, int boardSizeSet);

    void printBoard();

    vector<string> getBoard();

    int getBoardSize();

    int getHayBales();

    vector<cords> getListOfTile(char charToFind);
    vector<cords> getGrassTileList();

    char getCordChar(cords desired);

  };


#endif

#ifndef SCOREINGFUNCTION
#define SCORINGFUNCTION
  int customCount(vector<char> fromCount, char toCount);
  vector<char> checkTiles(puzzleBoard board, int boardSize, string checkList, vector<cords> cordsToCheck);
  vector<char> checkCard(puzzleBoard board, int boardSize, string checkList, int i, int j);
  vector<char> check3x3(puzzleBoard board, int boardSize, string checkList, int i, int j);
  int getScore(puzzleBoard board, int boardSize);
  int getScore(vector<string> board, int boardSize);
#endif // !SCOREINGFUNCTION

