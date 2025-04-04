#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char startDate[11];
    int sum;
} WorkersDate;

typedef struct {
    int cipher;
    char* name;
    WorkersDate date;
} Workers;

int isPositiveInteger(const char* input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidDateFormat(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '.' || date[5] != '.') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return 0;
    }
    return 1;
}

Workers* createWorkersArray(int size) {
    Workers* workers = (Workers*)malloc(size * sizeof(Workers));
    if (!workers) {
        printf("Ошибка памяти!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        workers[i].name = NULL;
    }
    return workers;
}

void freeWorkersArray(Workers* workers, int size) {
    for (int i = 0; i < size; i++) {
        if (workers[i].name) {
            free(workers[i].name);
        }
    }
    free(workers);
}


int isInteger() {
    int n = 0;
    while (scanf_s("%d", &n) != 1 || getchar() != '\n')
    {
        printf("Ошибка\n");
        rewind(stdin);
    }
    return n;

}

void inputWorkers(Workers* workers, int maxNameLength) {
    char buffer[50];

    if (workers->name == NULL) {
        workers->name = (char*)malloc(maxNameLength * sizeof(char));
        if (!workers->name) {
            printf("Ошибка памяти!\n");
            exit(1);
        }
    }

    printf("Введите фамилию: ");
    scanf_s("%s", workers->name, maxNameLength);




    while (1) {
        printf("Введите шифр отдела: ");
        int a = isInteger();
        if (a >0) {
            workers->cipher = a;
            break;
        }
        else {
            printf("Ошибка.\n");
        }
    }

    while (1) {
        printf("Введите дату приема на работу (DD.MM.YYYY): ");
        scanf_s("%s", workers->date.startDate, (unsigned)sizeof(workers->date.startDate));
        if (isValidDateFormat(workers->date.startDate)) {
            break;
        }
        else {
            printf("Invalid date format. Please use DD.MM.YYYY.\n");
        }
    }

    while (1) {
        printf("Введите оклад: ");
        int a = isInteger();
        if (a > 0) {
            workers->date.sum = a;
            break;
        }
        else {
            printf("Ошибка.\n");
        }
    }
}

void printWorkers(const Workers* workers) {
    if (workers->name) {
        printf("Фамилия сотрудника: %s, Шифр отдела: %d, Дата приема на работу: %s, Оклад : %d \n",
               workers->name, workers->cipher, workers->date.startDate, workers->date.sum);
    }
    else {
        printf("Не заполнено.\n");
    }
}

void findByName(Workers* workers, int count, const char* name) {
    printf("Сотрудник с фамилией %d:\n", name);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (workers[i].name && strcmp(workers[i].name, name) == 0) {
            printWorkers(&workers[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Нет никого с фамилией %d.\n", name);
    }
}

int deleteBySum(Workers * workers, int count, int maxCost) {
    int newSize = count;
    printf("Удалить сотрудника с окладом меньше %d:\n", maxCost);
    for (int i = 0; i < count; i++) {
        if (workers[i].date.sum < maxCost) {
            free(workers[i].date.sum);
            workers[i].date.sum = NULL;
            for (int j = i; j < workers - 1; j++) {
                workers[j] = workers[j + 1];
            }
            newSize--;
            i--;
        }
    }
   if (newSize == count) {
        printf("Сотрудников с окладом ниже '%d' не найдено:\n", maxCost);
    }
    else {
        printf("Сотрудники с окладом ниже '%d' были удалены.\n", maxCost);
    }
    return newSize;
}