// tictactoe/main.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <ncurses.h>

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

int main() {
  // ncurses Setup.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Exit ncurses mode.
  endwin();
}
