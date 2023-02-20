
#include <iostream>
#include <vector>
#include <string>
#include<cstdlib>
#include "agents.h"
#include "gameFile.h"

using namespace std;

void runner()
{

  int boardSize = 0;
  cin >> boardSize;
  puzzleBoard temp(boardSize);

  temp.setBoard(randomPlacement(temp), temp.getBoardSize());
  cout << boardSize << endl;
  temp.printBoard();
  cout << getScore(temp, temp.getBoardSize());

}

int main()
{
  runner();

  return 0;
}
