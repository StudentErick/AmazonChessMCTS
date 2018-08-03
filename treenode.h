#ifndef TREENODE_H
#define TREENODE_H

#include <cmath>
#include <memory>
#include <queue>
#include <random>
#include <vector>
#include "gamestate.h"
#include "utils.h"

class TreeNode {
 public:
  TreeNode();
  TreeNode(const ChessMove& move, std::shared_ptr<TreeNode> par, int side,
           double childValue = 0.0, double puct = 1.0 / sqrt(2.0));
  std::shared_ptr<const TreeNode> getBestChild() const;
  void update(double res);
  void fullExpand();
  inline double getUCTValue() const { return m_uctValue; }
  inline int getVisitedCount() const { return n_visits; }
  inline std::shared_ptr<const TreeNode> getParent() const {
    return m_parent.lock();
  }
  inline bool isLeafNode() const { return isLeaf; }

 protected:
  double m_uctValue;
  struct cmp {
    bool operator()(TreeNode* m1, TreeNode* m2) {
      return m1->n_visits < m2->n_visits;
    }
  };
  bool isLeaf;
  GameState m_GameState;
  ChessMove curMove;                       // 获取父节点给的move
  std::weak_ptr<const TreeNode> m_parent;  // 父节点指针
  int n_visits;                            // 当前结点访问的次数
  double m_ChildValue;  // 孩子结点的评估值之和，如果是叶子结点就直接是1或者0
  double m_puct;  // 常数
  std::vector<std::shared_ptr<TreeNode>> m_ChildNodes;
  std::priority_queue<std::shared_ptr<TreeNode>,
                      std::vector<std::shared_ptr<TreeNode>>, cmp>
      QMoveQueue;
  int m_side;
};

#endif  // TREENODE_H
