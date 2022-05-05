#include "pomoku.h"
#include "color.h"
#include <stdio.h>
#include <assert.h>

#define MAX_ROW (20)
#define MIN_ROW (10)
#define MAX_COL (20)
#define MIN_COL (10)

static int board[20][20];
static int row_count;
static int col_count;

static int black_stone_score;
static int white_stone_score;

static int is_valid_scope(const int row, const int col);
static int* get_stone_score(const color_t color);
static int get_stone_count(const color_t color, const unsigned int row, const unsigned int col,const int row_increment,const int col_increment);

void init_game(void) {
    int i;
    int* p = board[0];
    
    col_count = 15;
    row_count = 15;
    
    black_stone_score = 0;
    white_stone_score = 0;
    
    for (i = 0; i < MAX_ROW * MAX_COL; i++) {
        *p++ = -1;
    }
    
}

unsigned int get_row_count(void) {
    return row_count;
}

unsigned int get_column_count(void) {
    return col_count;
}

int get_score(const color_t color) {
    
    if (color != COLOR_BLACK && color != COLOR_WHITE) {
        return -1;
    }

    return *get_stone_score(color);
}

int get_color(const unsigned int row, const unsigned int col) {
    if(!is_valid_scope(row, col)) {
        return -1;
    }
    return board[row][col];
}

int is_placeable(const unsigned int row, const unsigned int col) {
    if(!is_valid_scope(row, col) || board[row][col] != -1) {
        return 0;
    }
    
    return 1;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col) {
    int stone_count;
    int* stone_score;
    
    if (!is_placeable(row, col) || color != COLOR_BLACK && color != COLOR_WHITE) {
        return 0;
    }
    
    stone_score = get_stone_score(color);
    board[row][col] = color;
    
    stone_count = get_stone_count(color, row + 1, col + 1, 1, 1) + get_stone_count(COLOR_BLACK, row - 1, col - 1, -1, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row - 1, col + 1, -1, 1) + get_stone_count(COLOR_BLACK, row + 1, col - 1, 1, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row, col + 1, 0, 1) + get_stone_count(COLOR_BLACK, row, col - 1, 0, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row + 1, col, 1, 0) + get_stone_count(COLOR_BLACK, row - 1, col, -1, 0) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    return 1;
}

/* special moves */

int insert_row(const color_t color, const unsigned int row) {
    int i;
    int j;
    int* score = get_stone_score(color);
    
    if(*score < 3 || !is_valid_scope(row, 0)) {
        return 0;
    }

    row_count++;
    *score -= 3;
    
    for(i = MAX_ROW - 2; i >= row; i--) {
        for(j = 0; j < MAX_COL; j++) {    
            board[i + 1][j] = board[i][j];
            if(i == row) {
                 board[i][j] = -1;   
            }
        }
    }    

    return 1;
}


int insert_column(const color_t color, const unsigned int col) {
    int i;
    int j;
    int* score = get_stone_score(color);
    
    if(*score < 3 || !is_valid_scope(0, col)) {
        return 0;
    }

   col_count++;
    *score -= 3;

    for(i = 0; i < MAX_ROW; i++) {
        for(j = MAX_COL - 2; j >= col; j--) {    
            board[i][j + 1] = board[i][j];
            if(j == col) {
                 board[i][j] = -1;   
            }
        }
    }    

    return 1;
}



static int* get_stone_score(const color_t color) {
    int* score;
    
    switch (color) {
    case COLOR_BLACK: 
        score = &black_stone_score;
    break;
	case COLOR_WHITE: 
        score = &white_stone_score;
    break;
    default: 
        assert(0);
    break;
    }
    
    return score;
}

static int get_stone_count(const color_t color, const unsigned int row, const unsigned int col,const int row_increment,const int col_increment) {
    if (!is_valid_scope(row, col) || board[row][col] != color) {
        return 0;
    }
    
    return 1 + get_stone_count(color, row + row_increment, col + col_increment, row_increment, col_increment);
}


static int is_valid_scope(const int r, const int c) {
    if(-1 >= r || row_count <= r || -1 >= c || col_count <= c) {
        return 0;
    }
    
    return 1;
}

void print_full_board(void) {
    int i; 
    int j;
    char c;
    printf("-------------------------------------------------------\n");
    for(i = 0; i < MAX_ROW; i++) {
        for (j = 0; j < MAX_COL; j++) {
        switch(board[i][j]) {
        case(-1):
            c = ' ';
        break;
        case(COLOR_BLACK):
            c = 'o';
        break;
        case(COLOR_WHITE):
            c = 'x';
        break;
        default: 
            c = 'q';
        break;
        }
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("BLACK : %d\nWHITE : %d\n", black_stone_score, white_stone_score );
    printf("row : %d , col : %d\n", row_count, col_count);
    printf("-------------------------------------------------------\n");

}


