#include <algorithm>
#include <iostream>
#include <queue>
#include "utils.h"
using namespace std;

/*
├ ┼ ─ ┬ ┴ └ ┌ ┘ │
*/
void showBoard(int Board[10][10]) {
  std::cout << "    0   1   2   3   4   5   6   7   8   9" << endl;
  cout << "  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐" << endl;
  for (int i = 0; i < 10; ++i) {
    cout << i << " │";
    for (int j = 0; j < 10; ++j) {
      if (Board[i][j] == BLACK) {
        cout << " ○ │";
      } else if (Board[i][j] == WHITE) {
        cout << " ● │";
      } else if (Board[i][j] == BARRIER) {
        cout << " ▲ │";
      } else {
        cout << "   │";
      }
    }
    if (i != 9) {
      cout << "\n  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤" << endl;
    } else {
      cout << "\n  └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘" << endl;
    }
  }
}

void initBoard(int Board[10][10]) {
  Board[0][3] = WHITE;
  Board[0][6] = WHITE;
  Board[3][0] = WHITE;
  Board[3][9] = WHITE;
  Board[6][0] = BLACK;
  Board[6][9] = BLACK;
  Board[9][3] = BLACK;
  Board[9][6] = BLACK;
}

int main() {
  /*
vector<int> v({1, 2, 3, 4, 5});
for (auto &i : v) {
  cout << i << endl;
}
*/
  return 0;
}
