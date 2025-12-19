// tictactoe/tictactoe.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <stddef.h>  // for NULL.
#include <malloc.h>

#include "tictactoe.h"

int init_tictactoe(struct Tictactoe *pGame, const int size) {
  if (pGame == NULL) {
    // Game pointer is NULL, we can't use it.
    return -1;
  }

  if (size <= 0) {
    // Size can't be negative.
    return -1;
  }
  pGame->size = size;

  pGame->board = malloc(sizeof(struct Tictactoe *) * size);
  if (pGame->board == NULL) {
    // Malloc failed.
    return -1;
  }
  for (int i = 0; i < size; i++) {
    pGame->board[i] = malloc(sizeof(struct Tictactoe) * size);
    if (pGame->board[i] == NULL) {
      // Malloc failed.
      return -1;
    }
    for (int j = 0; j < size; j++) {
      pGame->board[i][j] = kEmpty;
    }
  }

  return 0;
}