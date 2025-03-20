#include <stdio.h>
#include <stdlib.h>

void printFile();
void printEvenFile();
int safeInput();
void multiply();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];

    
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    printf("Вводите целые числа для записи в текстовый файл (0 для завершения записи):\n");
    int num;
    while (1) {
        num = safeInput();
        if (num == 0) {
            break;
        }
        fprintf(file, "%d\n", num);
    }
    fclose(file);

    // вывод 
    printf("Содержимое файла:\n");
    printFile(filename);
    printf("Четные элементы файла:\n");
    printEvenFile(filename);
    multiply(filename, "multiplication_result.txt");

    return 0;
}

int safeInput() {
    char buffer[100];
    int num;

    while (1) {
        printf("Введите число (0 для завершения): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
              if (sscanf_s(buffer, "%d", &num) == 1) {
                return num; 
            }
            else {
                printf("Неверный ввод. Пожалуйста, введите целое число.\n");
            }
        }
        else {
            printf("Ошибка ввода. Пожалуйста, попробуйте снова.\n");
        }
    }
}

void printFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int num;
    while (fscanf_s(file, "%d", &num) == 1) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}

void printEvenFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int num;
    while (fscanf_s(file, "%d", &num) == 1) {
        if (num % 2 == 0) {
            printf("%d ", num);
        }
    }
    printf("\n");
    fclose(file);
}

void multiply(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "r");
    if (!inputFile) {
        perror("Ошибка открытия исходного файла");
        return;
    }

    int num1, num2;
    if (fscanf_s(inputFile, "%d", &num1) != 1 || fscanf_s(inputFile, "%d", &num2) != 1) {
        printf("В файле должно быть как минимум два числа.\n");
        fclose(inputFile);
        return;
    }
    fclose(inputFile);

    FILE* outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        perror("Ошибка создания файла для результата");
        return;
    }

    // оформление записи в столбик
    fprintf(outputFile, "  %d\n", num1);
    fprintf(outputFile, "× %d\n", num2);
    fprintf(outputFile, "-----\n");
    fprintf(outputFile, "  %d\n", num1 * num2);
    fclose(outputFile);
    printf("Результат умножения записан в файл: %s\n", outputFilename);
}
