#include <stdio.h> 
 
// Функция для вывода двоичного представления числа 
void printBinary(int n) { 
    // Количество битов в типе int 
    int numBits = sizeof(n) * 8; 
 
    // Выводим биты от старшего к младшему 
    for (int bit = numBits - 1; bit >= 0; bit--) { 
        printf("%d", (n & (1 << bit)) ? 1 : 0); 
    } 
    printf("\n"); 
} 
 
int main() { 
    int num; 
    printf("Введите целое отрицательное число: "); 
    if (scanf("%d", &num) != 1) { 
        printf("Ошибка ввода.\n"); 
        return 1; 
    } 
    if (num >= 0) { 
        printf("Введено не отрицательное число.\n"); 
        return 1; 
    } 
    printf("Двоичное представление числа %d: ", num); 
    printBinary(num); 
    return 0; 
}
