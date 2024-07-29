// div.c
#include "calc.h"

int div(int a, int b) {
    if (b == 0) {
        printf("Ошибка: деление на ноль.\n");
        return 0; // Ошибка, деление на ноль
    }
    return a / b;
}
