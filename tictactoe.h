// tictactoe/tictactoe.h
// Copyright (c) 2025 Ray. All Rights Reserved.

#ifndef TICTACTOE_TICTACTOE_H_
#define TICTACTOE_TICTACTOE_H_

// @brief This has items in the tictactoe game board.
enum TictactoeItem {
  // For summation.
  kItemEmpty = 0,
  kItemO = 1,
  kItemX = -1
};

// @brief Who wins in the tictactoe game.
enum TictactoeWinner {
  kWinnerNone = 0,
  kWinnerO = 1,
  kWinnerX = -1,
  kWinnerTie = 2,
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
  int *row_sum;     // Row counter array.
  int *col_sum;     // Column counter array.
  int diag_sum[2];  // [0] for top-left to bottom-right.
                    // [1] for top-right to bottom-left.
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

// @brief Check winner.
// The result will store in *winner.
enum StatusCode check_winner(struct Tictactoe *pGame, enum TictactoeWinner *winner);

// @brief Convert enum TictactoeWinner to a char.
char winner_to_char(const enum TictactoeWinner winner);

#endif  // TICTACTOE_TICTACTOE_H_
