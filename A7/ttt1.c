#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

// printable string that displays the initial board
// Board START_BOARD = "0|1|2\n-+-+-\n3|4|5\n-+-+-\n6|7|8\n";
Board START_BOARD = "0|1|2\n-+-+-\n3|4|5\n-+-+-\n6|7|8\n";

// array that maps the playable positions to their indices in the board string
int pos2idx[9] = {0, 2, 4, 12, 14, 16, 24, 26, 28};

// array of row, column and diagonal positions
int WINS[8][3] = {
    {0, 1, 2}, // top row
    {3, 4, 5}, // middle row
    {6, 7, 8}, // bottom row
    {0, 3, 6}, // left column
    {1, 4, 7}, // middle column
    {2, 5, 8}, // right column
    {0, 4, 8}, // \ diagonal
    {2, 4, 6}  // / diagonal
};

// hash table of board nodes for graph
struct BoardNode htable[HSIZE];

int board_hash(char board[31])
// this function computes a hash value for a given board considering only
// the playable positions
// this is a perfect hash in the sense that every possible board is
// mapped to a unique hash value
// but it is wasteful since even some impossible boards are mapped
// to unique hash values (e.g. a board with 7 Xs and zero Os)
{
  int total = 0;
  int mult = 1;
  for (int i = 0; i < 9; i++)
  {
    switch (board[pos2idx[i]])
    {
    case 'X':
      total += 2 * mult;
      break;
    case 'O':
      total += 1 * mult;
      break;
    default: // unoccupied space represented by a numerical board position
      total += 0 * mult;
      break;
    }
    mult *= 3;
  }
  return total;
}

void print_node(struct BoardNode board_node)
{
  printf("**************************************************************\n");
  printf("init=%d\n", board_node.init);
  if (board_node.init)
  {
    printf("turn=%c\n", board_node.turn);
    printf("depth=%d\n", board_node.depth);
    printf("%s", board_node.board);
    printf("winner=%c\n", board_node.winner);
    printf("moves= ");
    for (int m = 0; m < 9; m++)
      printf("[%d]=%d, ", m, board_node.move[m]);
    printf("\n");
    printf("score=%d\n", board_node.score);
  }
  printf("**************************************************************\n");
}
