#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <vector>
#include "utils.h"

class MoveGenerator {
 public:
  MoveGenerator();
  ~MoveGenerator() {}
  // 产生的走法可能情况，存储到vector中
  int CreatePossibleMove(int Board[10][10], int side,
                         std::vector<ChessMove> &MoveList);

 private:
  // 产生所有的障碍个数
  void CreatePossibleBar(int lx, int ly, int x, int y, int side,
                         std::vector<ChessMove> &MoveList);
  // 复制棋盘
  int m_Position[10][10];
  // 步法总数
  int m_Count;
};

#endif  // MOVEGENERATOR_H
