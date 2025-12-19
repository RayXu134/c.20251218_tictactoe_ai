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

int make_move(struct Tictactoe *pGame, const int x, const int y, enum TictactoeItem item) {
  if (pGame == NULL) {
    // Game pointer is NULL.
    return -1;
  }
  if (x < 0 || x >= pGame->size || y < 0 || y >= pGame->size) {
    // Position out of range.
    return -1;
  }
  if (item == kEmpty) {
    // Item is empty, returns 0.
    return 0;
  }
  if (pGame->board[x][y] != kEmpty) {
    // The given position isn't empty.
    return -1;
  }
  pGame->board[x][y] = item;

  return 0;
}
