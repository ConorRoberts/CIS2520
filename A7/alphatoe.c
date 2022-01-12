/*
 * Fixed version of alphatoe.c
 * Credit: Samuel Guilbeault
 */

#include "ttt.h"
#include <stdio.h>
#include <ctype.h>

#define MAX_INPUT 512

int main(int argc, char **argv)
{
  char human;
  char input[MAX_INPUT];

  init_boards();
  init_board(START_BOARD);
  join_graph(START_BOARD);
  compute_score();

  printf("X or O? ");
  fgets(input, MAX_INPUT, stdin);
  human = input[0];

  int board = 0;

  while (isalpha(htable[board].turn)) // while no winner
  {
    printf("%d\n", board);
    if (human == htable[board].turn)
    {
      int next_board;
      do
      {
        char movec;
        int movei;
        print_node(htable[board]);
        printf("Your move [0-8]: ");
        fgets(input, MAX_INPUT, stdin);
        movec = input[0];
        movei = (int)(movec - '0');
        next_board = htable[board].move[movei];
        if (next_board == -1)
        {
          printf("Illegal move, try again!\n");
        }
      } while (next_board == -1);
      board = next_board;
    }
    else // computers turn
    {
      board = htable[board].move[best_move(board)];
    } // computers turn
  }   // while loop

  print_node(htable[board]);
  printf("Game over, Player 1!\n");

  if (htable[board].winner == human)
    printf("You won!\n");
  else if (htable[board].winner == '-')
    printf("The game was a tie!\n");
  else
    printf("You lost!\n");
}
