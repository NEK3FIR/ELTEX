#include <stdio.h> 
 
// Функция для вывода двоичного представления числа 
void printBinary(unsigned int n) { 
    // Найти самый старший значащий бит 
    int bit = sizeof(n) * 8 - 1; 
    while (bit >= 0 && !(n & (1 << bit))) { 
        bit--; 
    } 
    // Если число ноль, вывести 0 
    if (bit == -1) { 
        printf("0"); 
    } else { 
        // Выводить биты от старшего к младшему 
        for (; bit >= 0; bit--) { 
            printf("%d", (n & (1 << bit)) ? 1 : 0); 
        } 
    } 
    printf("\n"); 
} 
 
int main() { 
    unsigned int num; 
    printf("Введите целое положительное число: "); 
    if (scanf("%u", &num) != 1) { 
        printf("Ошибка ввода.\n"); 
        return 1; 
    } 
    printf("Двоичное представление числа %u: ", num); 
    printBinary(num); 
    return 0; 
}
