#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
struct abonent { 
    char name[10]; 
    char second_name[10]; 
    char tel[10]; 
}; 
 
void add_abonent(struct abonent **directory, int *count) { 
    *directory = realloc(*directory, (*count + 1) * sizeof(struct abonent)); 
    if (*directory == NULL) { 
        printf("Ошибка выделения памяти.\n"); 
        exit(1); 
    } 
 
    printf("Введите имя: "); 
    scanf("%9s", (*directory)[*count].name); 
    printf("Введите фамилию: "); 
    scanf("%9s", (*directory)[*count].second_name); 
    printf("Введите телефон: "); 
    scanf("%9s", (*directory)[*count].tel); 
 
    (*count)++; 
    printf("Абонент добавлен.\n"); 
} 
 
void delete_abonent(struct abonent **directory, int *count) { 
    char name[10]; 
    char second_name[10]; 
    printf("Введите имя абонента для удаления: "); 
    scanf("%9s", name); 
    printf("Введите фамилию абонента для удаления: "); 
    scanf("%9s", second_name); 
 
    for (int i = 0; i < *count; i++) { 
        if (strcmp((*directory)[i].name, name) == 0 && strcmp((*directory)[i].second_name, second_name) == 0) { 
            (*directory)[i] = (*directory)[*count - 1]; // Перемещение последнего элемента на место удаляемого 
            *directory = realloc(*directory, (*count - 1) * sizeof(struct abonent)); 
            if (*directory == NULL && *count - 1 > 0) { 
                printf("Ошибка выделения памяти.\n"); 
                exit(1); 
            } 
            (*count)--; 
            printf("Абонент удален.\n"); 
            return; 
        } 
    } 
    printf("Абонент не найден.\n"); 
} 
 
void search_abonent(struct abonent *directory, int count) { 
    char name[10]; 
    printf("Введите имя для поиска: "); 
    scanf("%9s", name); 
 
    int found = 0; 
    for (int i = 0; i < count; i++) { 
        if (strcmp(directory[i].name, name) == 0) { 
            printf("Имя: %s, Фамилия: %s, Телефон: %s\n", directory[i].name, directory[i].second_name, directory[i].tel); 
            found = 1; 
        } 
    } 
    if (!found) { 
        printf("Абоненты с именем %s не найдены.\n", name); 
    } 
} 
 
void print_all_abonents(struct abonent *directory, int count) { 
    if (count == 0) { 
        printf("Справочник пуст.\n"); 
        return; 
    } 
 
    for (int i = 0; i < count; i++) { 
        printf("Имя: %s, Фамилия: %s, Телефон: %s\n", directory[i].name, directory[i].second_name, directory[i].tel); 
    } 
} 
 
void display_menu() { 
    printf("\nМеню:\n"); 
    printf("1) Добавить абонента\n"); 
    printf("2) Удалить абонента\n"); 
    printf("3) Поиск абонентов по имени\n"); 
    printf("4) Вывод всех записей\n"); 
    printf("5) Выход\n"); 
    printf("Введите номер пункта меню: "); 
} 
 
int main() { 
    struct abonent *directory = NULL; 
    int count = 0; 
    int choice; 
 
    do { 
        display_menu(); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                add_abonent(&directory, &count); 
                break; 
            case 2: 
                delete_abonent(&directory, &count); 
                break; 
            case 3: 
                search_abonent(directory, count); 
                break; 
            case 4: 
                print_all_abonents(directory, count); 
                break; 
            case 5: 
                printf("Выход из программы.\n"); 
                break; 
            default: 
                printf("Неверный пункт меню.\n"); 
        } 
    } while (choice != 5); 
 
    free(directory); 
    return 0; 
}
