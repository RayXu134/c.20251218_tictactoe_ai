// tictactoe/minimax.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <stdbool.h>
#include <stddef.h>

#include "minimax.h"
#include "tictactoe.h"

// You can only use this static function in this file.
// @brief Checks if there are any moves left on the board.
// @return True if there are moves left, false otherwise.
static int is_moves_left(struct Tictactoe *pGame) {
  if (pGame == NULL) {
    return false;
  }
  for (int i = 0; i < pGame->size; i++) {
    for (int j = 0; j < pGame->size; j++) {
      if (pGame->board[i][j] == kItemEmpty) {
        return true;
      }
    }
  }
  // If the loops complete without finding an empty cell, it means the
  // board is full.
  return false;
}

// @brief A recursive function to evaluate the
// score of a tictactoe board.
// Return 0 if an error occurs.
int minimax(struct Tictactoe *pGame, bool is_maximizing) {
  if (pGame == NULL) {
    return 0;
  }
  enum TictactoeWinner winner;
  enum StatusCode status = check_winner(pGame, &winner);
  if (status != kOk) {
    return 0;
  }
  if (winner == kWinnerX) {
    return 10;  // AI ('X') wins, return a positive score.
  } else if (winner == kWinnerO) {
    return -10;  // Player ('O') wins, return a negative score.
  } else if (winner == kWinnerTie) {
    return 0;  // It's a tie, return 0.
  }
  // The game is not over yet.
  if (is_maximizing) {
    // Maximizing.
    int best_score = -1000;
    for (int i = 0; i < pGame->size; i++) {
      for (int j = 0; j < pGame->size; j++) {
        if (pGame->board[i][j] != kItemEmpty) {
          continue;
        }
        enum TictactoeItem temp_item = pGame->board[i][j];
        pGame->board[i][j] = kItemX;  // AI is 'X'.
        int score = minimax(pGame, !is_maximizing);
        pGame->board[i][j] = temp_item;
        if (score > best_score) {
          best_score = score;
        }
      }
    }
    return best_score;
  } else {
    // Minimizing.
    int worst_score = 1000;
    for (int i = 0; i < pGame->size; i++) {
      for (int j = 0; j < pGame->size; j++) {
        if (pGame->board[i][j] != kItemEmpty) {
          continue;
        }
        enum TictactoeItem temp_item = pGame->board[i][j];
        pGame->board[i][j] = kItemO;  // Player is 'O'.
        int score = minimax(pGame, !is_maximizing);
        pGame->board[i][j] = temp_item;
        if (score < worst_score) {
          worst_score = score;
        }
      }
    }
    return worst_score;
  }
}
