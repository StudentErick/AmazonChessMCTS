#include "gamestate.h"
#include <cstring>

GameState::GameState() { m_Count = 0; }

GameState::GameState(const GameState& state) {
  memcpy(this->m_Board, state.m_Board, sizeof(this->m_Board));
  m_Count = 0;
}

int GameState::CreatePossibleMove(int side, std::vector<ChessMove>& MoveList) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (m_Board[i][j] == side) {
        int k = i, l = j;
        for (int t = 0; t < 8; ++t) {
          k += offset[t][0];
          l += offset[t][1];
          while (k >= 0 && k < 10 && l >= 0 && l < 10 &&
                 m_Board[k][l] == EMPTY) {
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

void GameState::CreatePossibleBar(int lx, int ly, int x, int y, int side,
                                  std::vector<ChessMove>& MoveList) {
  m_Board[lx][ly] = EMPTY;
  m_Board[x][y] = side;
  int k = x, l = y;
  // 遍历8个方向
  for (int t = 0; t < 8; ++t) {
    k += offset[t][0];
    l += offset[t][1];
    while (k >= 0 && k < 10 && l >= 0 && l < 10 && m_Board[k][l] == EMPTY) {
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
  m_Board[x][y] = EMPTY;
  m_Board[lx][ly] = side;
}

void GameState::DoMove(ChessMove& move) {
  m_Board[move.From.x][move.From.y] = EMPTY;
  m_Board[move.To.x][move.To.y] = move.ChessID;
  m_Board[move.Bar.x][move.Bar.y] = BARRIER;
}

int GameState::IsGameOver(int side) {
  int nBlack = 0, nWhite = 0;  // 被堵死的棋子的数量
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (m_Board[i][j] != EMPTY && m_Board[i][j] != BARRIER) {
        int n = 0;
        // 8个方向判别
        for (int k = 0; k < 8; ++k) {
          int a = i + offset[k][0];
          int b = j + offset[k][1];
          if (a < 0 || a > 9 || b < 0 || b > 9 || m_Board[a][b] != EMPTY) {
            ++n;
          }
        }
        // 8个方向都被堵死，判别棋子的种类
        if (n >= 8) {
          if (m_Board[i][j] == BLACK) {
            ++nBlack;
          } else {
            ++nWhite;
          }
        }
      }
    }
  }
  if (nBlack >= 4) {
    if (side == BLACK) {
      return 1;
    } else {
      return 0;
    }
  } else if (nWhite >= 4) {
    if (side == WHITE) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return -1;
  }
}
