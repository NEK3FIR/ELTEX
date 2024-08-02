// main.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <dlfcn.h> 
 
void show_menu() { 
    printf("1) Сложение\n"); 
    printf("2) Вычитание\n"); 
    printf("3) Умножение\n"); 
    printf("4) Деление\n"); 
    printf("5) Выход\n"); 
} 
 
int main() { 
    int choice, a, b; 
    void *handle; 
    int (*add)(int, int); 
    int (*sub)(int, int); 
    int (*mul)(int, int); 
    int (*div)(int, int); 
    char *error; 
 
    handle = dlopen("./libcalc.so", RTLD_LAZY); 
    if (!handle) { 
        fprintf(stderr, "%s\n", dlerror()); 
        exit(EXIT_FAILURE); 
    } 
 
    // Загружаем функции 
    add = dlsym(handle, "add"); 
    if ((error = dlerror()) != NULL)  { 
        fprintf(stderr, "%s\n", error); 
        exit(EXIT_FAILURE); 
    } 
 
    sub = dlsym(handle, "sub"); 
    if ((error = dlerror()) != NULL)  { 
        fprintf(stderr, "%s\n", error); 
        exit(EXIT_FAILURE); 
    } 
 
    mul = dlsym(handle, "mul"); 
    if ((error = dlerror()) != NULL)  { 
        fprintf(stderr, "%s\n", error); 
        exit(EXIT_FAILURE); 
    } 
 
    div = dlsym(handle, "div"); 
    if ((error = dlerror()) != NULL)  { 
        fprintf(stderr, "%s\n", error); 
        exit(EXIT_FAILURE); 
    } 
 
    while (1) { 
        show_menu(); 
        printf("Выберите операцию: "); 
        scanf("%d", &choice); 
 
        if (choice == 5) { 
            break; 
        } 
 
        if (choice < 1 || choice > 4) { 
            printf("Неверный выбор. Попробуйте снова.\n"); 
            continue; 
        } 
 
        printf("Введите два целых числа: "); 
        scanf("%d %d", &a, &b); 
 
        switch (choice) { 
            case 1: 
                printf("Результат: %d\n", add(a, b)); 
                break; 
            case 2: 
                printf("Результат: %d\n", sub(a, b)); 
                break; 
            case 3: 
                printf("Результат: %d\n", mul(a, b)); 
                break; 
            case 4: 
                printf("Результат: %d\n", div(a, b)); 
                break; 
        } 
    } 
 
    dlclose(handle); 
    return 0; 
}
