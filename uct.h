#ifndef UCT_H
#define UCT_H

#include "movegenerator.h"
#include "utils.h"

class UCT {
 public:
  /*
UCT();
~UCT();
void UCTSearch();

protected:
void expand(int side);              // 扩展博弈树
ChessMove &SelectChild();           // 返回孩子结点中胜率最大的
int RolloutOut(int Board[10][10]);  // 随机走子

static void MakeMove(const ChessMove &move, int Board[10][10]);
static void UnMakeMove(const ChessMove &move, int Board[10][10]);

// 黑方获胜返回1 白方返回-1 没结束返回0
static int IsGameOver(int Board[10][10], int side);

double getValue(const ChessMove &move, int side);  // 返回结点的评估分数

MoveGenerator *m_pMoveGenerator;
int m_Board[10][10];

struct cmp {
  bool operator()(const ChessMove &m1, const ChessMove &m2) {
    return m1.prob < m2.prob;
  }
};
*/
};

#endif  // UCT_H
