// tictactoe/minimax.h
// Copyright (c) 2025 Ray. All Rights Reserved.

#ifndef TICTACTOE_MINIMAX_H_
#define TICTACTOE_MINIMAX_H_

#include "tictactoe.h"  // For struct Tictactoe, enum StatusCode.

// @brief Find the best move for the AI.
// The AI is 'X' and the player is 'O'.
// The result will be stored in *x and *y.
enum StatusCode find_best_move(struct Tictactoe *pGame, int *x, int *y);

#endif  // TICTACTOE_MINIMAX_H_
