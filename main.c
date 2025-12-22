// tictactoe/main.c
// Copyright (c) 2025 Ray. All Rights Reserved.

#include <ncurses.h>
#include <time.h>

#include "tictactoe.h"
#include "minimax.h"

enum TictactoeColorPair {
  kDefaultPair=1,
  kSelectedPair
};

enum TictactoeGameMode {
  kPvpMode=1,
  kPveMode
};

// @brief Show game board.
// It will show the selected item in a special color.
void show_game_board(const struct Tictactoe *pGame, const int cursor_x, const int cursor_y);

// @brief Convert a enum TictactoeGameMode to a string.
char *mode_to_string(const enum TictactoeGameMode mode);

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

  start_color();
  use_default_colors();  // Use default colors of the terminal.
  init_pair(kDefaultPair, COLOR_WHITE, -1);
  init_pair(kSelectedPair, COLOR_RED, -1);

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

  // Ask for game mode.
  int mode = kPvpMode;  // Default mode is Pvp mode.
  {
    int key;
    bool selecting = true;
    while (selecting) {
      clear();
      mvprintw(0, 0, "Choose a mode");
      mvprintw(1, 0, "(use the up, down arrow keys, space to select, q to quit)");
      // Print mode options (with highlight).
      for (int i = 1; i <= 2; i++) {
        if (i == mode) {
          attron(COLOR_PAIR(kSelectedPair));
        }
        mvprintw(i+1, 2, "- %s", mode_to_string(i));
        if (i == mode) {
          attroff(COLOR_PAIR(kSelectedPair));
        }
      }
      refresh();
      key = getch();
      switch (key) {
        case 'q':  // [fallthrough]
        case 'Q':
          endwin();
          return 0;
          break;
        case KEY_UP:
          if (mode > 1) {
            mode--;
          }
          break;
        case KEY_DOWN:
          if (mode < 2) {
            mode++;
          }
          break;
        case '\n':  // [fallthrough]
        case ' ':
          selecting = false;  // Finish selecting.
          break;
        default:
          break;
      }
    }
  }

  enum TictactoeWinner winner = kWinnerNone;
  int key;  // Stores the result of getchar().
  // Position of cursor.
  int cursor_x = 0;
  int cursor_y = 0;
  // Whose turn.
  // O moves first.
  int turn = kWinnerO;
  // Main game loop.
  bool is_running = true;
  while (is_running) {
    clear();
    show_game_board(&tictactoe, cursor_x, cursor_y);
    refresh();

    if (mode == kPveMode && turn == kWinnerX) {
      int x;
      int y;
      status = find_best_move(&tictactoe, &x, &y);
      if (status != kOk) {
        endwin();
        printf("find_best_move() error, code: %d\n", status);
        return -1;
      }
      cursor_x = x;
      cursor_y = y;
      status = make_move(&tictactoe, x, y, kItemX);  // The AI is 'X'.
      if (status != kOk) {
        endwin();
        printf("make_move() error, code: %d, x=%d, y=%d\n", status, x, y);
        return -1;
      }
      // Take turn.
      turn = kItemO;
    } else {
      // Get and handle key pressing.
      key = getch();
      switch (key) {
        // Exit.
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
        // Up.
        case KEY_UP:  // [fallthrough]
        case 'w':
          if (cursor_y > 0) {
            cursor_y--;
          }
          break;
        // Down.
        case KEY_DOWN:  // [fallthrough]
        case 's':
          if (cursor_y < tictactoe.size - 1) {
            cursor_y++;
          }
          break;
        // Right.
        case KEY_RIGHT:  // [fallthrough]
        case 'd':
          if (cursor_x < tictactoe.size - 1) {
            cursor_x++;
          }
          break;
        // Left.
        case KEY_LEFT:  // [fallthrough]
        case 'a':
          if (cursor_x > 0) {
            cursor_x--;
          }
          break;
        // Make move.
        case '\n':  // [fallthrough]
        case ' ':
          if (tictactoe.board[cursor_y][cursor_x] == kItemEmpty) {
            status = make_move(&tictactoe, cursor_x, cursor_y, turn);
            if (status != kOk) {
              // break, make_move error.
              mvprintw(0, 0, "make_move error");
              break;
            }
            // Take turn.
            if (turn == kWinnerO) {
              turn = kWinnerX;
            } else if (turn == kWinnerX) {
              turn = kWinnerO;
            }
          }
        default:
          break;
      }
    }
    // Check winner.
    status = check_winner(&tictactoe, &winner);
    if (status != kOk) {
      // break, check_winner error.
      mvprintw(0, 0, "check_winner error");
      break;
    }
    if (winner != kWinnerNone) {
      // We have a winner, exit loop.
      is_running = false;
      break;
    }
  }
  if (winner != kWinnerNone) {
    clear();
    show_game_board(&tictactoe, cursor_x, cursor_y);
    if (winner == kWinnerTie) {
      mvprintw(0, 0, "It's a tie! Press any key to exit");
    } else {
      // There is a winner, show it.
      mvprintw(0, 0, "The winner is %c! Press any key to exit", winner_to_char(winner));
    }
    refresh();
    getch();  // Wait for a key, and then exit.
  }

  // Exit ncurses mode.
  endwin();
  return 0;
}

// @brief Show game board.
// It will show the selected item in a special color.
void show_game_board(const struct Tictactoe *pGame, const int cursor_x, const int cursor_y)  {
  // Temporary stores a item in the board.
  int item;
  char item_in_char = '\0';
  bool is_selected = false;  // This item ([i][j]) is selected.
  // Shows the game board.
  for (int i = 0; i < pGame->size; i++) {
    for (int j = 0; j < pGame->size; j++) {
      // Check selected.
      if (i == cursor_y && j == cursor_x) {
        is_selected = true;
      } else {
        is_selected = false;
      }

      item = pGame->board[i][j];
      if (item == kItemO) {
        item_in_char = 'O';
      } else if (item == kItemX) {
        item_in_char = 'X';
      } else {
        // Empty.
        if (is_selected) {
          item_in_char = '+';
        } else {
          item_in_char = '-';
        }
      }

      if (is_selected) {
        // If this item is selected, use a special color pair.
        attron(COLOR_PAIR(kSelectedPair));
      }
      mvprintw(i*4+3, j*8+4, "%c", item_in_char);
      if (is_selected) {
        // Turn off the color pair if needed.
        attroff(COLOR_PAIR(kSelectedPair));
      }
    }
  }
}

char *mode_to_string(const enum TictactoeGameMode mode) {
  if (mode == kPvpMode) {
    return "PvP Mode";
  } else if (mode == kPveMode) {
    return "PvE Mode";
  }
  return "Undefined Mode";
}
