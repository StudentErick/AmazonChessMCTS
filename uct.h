#ifndef UCT_H
#define UCT_H

#include "movegenerator.h"
#include "utils.h"

class UCT {
 public:
  UCT(int time, long num);  // 传入时间限制和总的步法限制
  ~UCT();
  void UCTSearch(int Board[10][10]);

 protected:
  // 扩展博弈树，返回子节点的的平均评估分数
  void expand(ChessMove &move, int side);
  // 随机走子
  double RolloutOut(int Board[10][10], int side);

  static void MakeMove(const ChessMove &move, int Board[10][10]);
  static void UnMakeMove(const ChessMove &move, int Board[10][10]);

  // 黑方获胜返回1 白方返回-1 没结束返回0
  static int IsGameOver(int Board[10][10], int side);

  double getValue(const ChessMove &move, int side);  // 返回结点的评估分数

  MoveGenerator *m_pMoveGenerator;
  int m_Board[10][10];
  double C;
  static int iteNum;   // 当前UCT模拟的次数
  static long AllNum;  // 总的UCT次数
  int timeLimit;       // 时间允许范围内

  struct cmp {
    bool operator()(const ChessMove &m1, const ChessMove &m2) {
      return m1.prob < m2.prob;
    }
  };
};

#endif  // UCT_H
