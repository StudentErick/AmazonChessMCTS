#ifndef UCT_H
#define UCT_H

#include "treenode.h"
#include "utils.h"

class UCT {
 public:
  UCT();
  ~UCT();
  void TreePolicy();
  void DefaultPolicy();
  void BackUp();  // 从根节点回溯

 private:
  std::shared_ptr<TreeNode> Root;  // 根节点
  int Board[10][10];
};

#endif  // UCT_H
