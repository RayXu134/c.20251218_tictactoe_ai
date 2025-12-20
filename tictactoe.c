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

  // calloc will initialize memories to 0, it's suitable for counters.
  pGame->row_sum = calloc(size, sizeof(int));
  pGame->col_sum = calloc(size, sizeof(int));

  // Manually reset the diagonal counters to 0.
  pGame->diag_sum[0] = 0;
  pGame->diag_sum[1] = 0;

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

// @brief Check winner.
enum StatusCode check_winner(struct Tictactoe *pGame, enum TictactoeWinner *winner) {
  if (pGame == NULL || winner == NULL) {
    // NULL pointer.
    return kErrorNullPointer;
  }
  // Reset counters.
  pGame->diag_sum[0] = 0;
  pGame->diag_sum[1] = 0;
  for (int i = 0; i < pGame->size; i++) {
    pGame->col_sum[i] = 0;
    pGame->row_sum[i] = 0;
  }
  // Sum rows and columns.
  for (int i = 0; i < pGame->size; i++) {
    for (int j = 0; j < pGame->size; j++) {
      pGame->row_sum[i] += pGame->board[i][j];
      pGame->col_sum[i] += pGame->board[j][i];
    }
  }
  // Sum diagonals.
  for (int i = 0; i < pGame->size; i++) {
    // Top-left to bottom-right.
    pGame->diag_sum[0] += pGame->board[i][i];
    // Top-right to bottom-left.
    pGame->diag_sum[1] += pGame->board[i][(pGame->size - 1) - i];
  }

  // Default winner is none.
  *winner = kWinnerNone;
  // Check summations.
  for (int i = 0; i < pGame->size; i++) {
    if (pGame->row_sum[i] == kWinnerO * pGame->size) {
      *winner = kWinnerO;
      break;
    } else if (pGame->row_sum[i] == kWinnerX * pGame->size) {
      *winner = kWinnerX;
      break;
    }
    if (pGame->col_sum[i] == kWinnerO * pGame->size) {
      *winner = kWinnerO;
      break;
    } else if (pGame->col_sum[i] == kWinnerX * pGame->size) {
      *winner = kWinnerX;
      break;
    }
  }
  if (*winner != kWinnerNone) {
    return kOk;
  }
  // Checks diagonal summations.
  for (int i = 0; i < 2; i++) {
    if (pGame->diag_sum[i] == kWinnerO * pGame->size) {
      *winner = kWinnerO;
      break;
    } else if (pGame->diag_sum[i] == kWinnerX * pGame->size) {
      *winner = kWinnerX;
      break;
    }
  }
  return kOk;
}
