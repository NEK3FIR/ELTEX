#include <stdio.h> 
 
void printMatrix(int N) { 
    int matrix[N][N]; 
    int value = 1; 
 
    // Заполнение матрицы числами от 1 до N*N 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            matrix[i][j] = value++; 
        } 
    } 
 
    // Вывод матрицы на экран 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            printf("%d ", matrix[i][j]); 
        } 
        printf("\n"); 
    } 
} 
 
int main() { 
    int N; 
 
    // Ввод значения N 
    printf("Введите размер матрицы N: "); 
    scanf("%d", &N); 
 
    // Печать матрицы 
    printMatrix(N); 
 
    return 0; 
}
