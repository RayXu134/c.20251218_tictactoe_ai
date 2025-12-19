// tictactoe/tictactoe.h
// Copyright (c) 2025 Ray. All Rights Reserved.

// @brief This has items in the tictactoe game board.
enum TictactoeItem {
  kO=0,
  kX,
  kEmpty
};

// @brief Who wins in the tictactoe game.
enum TictactoeWinner {
  kO = 0,
  kX,
  kNoWinner
};

// @brief Status code for functions.
enum StatusCode {
  kOk = 0,
  kErrorNullPointer,
  kErrorSizeIsInvalid,
  kErrorMalloc,
  kErrorPositionOutOfRange,
  kErrorPositionIsNotEmpty
};

// @brief Store everything in the tictactoe game.
// Initialize with init_tictactoe before using.
struct Tictactoe {
  // Board size.
  int size;
  // A 2d array stores items in the game.
  enum TictactoeItem **board;
};

// @brief Init a Tictactoe struct.
// @param size The size of the tictactoe game.
enum StatusCode init_tictactoe(struct Tictactoe *pGame, const int size);

// @brief Attempt to place a player's piece at a given position.
// If the given position is empty, this function place the piece
// to the given position (x, y).
// If item is kEmpty, this function won't do anything.
// And returns Ok.
enum StatusCode make_move(struct Tictactoe *pGame, const int x, const int y, enum TictactoeItem item);
