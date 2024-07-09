#include <stdio.h> 
 
int main() { 
    int N; 
 
    // Ввод размера матрицы 
    printf("Введите размер матрицы N: "); 
    scanf("%d", &N); 
 
    // Создание и заполнение матрицы 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            if (j >= N - i - 1) { 
                printf("1 "); 
            } else { 
                printf("0 "); 
            } 
        } 
        printf("\n"); 
    } 
 
    return 0; 
}
