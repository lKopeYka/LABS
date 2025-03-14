#include <stdio.h>
#include <stdlib.h>

// вывож файла
void printFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int num;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}

// подсчет уникальных чисел
int countUniqueNumbers(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int prev, current;
    int count = 0;

    if (fread(&prev, sizeof(int), 1, file) == 1) {
        count = 1;
        while (fread(&current, sizeof(int), 1, file) == 1) {
            if (current != prev) {
                count++;
                prev = current;
            }
        }
    }

    fclose(file);
    return count;
}

// вставка с сохранением порядка
void insertNumber(const char* filename, int num) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int current;
    long pos = 0;


    while (fread(&current, sizeof(int), 1, file) == 1) {
        if (current < num) {
            break;
        }
        pos++;
    }

    // сдвиг
    fseek(file, 0, SEEK_END);
    long end = ftell(file);
    while (end > pos * sizeof(int)) {
        fseek(file, end - sizeof(int), SEEK_SET);
        fread(&current, sizeof(int), 1, file);
        fseek(file, end, SEEK_SET);
        fwrite(&current, sizeof(int), 1, file);
        end -= sizeof(int);
    }

    // вставка 
    fseek(file, pos * sizeof(int), SEEK_SET);
    fwrite(&num, sizeof(int), 1, file);

    fclose(file);
}

// реверс элементов в файле
void reverseFile(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    int num1, num2;
    long left = 0, right = size / sizeof(int) - 1;

    while (left < right) {
        // левый элемент
        fseek(file, left * sizeof(int), SEEK_SET);
        fread(&num1, sizeof(int), 1, file);

        //правый элемент
        fseek(file, right * sizeof(int), SEEK_SET);
        fread(&num2, sizeof(int), 1, file);

        // свап
        fseek(file, left * sizeof(int), SEEK_SET);
        fwrite(&num2, sizeof(int), 1, file);

        fseek(file, right * sizeof(int), SEEK_SET);
        fwrite(&num1, sizeof(int), 1, file);

        left++;
        right--;
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    // запись в файл
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    int num;
    printf("Enter integers in non-increasing order (enter 0 to finish):\n");
    while (scanf_s("%d", &num) == 1 && num != 0) {
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);

 // вывод
    printf("File contents:\n");
    printFile(filename);

   // кол во уникальных чисел
    int uniqueCount = countUniqueNumbers(filename);
    printf("Number of unique numbers: %d\n", uniqueCount);

 // запись доп чисел в файл
    printf("Enter additional numbers (enter 0 to finish):\n");
    while (scanf_s("%d", &num) == 1 && num != 0) {
        insertNumber(filename, num);
    }
    printf("File contents after insertion:\n");
    printFile(filename);

 // реверс
    reverseFile(filename);
    printf("File contents after reversing:\n");
    printFile(filename);

    return 0;
}
