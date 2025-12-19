// tictactoe/main.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <ncurses.h>
#include <malloc.h>

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

// ---------------------
// Function declarations
// ---------------------

// @brief Init a Tictactoe struct.
// @param size The size of the tictactoe game.
// @return 0 when success. -1 when error.
int init_tictactoe(struct Tictactoe *pGame, const int size);

// -------------
// Main function
// -------------

int main() {
  // ncurses Setup.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Exit ncurses mode.
  endwin();
}

// ------------------------
// Function implementations
// ------------------------

int init_tictactoe(struct Tictactoe *pGame, const int size) {
  if (pGame == NULL) {
    // Game pointer is NULL, we can't use it.
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
