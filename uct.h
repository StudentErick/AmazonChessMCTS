#ifndef UCT_H
#define UCT_H

#include <ctime>
#include "treenode.h"
#include "utils.h"
class UCT {
 public:
  UCT(int limit);
  ~UCT();
  void UCTSearch(int board[10][10]);

 private:
  void TreePolicy();
  int DefaultPolicy(std::shared_ptr<TreeNode> node);
  void BackUp(std::shared_ptr<TreeNode> leaf_node, int res);  // 从根节点回溯
  void MakeMove(ChessMove &move);
  void UnMakeMove(ChessMove &move);

  time_t startTime;
  time_t curTime;
  int limitTime;
  std::shared_ptr<TreeNode> Root;  // 根节点
  int Board[10][10];
};

#endif  // UCT_H
