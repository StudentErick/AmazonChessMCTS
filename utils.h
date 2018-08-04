#ifndef UTILS_H
#define UTILS_H

/*
 * 定义了一般的数据结构和方法
 */

#include <vector>

const int BLACK = -1;
const int WHITE = -2;
const int BARRIER = -3;
const int EMPTY = 0;
const double D_INF = 10000000.0;
const int INF = 10000000;
const double NOT_HIT_TARGET = 666666.0;
const double eps = 0.00000001;
const int BLACKWIN = 1;
const int WHITEWIN = 0;
const int NOTEND = -1;

// 8个偏移方向
const int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};

// 位置坐标
struct Pos {
  int x, y;
};
// 步法信息
struct ChessMove {
  Pos From;     // 起点坐标
  Pos To;       // 终点坐标
  Pos Bar;      // 障碍坐标
  int ChessID;  // 棋子的类型
  ChessMove() {}
  ChessMove(const ChessMove &move) {
    From.x = move.From.x;
    From.y = move.From.y;
    To.x = move.To.x;
    To.y = move.To.y;
    ChessID = move.ChessID;
  }
  bool operator==(const ChessMove &m) {
    return this->From.x == m.From.x && this->From.y == m.From.y &&
           this->To.x == m.To.x && this->To.y == m.To.y &&
           this->Bar.x == m.Bar.x && this->Bar.y == m.Bar.y &&
           this->ChessID == m.ChessID;
  }
};

class GameKit {
 public:
  // 产生的走法可能情况，存储到vector中
  static void CreatePossibleMove(int Board[10][10], int side,
                                 std::vector<ChessMove> &MoveList) {
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        if (Board[i][j] == side) {
          int k = i, l = j;
          for (int t = 0; t < 8; ++t) {
            k += offset[t][0];
            l += offset[t][1];
            while (k >= 0 && k < 10 && l >= 0 && l < 10 &&
                   Board[k][l] == EMPTY) {
              CreatePossibleBar(i, j, k, l, side, Board, MoveList);
              k += offset[t][0];
              l += offset[t][1];
            }
            k = i;
            l = j;
          }
        }
      }
    }
  }

  static int IsGemeOver(int Board[10][10], int side) {
    int nBlack = 0, nWhite = 0;  // 被堵死的棋子的数量
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        if (Board[i][j] != EMPTY && Board[i][j] != BARRIER) {
          int n = 0;
          // 8个方向判别
          for (int k = 0; k < 8; ++k) {
            int a = i + offset[k][0];
            int b = j + offset[k][1];
            if (a < 0 || a > 9 || b < 0 || b > 9 || Board[a][b] != EMPTY) {
              ++n;
            }
          }
          // 8个方向都被堵死，判别棋子的种类
          if (n >= 8) {
            if (Board[i][j] == BLACK) {
              ++nBlack;
            } else {
              ++nWhite;
            }
          }
        }
      }
    }
    if (side == BLACK && nBlack >= 4) {  // 黑方获胜返回1
      return BLACKWIN;
    } else if (side == WHITE && nWhite >= 4) {  // 白方获胜返回-1
      return WHITEWIN;
    } else {  // 未结束返回-1
      return NOTEND;
    }
  }

 private:
  // 产生所有的障碍个数
  static void CreatePossibleBar(int lx, int ly, int x, int y, int side,
                                int Board[10][10],
                                std::vector<ChessMove> &MoveList) {
    Board[lx][ly] = EMPTY;
    Board[x][y] = side;
    int k = x, l = y;
    // 遍历8个方向
    for (int t = 0; t < 8; ++t) {
      k += offset[t][0];
      l += offset[t][1];
      while (k >= 0 && k < 10 && l >= 0 && l < 10 && Board[k][l] == EMPTY) {
        ChessMove cm;
        cm.From.x = lx;
        cm.From.y = ly;
        cm.To.x = x;
        cm.To.y = y;
        cm.Bar.x = k;
        cm.Bar.y = l;
        cm.ChessID = side;
        MoveList.push_back(cm);
        k += offset[t][0];
        l += offset[t][1];
      }
      k = x;
      l = y;
    }
    Board[x][y] = EMPTY;
    Board[lx][ly] = side;
  }
};
#endif  // UTILS_H
