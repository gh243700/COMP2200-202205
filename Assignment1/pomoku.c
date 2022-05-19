#include "pomoku.h"
#include "color.h"
#include <assert.h>

#define MAX_ROW (20)
#define MIN_ROW (10)
#define MAX_COL (20)
#define MIN_COL (10)

static int s_board[20][20];
static int s_row_count;
static int s_col_count;

static int s_black_stone_score;
static int s_white_stone_score;

int is_valid_scope(const int row, const int col);
int* get_stone_score(const color_t color);
int get_stone_count(const color_t color, const unsigned int row, const unsigned int col, const int row_increment, const int col_increment);

void init_game(void)
{
    int i;
    int* p = s_board[0];
    
    s_col_count = 15;
    s_row_count = 15;
    
    s_black_stone_score = 0;
    s_white_stone_score = 0;
    
    for (i = 0; i < MAX_ROW * MAX_COL; i++) {
        *p++ = -1;
    }
    
}

unsigned int get_row_count(void) 
{
    return s_row_count;
}

unsigned int get_column_count(void) 
{
    return s_col_count;
}

int get_score(const color_t color)
{
    
    if (color != COLOR_BLACK && color != COLOR_WHITE) {
        return -1;
    }

    return *get_stone_score(color);
}

int get_color(const unsigned int row, const unsigned int col) 
{
    if (!is_valid_scope(row, col)) {
        return -1;
    }
    return s_board[row][col];
}

int is_placeable(const unsigned int row, const unsigned int col) 
{
    if (!is_valid_scope(row, col) || s_board[row][col] != -1) {
        return 0;
    }
    
    return 1;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col) 
{
    int stone_count;
    int* stone_score;
    
    if (!is_placeable(row, col) || (color != COLOR_BLACK && color != COLOR_WHITE)) {
        return 0;
    }
    
    stone_score = get_stone_score(color);
    s_board[row][col] = color;
    
    stone_count = get_stone_count(color, row + 1, col + 1, 1, 1) + get_stone_count(color, row - 1, col - 1, -1, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row - 1, col + 1, -1, 1) + get_stone_count(color, row + 1, col - 1, 1, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row, col + 1, 0, 1) + get_stone_count(color, row, col - 1, 0, -1) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    stone_count = get_stone_count(color, row + 1, col, 1, 0) + get_stone_count(color, row - 1, col, -1, 0) + 1;
    
    if (stone_count >= 5) {
        *stone_score += stone_count - 4;
    }
    
    return 1;
}

/* special moves */

int insert_row(const color_t color, const unsigned int row) 
{
    int i;
    int j;
    int* score = get_stone_score(color);
    
    if (score == NULL || *score < 3 || row < 0 || row > s_row_count || s_row_count >= MAX_ROW) {
        return 0;
    }
    *score -= 3;
    
    for (i = s_row_count - 1; i >= (int)row; i--) {
        for (j = 0; j < s_col_count; j++) {    
            s_board[i + 1][j] = s_board[i][j];
            s_board[i][j] = -1;
        }
    }    

    s_row_count++;

    return 1;
}


int insert_column(const color_t color, const unsigned int col) 
{
    int i;
    int j;
    int* score = get_stone_score(color);
    
    if (score == NULL || *score < 3 || col < 0 || col > s_col_count || s_col_count >= MAX_COL) {
        return 0;
    }

    *score -= 3;

    for (i = 0; i < s_row_count; i++) {
        for (j = s_col_count - 1; j >= (int)col; j--) {    
            s_board[i][j + 1] = s_board[i][j];
            s_board[i][j] = -1;
        }
    }    

    s_col_count++;

    return 1;
}

int remove_row(const color_t color, const unsigned int row) 
{
    int* score = get_stone_score(color);
    int i;
    int j;

    if (score == NULL || *score < 3 || row >= s_row_count || s_row_count <= MIN_ROW) {
        return 0;
    }

    *score -= 3;

    for (i = row; i < s_row_count; i++) {
        for (j = 0; j < s_col_count; j++) {
            s_board[i][j] = s_board[i + 1][j];
        }        
    }
        
    s_row_count--;    

    return 1;
}

int remove_column(const color_t color, const unsigned int col) 
{
    int* score = get_stone_score(color);
    int i;
    int j;

    if (score == NULL || *score < 3 || col >= s_col_count || s_col_count <= MIN_COL) {
        return 0;
    }

    *score -= 3;

    for (i = 0; i < s_row_count; i++) {
        for (j = col; j < s_col_count; j++) {
            s_board[i][j] = s_board[i][j + 1];
        }        
    }
        
    s_col_count--;

    return 1;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    int i; 
    int* ptr1 = s_board[row0];
    int* ptr2 = s_board[row1];    
    int* score = get_stone_score(color);

    if (score == NULL || *score < 2 || row0 >= s_row_count || row1 >= s_row_count) {
        return 0;
    }

    *score -= 2;

    for (i = 0; i < s_row_count; i++) {
        *ptr1 ^= *ptr2;
        *ptr2 ^= *ptr1;
        *ptr1 ^= *ptr2;
        ptr1++;
        ptr2++;
    }

    return 1;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1) 
{
    int i;
    int* ptr1 = &s_board[0][col0];
    int* ptr2 = &s_board[0][col1];
    int* score = get_stone_score(color);

    if (score == NULL || *score < 2 || col0 >= s_col_count || col1 >= s_col_count) {
        return 0;
    }

    *score -= 2;

    for (i = 0; i < s_col_count; i++) {
        *ptr1 ^= *ptr2;
        *ptr2 ^= *ptr1;
        *ptr1 ^= *ptr2;
        ptr1 += MAX_COL;
        ptr2 += MAX_COL;
    }

    return 1;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst) 
{
    int i; 
    int* ptr1 = s_board[src];
    int* ptr2 = s_board[dst];
    int* score = get_stone_score(color);

    if (score == NULL || *score < 4 || src >= s_row_count || dst >= s_row_count) {
        return 0;
    }

    *score -= 4;

    for (i = 0; i < s_row_count; i++) {
        *ptr2++ = *ptr1++;
    }

    return 1;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    int i;
    int* ptr1 = &s_board[0][src];
    int* ptr2 = &s_board[0][dst];
    int* score = get_stone_score(color);

    if (score == NULL || *score < 4 || src >= s_col_count || dst >= s_col_count) {
        return 0;
    }

    *score -= 4;

    for (i = 0; i < s_col_count; i++) {
        *ptr2 = *ptr1;
        ptr1 += MAX_COL;
        ptr2 += MAX_COL; 
    }

    return 1;
}

int* get_stone_score(const color_t color) 
{
    int* score;
    
    switch (color) {
    case COLOR_BLACK: 
        score = &s_black_stone_score;
        break;
    case COLOR_WHITE: 
        score = &s_white_stone_score;
        break;
    default: 
        return NULL;
        break;
    }
    
    return score;
}

int get_stone_count(const color_t color, const unsigned int row, const unsigned int col, const int row_increment, const int col_increment) 
{
    if (!is_valid_scope(row, col) || s_board[row][col] != color) {
        return 0;
    }
    
    return 1 + get_stone_count(color, row + row_increment, col + col_increment, row_increment, col_increment);
}


int is_valid_scope(const int r, const int c) 
{
    if (-1 >= r || s_row_count <= r || -1 >= c || s_col_count <= c) {
        return 0;
    }
    
    return 1;
}


