#ifndef TREENODE_H
#define TREENODE_H

#include <array>
#include <cmath>
#include <memory>
#include <queue>
#include <random>
#include <vector>
#include "utils.h"

class TreeNode {
 public:
  TreeNode();
  TreeNode(int board[10][10]);
  TreeNode(const ChessMove& move, std::shared_ptr<TreeNode> parent, double c,
           int board[10][10]);
  std::shared_ptr<TreeNode> AddChild();        // 扩展孩子节点
  std::shared_ptr<TreeNode> SelectBestChid();  // 选择最佳的孩子
  void expandNode();
  void update(int z);

  int getSide() const { return side; }
  int getVisitedNum() const { return nVisit; }
  double getScore() const { return eval; }
  ChessMove& getCurMove() { return curMove; }
  std::shared_ptr<TreeNode> getParent() const { return mParent.lock(); }
  bool isLeaf() const { return is_Leaf; }
  bool isFullNode() const { return is_full_expanded; }

 private:
  std::weak_ptr<TreeNode> mParent;                     // 父节点
  std::vector<std::shared_ptr<TreeNode>> mChildNodes;  // 孩子结点
  std::vector<ChessMove> UnTriedMove;                  // 未访问的结点
  std::array<std::array<int, 10>, 10> A;               // 表示棋盘
  ChessMove curMove;      // 父节点传入的步法
  double Qsa;             // 评估数据
  double eval;            // 最终评估值
  bool is_Leaf;           // 叶子结点的标记
  int side;               // 当前的走子方
  bool is_full_expanded;  // 完全展开
  int nVisit;             // 访问的次数
  double nConst;          // 常数
  int (*Board)[10];       // 接收父节点的棋盘
};

#endif  // TREENODE_H
