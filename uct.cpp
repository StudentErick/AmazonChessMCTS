#include "uct.h"
#include <cmath>
#include <cstring>
#include <ctime>
#include <queue>
#include <vector>

UCT::UCT(int time, long num) {
  C = sqrt(2);       // 常数
  iteNum = 0;        // 假设是100次
  timeLimit = time;  // 限制时间
  AllNum = num;
  m_pMoveGenerator = new MoveGenerator;
  timeLimit = false;
}

UCT::~UCT() {
  delete m_pMoveGenerator;
  m_pMoveGenerator = nullptr;
}

void UCT::UCTSearch(int Board[10][10]) {
  memcpy(m_Board, Board, sizeof(m_Board));
  std::vector<ChessMove> RootMoveList;
  // 根节点产生步法
  m_pMoveGenerator->CreatePossibleMove(m_Board, BLACK, RootMoveList);
  for (auto& p : RootMoveList) {
    expand(p, BLACK);
  }
  auto bestMove = RootMoveList[0];
  for (auto& p : RootMoveList) {
    if (bestMove.prob > p.prob) {
      bestMove = p;
    }
  }
  MakeMove(bestMove, m_Board);
  memcpy(Board, m_Board, sizeof(m_Board));
}

void UCT::MakeMove(const ChessMove& move, int Board[10][10]) {
  Board[move.From.x][move.From.y] = EMPTY;
  Board[move.To.x][move.To.y] = move.ChessID;
  Board[move.Bar.x][move.Bar.y] = BARRIER;
}

void UCT::UnMakeMove(const ChessMove& move, int Board[10][10]) {
  Board[move.From.x][move.From.y] = move.ChessID;
  Board[move.To.x][move.To.y] = EMPTY;
  Board[move.Bar.x][move.Bar.y] = EMPTY;
}

/*  计算机永远是黑方
 *  黑方获胜返回1， 白方获胜返回0, 没结束返回0
 *  评估值永远是站在计算机的角度来看的
 * */
int UCT::IsGameOver(int Board[10][10], int side) {
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
  if (nBlack >= 4) {  // 黑方被堵死了
    if (side == BLACK) {
      return 0;
    } else {
      return 1;
    }
  } else if (nWhite >= 4) {  // 白方被堵死了
    if (side == WHITE) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return -1;
  }
}

void UCT::expand(ChessMove& move, int side) {
  int res = IsGameOver(m_Board, side);
  if (res != -1) {       // 游戏终止
    move.n_visited = 1;  // 访问过1次
    if (res == 0) {      // 当前走子方获胜
      move.prob = 1.0;
    } else {
      move.prob = 0.0;  // 对手获胜
    }
    move.v = 0.0;  // 没有孩子结点，肯定是0
    return;
  }
  MakeMove(move, m_Board);  // 模拟当前结点
  int sum_visited = 0;      // 所有结点的访问次数
  // 走法队列
  std::vector<ChessMove> MoveList;
  std::priority_queue<ChessMove, std::vector<ChessMove>, cmp> QMoveList;
  // 产生该节点的所有孩子结点，并返回个数
  int nChild = m_pMoveGenerator->CreatePossibleMove(m_Board, side, MoveList);
  for (auto& p : MoveList) {
    // 孩子结点先进行一次Rollout
    p.prob = RolloutOut(m_Board, side);
    QMoveList.push(p);
  }
  while (sum_visited < iteNum && timeLimit) {
    ++sum_visited;
    auto m = QMoveList.top();
    QMoveList.pop();
    m.is_expanded = true;
    m.n_visited += 1;
    // 计算结点的胜率
    m.prob = m.v + C * sqrt(2 * log(static_cast<double>(sum_visited)) /
                            static_cast<double>(m.n_visited));
    QMoveList.push(m);  // 重新入堆
  }
  double v = 0.0;
  for (auto& p : MoveList) {
    v += p.prob;
  }
  move.v = v / nChild;        // 计算孩子结点的均值
  UnMakeMove(move, m_Board);  // 恢复模拟
}

double UCT::RolloutOut(int Board[10][10], int side) {
  int board[10][10];
  memcpy(board, Board, sizeof(board));
  // s和side有区别，在评估的时候，初始的side不能变，而模拟的时候需要交替进行
  int s = side;
  while (IsGameOver(board, side) != -1) {
    std::vector<ChessMove> MoveList;
    // 生成队列
    m_pMoveGenerator->CreatePossibleMove(board, s, MoveList);
    unsigned long i =
        static_cast<unsigned long>(rand() % static_cast<int>(MoveList.size()));
    // 清空队列
    MoveList.clear();
    MakeMove(MoveList[i], board);
    s = -3 - s;  // 转换走子方
  }
  // 返回最终结果
  return IsGameOver(board, side);
}
