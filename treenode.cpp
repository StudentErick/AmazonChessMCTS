#include "treenode.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include "utils.h"

TreeNode::TreeNode() {
  is_Leaf = false;
  Qsa = 0.0;
  nVisit = 0;
  nConst = 1 / sqrt(2.0);
  eval = D_INF;  // 根据论文的描述，可以把刚开辟的结点的评估值看成INF
  side = BLACK;
  is_full_expanded = false;
  is_Leaf = true;  // 新建的结点肯定是叶子结点
}

TreeNode::TreeNode(int board[10][10]) : Board(board) {
  is_Leaf = false;
  Qsa = 0.0;
  nVisit = 0;
  nConst = 1 / sqrt(2.0);
  eval = D_INF;  // 根据论文的描述，可以把刚开辟的结点的评估值看成INF
  side = BLACK;
  is_full_expanded = false;
  is_Leaf = true;  // 新建的结点肯定是叶子结点
}

TreeNode::TreeNode(const ChessMove& move, std::shared_ptr<TreeNode> parent,
                   double c, int board[10][10])
    : mParent(parent), curMove(move), nConst(c), Board(board) {
  side = -3 - parent->getSide();
  nVisit = 1;
  Qsa = 0;
  eval = 0.0;
  is_full_expanded = false;
  is_Leaf = true;
  // 新节点成立后，生成所有可能的步法
  GameKit::CreatePossibleMove(Board, side, UnTriedMove);
}

std::shared_ptr<TreeNode> TreeNode::AddChild() {
  is_Leaf = false;
  // 增加孩子结点，注意使用指针的动态转换
  auto p = std::shared_ptr<TreeNode>(this);
  mChildNodes.push_back(std::make_shared<TreeNode>(UnTriedMove[0], p, nConst));

  // 清除原来的孩子结点
  UnTriedMove.erase(
      std::remove(UnTriedMove.begin(), UnTriedMove.end(), UnTriedMove[0]));
  if (UnTriedMove.size() <= 0) {
    is_full_expanded = true;
  }
  std::weak_ptr<TreeNode> ptr = mChildNodes[mChildNodes.size() - 1];
  return ptr.lock();
}

void TreeNode::update(int z) {
  ++nVisit;
  Qsa += (z - Qsa) / nVisit;
  double n = static_cast<double>(mParent.lock()->getVisitedNum());
  // 公式是根据论文来的
  if (side == BLACK) {
    eval = Qsa + nConst * sqrt(log(n) / nVisit);
  } else {
    eval = Qsa - nConst * sqrt(log(n) / nVisit);
  }
}

std::shared_ptr<TreeNode> TreeNode::SelectBestChid() {
  double bestScore = mChildNodes[0]->getScore();
  std::weak_ptr<TreeNode> bestChild = mChildNodes[0];
  for (std::weak_ptr<TreeNode> p : mChildNodes) {
    double s = p.lock()->getScore();
    if (side == BLACK && bestScore > s) {
      bestChild = p;
    } else if (side == WHITE && bestScore < s) {
      bestChild = p;
    }
  }
  return bestChild.lock();
}
