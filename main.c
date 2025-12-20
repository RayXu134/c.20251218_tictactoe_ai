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

  if (has_colors() == false) {
    endwin();
    printf("Your terminal does not support color.");
    return -1;
  }

  enum TictactoeColorPair {
    kDefaultPair=1,
    kSelectedPair
  };
  start_color();
  use_default_colors();  // Use default colors of the terminal.
  init_pair(kDefaultPair, COLOR_WHITE, -1);
  init_pair(kSelectedPair, COLOR_YELLOW, -1);

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
  // Position of cursor.
  int cursor_x = 0;
  int cursor_y = 0;
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

        if (i == cursor_y && j == cursor_x) {
          // If this item is selected, use a special color pair.
          attron(COLOR_PAIR(kSelectedPair));
        }
        mvprintw(i*4+3, j*8+4, "%c", item_in_char);
        if (i == cursor_y && j == cursor_x) {
          // Turn off the color pair if needed.
          attroff(COLOR_PAIR(kSelectedPair));
        }
      }
    }

    refresh();

    key = getch();
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
