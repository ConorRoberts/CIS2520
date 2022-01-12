#include "ttt.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void init_boards()
{
    int i;
    for (i = 0; i < HSIZE; i++)
    {
        htable[i].init = 0;
    }
}

int depth(Board board)
{
    int i, count = 0;

    for (i = 0; i < 9; i += 1)
    {
        char c = board[pos2idx[i]];
        if (c == 'X' || c == 'O')
        {
            count++;
        }
    }

    return count;
}

char winner(Board board)
{
    // Checking if there is a winner
    int i, j, k;
    for (i = 0; i < 2; i++)
    {
        char player = i == 0 ? 'X' : 'O';

        // Checking each line in the WINS array
        // Wins contains board positions organized in lines
        for (j = 0; j < 8; j++)
        {
            int count = 0;

            // Check each spot in current line
            for (k = 0; k < 3; k++)
            {
                // Has to convert position in wins to pos in board array
                if (board[pos2idx[WINS[j][k]]] == player)
                {
                    count++;
                }
            }

            // 3 in a row?
            if (count == 3)
            {
                return player;
            }
        }
    }

    // Board full and no winner
    if (depth(board) == 9)
    {
        return '-';
    }

    // No winner found but board not full
    return '?';
}

char turn(Board board)
{
    int d = depth(board);
    if (d == 9 || winner(board) != '?')
    {
        return '-';
    }

    return (d % 2 == 0) ? 'X' : 'O';
}
void init_board(Board board)
{
    // Reference BoardNode
    struct BoardNode *ref = &htable[board_hash(board)];

    ref->init = 1;
    ref->turn = turn(board);
    ref->depth = depth(board);
    strcpy(ref->board, board);
    ref->winner = winner(board);
}

void join_graph(Board board)
{
    // Reference BoardNode
    struct BoardNode *ref = &htable[board_hash(board)];

    for (int i = 0; i < 9; i++)
    {
        if (isalpha(board[pos2idx[i]]))
        {
            ref->move[i] = -1;
            continue;
        }

        // Copy over data and update board
        Board new_board;
        strcpy(new_board, board);
        new_board[pos2idx[i]] = turn(new_board);

        // Update move with new hash
        htable[board_hash(board)].move[i] = board_hash(new_board);

        if (htable[board_hash(new_board)].init == 0 && ref->winner == '?')
        {
            init_board(new_board);
            join_graph(new_board);
        }
    }
}

int find_score(struct BoardNode *ref, char player_turn)
{
    char winner = ref->winner;
    if (winner == 'X')
    {
        return 1;
    }
    else if (winner == 'O')
    {
        return -1;
    }
    else if (winner == '-' || ref->depth == 0)
    {
        return 0;
    }

    // char player_turn = turn(ref->board);
    int (*minmax)(int a, int b);
    minmax = player_turn == 'X' ? &imax : &imin;

    int val = -5;
    for (int i = 0; i < 9; i++)
    {
        int current = ref->move[i];
        if (current == -1)
        {
            continue;
        }
        if (val == -5)
        {
            val = current;
        }

        val = minmax(val, current);
    }

    return find_score(&htable[val], player_turn);
}

int imax(int a, int b)
{
    return a > b ? a : b;
}

int imin(int a, int b)
{
    return a < b ? a : b;
}

// Last 20%
void compute_score()
{
    for (int i = 0; i < HSIZE; i++)
    {
        struct BoardNode *ref = &htable[i];
        ref->score = find_score(ref, turn(ref->board));
    }
}

int best_move(int board)
{
    int (*minmax)(int a, int b);
    minmax = htable[board].turn == 'X' ? &imax : &imin;

    int best = 0;
    for (int i = 0; i < 9; i++)
    {
        if (htable[board].move[i] == -1)
            continue;

        struct BoardNode parent = htable[board];
        int score_best = htable[parent.move[best]].score;
        int score_compare = htable[parent.move[i]].score;

        best = minmax(score_best, score_compare) == score_best ? best : i;
    }

    return best;
}
