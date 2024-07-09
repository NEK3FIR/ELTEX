#include <stdio.h> 
 
// Функция для подсчета количества единиц в двоичном представлении числа 
int countOnes(unsigned int n) { 
    int count = 0; 
    while (n) { 
        count += n & 1; 
        n >>= 1; 
    } 
    return count; 
} 
 
int main() { 
    unsigned int num; 
    printf("Введите целое положительное число: "); 
    if (scanf("%u", &num) != 1) { 
        printf("Ошибка ввода.\n"); 
        return 1; 
    } 
    int onesCount = countOnes(num); 
    printf("Количество единиц в двоичном представлении числа %u: %d\n", num, onesCount); 
    return 0; 
}
