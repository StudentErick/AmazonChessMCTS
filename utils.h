#ifndef UTILS_H
#define UTILS_H
// 棋子等的数据标示
const int BLACK = -1;
const int WHITE = -2;
const int BARRIER = -3;
const int EMPTY = 0;
const double D_INF = 10000000.0;
const int INF = 10000000;
const double NOT_HIT_TARGET = 666666.0;
const double eps = 0.00000001;

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
  ChessMove(const ChessMove& move) {
    From.x = move.From.x;
    From.y = move.From.y;
    To.x = move.To.x;
    To.y = move.To.y;
    ChessID = move.ChessID;
  }
};

#endif  // UTILS_H
