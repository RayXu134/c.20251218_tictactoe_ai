// tictactoe/minimax.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <stdbool.h>
#include <stddef.h>

#include "minimax.h"

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
