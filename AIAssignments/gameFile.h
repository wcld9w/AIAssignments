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
  #include<cstdlib>
  
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

    char getCordChar(cords desired);

  };


#endif

#ifndef SCOREINGFUNCTION
#define SCORINGFUNCTION
  int getScore(puzzleBoard board, int boardSize);
#endif // !SCOREINGFUNCTION

