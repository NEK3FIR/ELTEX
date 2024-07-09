#include <stdio.h>

// Функция для ввода целого положительного числа с клавиатуры
int input_positive_integer() {
    int num;
    printf("Введите целое положительное число: ");
    scanf("%d", &num);
    return num;
}

// Функция для ввода значения для третьего байта (0-255)
unsigned char input_byte_value() {
    unsigned char byte;
    printf("Введите новое значение для третьего байта (0-255): ");
    scanf("%hhu", &byte);
    return byte;
}

// Функция для изменения третьего байта числа на new_byte_value
void change_third_byte(int *num_ptr, unsigned char new_byte_value) {
    unsigned char *bytes = (unsigned char *)num_ptr;
    bytes[2] = new_byte_value;
}

int main() {
    int num;
    unsigned char new_byte;

    // Ввод числа
    num = input_positive_integer();

    // Ввод значения для третьего байта
    new_byte = input_byte_value();

    // Изменение третьего байта числа
    change_third_byte(&num, new_byte);

    // Вывод измененного числа
    printf("Измененное число: %d\n", num);

    return 0;
}
