#include <stdio.h> 
#include <string.h> 
 
#define MAX_STRING_LENGTH 100 
 
char *find_substring(char *str, char *substr) { 
    char *p = strstr(str, substr); 
    return p; 
} 
 
int main() { 
    char str[MAX_STRING_LENGTH]; 
    char substr[MAX_STRING_LENGTH]; 
 
    // Ввод основной строки 
    printf("Введите строку: "); 
    fgets(str, MAX_STRING_LENGTH, stdin); 
    // Удаляем символ новой строки, если он был считан 
    str[strcspn(str, "\n")] = 0; 
 
    // Ввод подстроки 
    printf("Введите подстроку: "); 
    fgets(substr, MAX_STRING_LENGTH, stdin); 
    // Удаляем символ новой строки, если он был считан 
    substr[strcspn(substr, "\n")] = 0; 
 
    // Поиск подстроки в строке 
    char *result = find_substring(str, substr); 
 
    // Результат поиска 
    if (result) { 
        printf("Подстрока найдена по адресу: %p\n", result); 
        printf("Начало подстроки: %s\n", result); 
    } else { 
        printf("Подстрока не найдена.\n"); 
    } 
 
    return 0; 
}
