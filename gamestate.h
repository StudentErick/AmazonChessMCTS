#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "utils.h"

class GameState {
 public:
  GameState();
  GameState(const GameState &state);  // 只复制父节点的棋盘状态
  // 产生所有可能的步法
  int CreatePossibleMove(int side, std::vector<ChessMove> &MoveList);
  int IsGameOver(int side);  // 1表示AI胜利，0表示人类胜利，-1表示未结束
  void DoMove(ChessMove &move);  // 走出父节点给的步法
  int m_Board[10][10];           // 棋盘状态
  int getMoveCount() const { return m_Count; }

 private:
  void CreatePossibleBar(int lx, int ly, int x, int y, int side,
                         std::vector<ChessMove> &MoveList);
  int m_Count;
};

#endif  // GAMESTATE_H
