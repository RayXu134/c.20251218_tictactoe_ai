// tictactoe/tictactoe.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <stddef.h>  // for NULL.
#include <malloc.h>

#include "tictactoe.h"

enum StatusCode init_tictactoe(struct Tictactoe *pGame, const int size) {
  if (pGame == NULL) {
    // Game pointer is NULL, we can't use it.
    return kErrorNullPointer;
  }

  if (size <= 0) {
    // Size can't be negative.
    return kErrorSizeIsInvalid;
  }
  pGame->size = size;

  pGame->board = malloc(sizeof(struct Tictactoe *) * size);
  if (pGame->board == NULL) {
    // Malloc failed.
    return kErrorMalloc;
  }
  for (int i = 0; i < size; i++) {
    pGame->board[i] = malloc(sizeof(struct Tictactoe) * size);
    if (pGame->board[i] == NULL) {
      // Malloc failed.
      return kErrorMalloc;
    }
    for (int j = 0; j < size; j++) {
      pGame->board[i][j] = kItemEmpty;
    }
  }

  return kOk;
}

enum StatusCode make_move(struct Tictactoe *pGame, const int x, const int y, enum TictactoeItem item) {
  if (pGame == NULL) {
    // Game pointer is NULL.
    return kErrorNullPointer;
  }
  if (x < 0 || x >= pGame->size || y < 0 || y >= pGame->size) {
    // Position out of range.
    return kErrorPositionOutOfRange;
  }
  if (item == kItemEmpty) {
    // Item is empty, returns 0.
    return kOk;
  }
  if (pGame->board[x][y] != kItemEmpty) {
    // The given position isn't empty.
    return kErrorPositionIsNotEmpty;
  }
  pGame->board[x][y] = item;

  return kOk;
}
