#include <stdio.h> 
 
int main(void) { 
    // Задаем размер массива 
    int arr[5] = {1, 2, 3, 4, 5}; 
 
    // Выводим массив в обратном порядке 
    for (int i = 5; i > 0; --i) { 
        printf("%d ", arr[i-1]); 
    } 
    printf("\n"); 
 
    return 0; 
}
