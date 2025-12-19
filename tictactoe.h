// tictactoe/tictactoe.h
// Copyright (c) 2025 Ray. All Rights Reserved.

// @brief This has items in the tictactoe game board.
enum TictactoeItem {
  kO=0,
  kX,
  kEmpty
};

// @brief Store everything in the tictactoe game.
struct Tictactoe {
  // Board size.
  int size;
  // A 2d array stores items in the game.
  enum TictactoeItem **board;
};

// @brief Init a Tictactoe struct.
// @param size The size of the tictactoe game.
// @return 0 when success. -1 when error.
int init_tictactoe(struct Tictactoe *pGame, const int size);
