#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 4
#define MAX_SIZE 9

int grid[MAX_SIZE][MAX_SIZE];
int SIZE;

// Hàm kiểm tra lưới Sudoku đã đầy chưa
int isDoneAll()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) return 0;
        }
    }
    return 1;
}

// Hàm kiểm tra số đã dùng trong cột chưa
int isUsedInCol(int consideredCol, int consideredNumb)
{
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][consideredCol] == consideredNumb) {
            return 1;
        }
    }
    return 0;
}

// Hàm kiểm tra số đã dùng trong khối chưa
int isUsedInBox(int consideredRow, int consideredCol, int consideredNumb)
{
    int boxSize = SIZE / 3;
    int boxRowStart = (consideredRow / boxSize) * boxSize;
    int boxColStart = (consideredCol / boxSize) * boxSize;

    for (int i = boxRowStart; i < boxRowStart + boxSize; i++) {
        for (int j = boxColStart; j < boxColStart + boxSize; j++) {
            if (grid[i][j] == consideredNumb) return 1;
        }
    }
    return 0;
}

// Hàm kiểm tra số đã dùng trong hàng chưa
int isUsedInRow(int consideredRow, int consideredNumb)
{
    for (int i = 0; i < SIZE; i++) {
        if (consideredNumb == grid[consideredRow][i]) {
            return 1;
        }
    }
    return 0;
}

// Hàm kiểm tra xem số có thể được đặt ở vị trí (row, col) không
int isSafe(int consideredRow, int consideredCol, int consideredNumb)
{
    if (isUsedInBox(consideredRow, consideredCol, consideredNumb) ||
        isUsedInCol(consideredCol, consideredNumb) ||
        isUsedInRow(consideredRow, consideredNumb)) return 0;
    return 1;
}

// Hàm giải Sudoku
int solveSudoku(int consideredRow, int consideredCol)
{
    if (isDoneAll()) return 1;

    consideredCol++;
    if (consideredCol == SIZE) {
        consideredCol = 0;
        consideredRow++;
    }

    if (consideredRow == SIZE) return 1;

    if (grid[consideredRow][consideredCol] == 0) {
        for (int i = 1; i <= SIZE; i++) {
            if (isSafe(consideredRow, consideredCol, i)) {
                grid[consideredRow][consideredCol] = i;
                if (solveSudoku(consideredRow, consideredCol)) {
                    return 1;
                } else {
                    grid[consideredRow][consideredCol] = 0;
                }
            }
        }
    } else {
        if (solveSudoku(consideredRow, consideredCol)) return 1;
    }
    return 0;
}

// Hàm in bảng kết quả
void printSolution()
{
    int boxSize = SIZE / 3;
    for (int i = 0; i < SIZE; i++) {
        if (i % boxSize == 0 && i != 0) {
            printf("--");
            for (int k = 0; k < SIZE - 1; k++) {
                printf("+--");
            }
            printf("\n");
        }
        for (int j = 0; j < SIZE; j++) {
            if (j % boxSize == 0 && j != 0) {
                printf("| ");
            }
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Hàm nhập dữ liệu vào ma trận
void input()
{
    printf("Nhập lưới Sudoku %dx%d (nhập 0 cho ô trống):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

// Hàm chọn kích thước ma trận
void chooseSize()
{
    int choice;
    do {
        printf("Chọn kích thước Sudoku (4-9): ");
        scanf("%d", &choice);
    } while (choice < MIN_SIZE || choice > MAX_SIZE || choice % 2 != 0);

    SIZE = choice;
}

int main()
{
    chooseSize();
    input();
    if (solveSudoku(0, 0)) {
        printf("Kết quả:\n");
        printSolution();
    } else {
        printf("Không có lời giải!\n");
    }
    return 0;
}

