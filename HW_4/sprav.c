#include <stdio.h> 
#include <string.h> 
 
#define MAX_ABONENTS 100 
 
struct abonent { 
    char name[10]; 
    char second_name[10]; 
    char tel[10]; 
}; 
 
void add_abonent(struct abonent *directory, int *count) { 
    if (*count >= MAX_ABONENTS) { 
        printf("Справочник переполнен. Невозможно добавить нового абонента.\n"); 
        return; 
    } 
 
    printf("Введите имя: "); 
    scanf("%9s", directory[*count].name); 
    printf("Введите фамилию: "); 
    scanf("%9s", directory[*count].second_name); 
    printf("Введите телефон: "); 
    scanf("%9s", directory[*count].tel); 
 
    (*count)++; 
    printf("Абонент добавлен.\n"); 
} 
 
void delete_abonent(struct abonent *directory, int *count) { 
    char name[10]; 
    char second_name[10]; 
    printf("Введите имя абонента для удаления: "); 
    scanf("%9s", name); 
    printf("Введите фамилию абонента для удаления: "); 
    scanf("%9s", second_name); 
 
    for (int i = 0; i < *count; i++) { 
        if (strcmp(directory[i].name, name) == 0 && strcmp(directory[i].second_name, second_name) == 0) { 
            for (int j = i; j < *count - 1; j++) { 
                directory[j] = directory[j + 1]; 
            } 
            memset(&directory[*count - 1], 0, sizeof(struct abonent)); 
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
 
int main() { 
    struct abonent directory[MAX_ABONENTS] = {0}; 
    int count = 0; 
    int choice; 
 
    do { 
        printf("\nМеню:\n"); 
        printf("1) Добавить абонента\n"); 
        printf("2) Удалить абонента\n"); 
        printf("3) Поиск абонентов по имени\n"); 
        printf("4) Вывод всех записей\n"); 
        printf("5) Выход\n"); 
        printf("Введите номер пункта меню: "); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                add_abonent(directory, &count); 
                break; 
            case 2: 
                delete_abonent(directory, &count); 
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
 
    return 0; 
}
