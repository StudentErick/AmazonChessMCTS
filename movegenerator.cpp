#include "MoveGenerator.h"
#include <cstring>
#include "utils.h"

MoveGenerator::MoveGenerator() { m_Count = 0; }

int MoveGenerator::CreatePossibleMove(int Board[10][10], int side,
                                      std::vector<ChessMove>& MoveList) {
  memcpy(m_Position, Board, 10 * 10 * sizeof(int));
  m_Count = 0;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (m_Position[i][j] == side) {
        int k = i, l = j;
        for (int t = 0; t < 8; ++t) {
          k += offset[t][0];
          l += offset[t][1];
          while (k >= 0 && k < 10 && l >= 0 && l < 10 &&
                 m_Position[k][l] == EMPTY) {
            CreatePossibleBar(i, j, k, l, side, MoveList);
            k += offset[t][0];
            l += offset[t][1];
          }
          k = i;
          l = j;
        }
      }
    }
  }
  return m_Count;
}

void MoveGenerator::CreatePossibleBar(int lx, int ly, int x, int y, int side,
                                      std::vector<ChessMove>& MoveList) {
  m_Position[lx][ly] = EMPTY;
  m_Position[x][y] = side;
  int k = x, l = y;
  // 遍历8个方向
  for (int t = 0; t < 8; ++t) {
    k += offset[t][0];
    l += offset[t][1];
    while (k >= 0 && k < 10 && l >= 0 && l < 10 && m_Position[k][l] == EMPTY) {
      ChessMove cm;
      cm.From.x = lx;
      cm.From.y = ly;
      cm.To.x = x;
      cm.To.y = y;
      cm.Bar.x = k;
      cm.Bar.y = l;
      cm.ChessID = side;
      MoveList.push_back(cm);

      ++m_Count;
      k += offset[t][0];
      l += offset[t][1];
    }
    k = x;
    l = y;
  }
  m_Position[x][y] = EMPTY;
  m_Position[lx][ly] = side;
}
