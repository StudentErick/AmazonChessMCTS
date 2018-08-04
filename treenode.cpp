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
  eval = 0.0;
  side = BLACK;
  is_full_expanded = false;
}

TreeNode::TreeNode(const ChessMove& move, std::shared_ptr<TreeNode> parent,
                   double c)
    : mParent(parent), curMove(move), nConst(c) {
  side = -3 - parent->getSide();
  nVisit = 1;
  Qsa = 0;
  eval = 0.0;
  is_full_expanded = false;
}

void TreeNode::AddChild() {
  if (is_full_expanded) {
    return;
  }

  // 增加孩子结点，注意使用指针的动态转换
  auto p = std::shared_ptr<TreeNode>(this);
  mChildNodes.push_back(std::make_shared<TreeNode>(UnTriedMove[0], p, nConst));

  // 清除原来的孩子结点
  UnTriedMove.erase(
      std::remove(UnTriedMove.begin(), UnTriedMove.end(), UnTriedMove[0]));
  if (UnTriedMove.size() <= 0) {
    is_full_expanded = true;
  }
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

std::weak_ptr<TreeNode> TreeNode::SelectBestChid() {
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
  return bestChild;
}
