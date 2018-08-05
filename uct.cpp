#include "uct.h"
#include <cstring>
#include <ctime>
#include <random>

UCT::UCT(int limit) : limitTime(limit) {
  startTime = 0;
  curTime = 0;
}

UCT::~UCT() {}

void UCT::UCTSearch(int board[10][10]) {
  memcpy(Board, board, 10 * 10 * sizeof(int));
  if (Root != nullptr) {
    Root.reset();
  }
  Root = std::make_shared<TreeNode>(board);
  ChessMove m;
  std::time(&curTime);  // 搜索开始时间
  while (curTime - startTime < limitTime) {
    TreePolicy();  // TreePolicy中包含了Default操作
    auto p = Root->SelectBestChid();
    m = p->getCurMove();
    std::time(&curTime);  // 获取当前系统时间
  }
  MakeMove(m);  // 选择最佳的步法
  memcpy(board, Board, 10 * 10 * sizeof(int));
}

void UCT::TreePolicy() {
  auto p = Root;
  int res = GameKit::IsGemeOver(Board, p->getSide());
  while (res == -1) {
    if (p->isFullNode()) {
      auto t = p->AddChild();
      res = DefaultPolicy(t);  // rollout操作
      BackUp(t, res);
      break;
    }
    p = p->SelectBestChid();
    auto m = p->getCurMove();
    MakeMove(m);
    res = GameKit::IsGemeOver(Board, p->getSide());
  }
}

int UCT::DefaultPolicy(std::shared_ptr<TreeNode> node) {
  int board[10][10];
  memcpy(board, Board, sizeof(board));
  std::vector<ChessMove> MoveList;
  auto p = node;
  GameKit::CreatePossibleMove(board, p->getSide(), MoveList);
  std::default_random_engine random(static_cast<unsigned long>(std::time(0)));
  int player = node->getSide();
  int res = GameKit::IsGemeOver(board, player);
  while (res == -1) {
    std::uniform_int_distribution<int> dist(0,
                                            static_cast<int>(MoveList.size()));
    int t = dist(random);
    MakeMove(MoveList[static_cast<unsigned long>(t)]);
    MoveList.clear();
    player = -3 - player;
    GameKit::CreatePossibleMove(Board, player, MoveList);
    res = GameKit::IsGemeOver(Board, player);
  }
  return res;
}

void UCT::BackUp(std::shared_ptr<TreeNode> leaf_node, int res) {
  auto p = leaf_node;
  while (p->getParent() != nullptr) {
    p->update(res);
    UnMakeMove(p->getCurMove());
    p = p->getParent();
  }
}
