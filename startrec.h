#include "functionsOne.h"
#include "functionsTwo.h"

void printStart() {
    printf("Выберите задание:\n");
    printf("1. Найти и вывести 2 старших бита беззнакового числа.\n");
    printf("2. Структура содержит информацию о сотрудниках фирмы: шифр отдела\n"
           "(число), фамилию (указатель), вложенную структуру – дату приёма на работу\n"
           "(строка фиксированной длины) и сумму оклада. Найти сотрудников с\n"
           "заданной фамилией. Удалить сотрудников с окладом ниже заданного.\n");
    printf("Введите номер задания: ");
}

void task1() {
    unsigned int num;
    printf("Введите беззнаковое целое число: ");
    while (scanf_s("%d", &num) != 1 || getchar() != '\n')
    {
        printf("Ошибка, введите целое число\n");
        rewind(stdin);
    };
    print_two_oldest_bits(num);

    return 0;
}

void task2() {
    int choice, count = 0;
    Workers *workers = NULL;

    printf("Введите колво сотрудников: ");
    int size = isInteger();

    if (size <= 0) {
        printf("Ошибка.\n");
        return;
    }

    workers = createWorkersArray(size);

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавьте сотрудника\n");
        printf("2. Покажите всех сотрудников\n");
        printf("3. Найти сотрудника по фамилии\n");
        printf("4. Удалить сотрудника с окладом ниже\n");
        printf("5. Выход\n");
        printf("Введите число: ");
        scanf_s("%d", &choice);

        switch (choice) {
            case 1:
                if (count == size) {
                    size++;
                    Workers *temp = realloc(workers, size * sizeof(Workers));
                    if (!temp) {
                        printf("Ошибка выделения памяти для массива сотрудников!\n");
                        freeWorkersArray(workers, count);
                        return;
                    }
                    workers = temp;
                    workers[count].name = NULL;
                }
                inputWorkers(&workers[count], 50);
                count++;
                break;

            case 2:
                if (count == 0) {
                    printf("Пусто.\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printWorkers(&workers[i]);
                    }
                }
                break;

            case 3: {
                char name[50];
                printf("Введите фамилию: ");
                scanf_s("%s", name, (unsigned) _countof(name));
                findByName(workers, count, name);
                break;
            }

            case 4: {
                printf("Введите оклад: ");
                int maxCost = isInteger();
                deleteBySum(workers, count, maxCost);
                break;
            }

            case 5:
                freeWorkersArray(workers, size);
                printf("Память была очищена.\n");
                return;

            default:
                printf("Ошибка.\n");
        }
    }
}