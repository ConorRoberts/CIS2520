#ifndef _TTT_H
#define _TTT_H

#define HSIZE 19683 // 3^9
#define BSIZE 31    // 6 characters per line, 5 lines, and \0

// represents a board
typedef char Board[BSIZE];

// start board string declared in ttt.c
extern Board START_BOARD;

// external array that maps the playable positions to their indices in the
// board string
extern int pos2idx[9];

// external array of row, column and diagonal positions

extern int WINS[8][3];

// board nodes for graph
struct BoardNode
{
  char init;   // 0=not initialized, or 1=initialized
  char turn;   // 'X', 'O', '-'=board is full (game over)
  int depth;   // depth of the node in the graph = moves played
  Board board; // printable board file
  char winner; // 'X', 'O', '-' (tie), '?' (game in progress)
  int move[9]; // board hashes for all move positions; -1=illegal move
  int score;   // winner of the game if both players play smartly
               // 1=X -1=O 0=tie
};

// htable declared in ttt.c
extern struct BoardNode htable[HSIZE];

int board_hash(Board board);
int imax(int a, int b);
int imin(int a, int b);
void init_boards();
char winner(Board board);
int depth(Board board);
char turn(Board board);
void init_board(Board board);
void join_graph(Board board);
void compute_score();
int best_move(int board);
void print_node(struct BoardNode board_node);
#endif
