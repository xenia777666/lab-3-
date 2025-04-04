#include "startrec.h"
int main() {
    int is_return = 1;
    do {
        printStart();

        int choice;

        while (scanf_s("%d", &choice) != 1 || getchar() != '\n' || choice > 2 || choice < 1)
        {
            printf("Error, input task number 1 or 2\n");
            rewind(stdin);
        }

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            default:
                printf("Ошибка.\n");
                break;
        }
        printf("\n  Еще раз? 1 - да, другое - нет \n");
        if (scanf_s("%d", &is_return) != 1 || is_return != 1 || getchar() != '\n') {
            is_return = 0;
        }
    } while (is_return);
    return 0;
}