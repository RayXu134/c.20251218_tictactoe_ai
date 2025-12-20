// tictactoe/main.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <ncurses.h>

#include "tictactoe.h"

// -------------
// Main function
// -------------

int main() {
  // ncurses Setup.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  mvprintw(0, 0, "Initializing the game...\n");
  refresh();

  // The board size of the game.
  const int kBoardSize = 3;

  // Stores the return value of function.
  enum StatusCode status;

  // Setup the game struct.
  struct Tictactoe tictactoe;
  status = init_tictactoe(&tictactoe, kBoardSize);
  if (status != kOk) {
    // init_tictactoe error.
    endwin();
    perror("Error");
    return -1;
  }

  enum TictactoeWinner winner = kWinnerNone;
  int key;  // Stores the result of getchar().
  // Main game loop.
  bool is_running = true;
  while (winner == kWinnerNone && is_running) {
    clear();

    // Temporary stores a item in the board.
    int item;
    char item_in_char = '\0';
    // Shows the game board.
    for (int i = 0; i < tictactoe.size; i++) {
      for (int j = 0; j < tictactoe.size; j++) {
        item = tictactoe.board[i][j];
        if (item == kItemO) {
          item_in_char = 'O';
        } else if (item == kItemX) {
          item_in_char = 'X';
        } else {
          // Empty.
          item_in_char = '-';
        }
        mvprintw(i+1, j*3, "%c", item_in_char);
      }
    }

    refresh();

    key = getchar();
    switch (key) {
      case 'q':  // [fallthrough]
      case 'Q':
        // User wants to exit, ask again.
        mvprintw(0, 0, "Really exit? (y/n)");
        refresh();
        int key_want_exit = getchar();
        if (key_want_exit == 'y') {
          // Exit while loop.
          is_running = false;
        }
        break;
    }
  }

  // Exit ncurses mode.
  endwin();
  return 0;
}
