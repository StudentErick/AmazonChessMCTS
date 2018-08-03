#include "treenode.h"
#include <algorithm>
#include <cmath>
#include <cstring>

TreeNode::TreeNode() {
  m_puct = 1.0 / sqrt(2.0);
  m_ChildValue = 0.0;
  isLeaf = false;
}

TreeNode::TreeNode(const ChessMove &move, std::shared_ptr<TreeNode> par,
                   int _side, double childValue, double puct)
    : m_GameState(par->m_GameState),
      curMove(move),
      m_parent(par),
      m_ChildValue(childValue),
      m_puct(puct),
      m_side(_side) {
  isLeaf = false;
}

std::shared_ptr<const TreeNode> TreeNode::getBestChild() const {
  auto p = QMoveQueue.top();
  return p;
}

void TreeNode::update(double res) {
  ++n_visits;
  m_ChildValue += res;
  auto par = m_parent.lock();
  m_uctValue = m_ChildValue / n_visits +
               m_puct * sqrt(2.0 * par->getVisitedCount() / n_visits);
}

void TreeNode::fullExpand() {
  m_GameState.DoMove(curMove);
  int flag = m_GameState.IsGameOver(m_side);
  if (flag != -1) {
    isLeaf = true;
    m_uctValue = static_cast<double>(flag);
  }
  std::vector<ChessMove> move;
  // m_GameState.CreatePossibleMove(m_side, )
}
