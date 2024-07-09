#include <stdio.h> 
 
// Функция для замены третьего байта в числе 
unsigned int replaceThirdByte(unsigned int num, unsigned char newByte) { 
    // Маска для очистки третьего байта (бит 16-23) 
    unsigned int mask = 0xFF << 16; 
    // Очистить третий байт и установить новое значение 
    num = (num & ~mask) | (newByte << 16); 
    return num; 
} 
 
int main() { 
    unsigned int num; 
    unsigned int newByte; 
 
    printf("Введите целое положительное число: "); 
    if (scanf("%u", &num) != 1) { 
        printf("Ошибка ввода.\n"); 
        return 1; 
    } 
 
    printf("Введите новое значение для третьего байта (0-255): "); 
    if (scanf("%u", &newByte) != 1 || newByte > 255) { 
        printf("Ошибка ввода.\n"); 
        return 1; 
    } 
 
    unsigned int result = replaceThirdByte(num, (unsigned char)newByte); 
    printf("Новое число: %u\n", result); 
 
    return 0; 
}

