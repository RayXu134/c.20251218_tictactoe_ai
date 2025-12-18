// tictactoe/main.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <ncurses.h>

int main() {
  // ncurses Setup.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Exit ncurses mode.
  endwin();
}
