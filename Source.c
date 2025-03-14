#include <stdio.h>
#include <stdlib.h>

// запись в файл
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

// поиск цифры в ффайле
void findNumber(const char* filename, int target) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int num;
    int found = 0;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        if (num == target) {
            printf("Number %d found in the file.\n", target);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Number %d not found in the file.\n", target);
    }
    fclose(file);
}

// свап двух цифр в файле
void swapNumbers(const char* filename, int pos1, int pos2) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int num1, num2;

    // Read the first number
    fseek(file, pos1 * sizeof(int), SEEK_SET);
    fread(&num1, sizeof(int), 1, file);

    // Read the second number
    fseek(file, pos2 * sizeof(int), SEEK_SET);
    fread(&num2, sizeof(int), 1, file);

    // Write the numbers to their new positions
    fseek(file, pos1 * sizeof(int), SEEK_SET);
    fwrite(&num2, sizeof(int), 1, file);

    fseek(file, pos2 * sizeof(int), SEEK_SET);
    fwrite(&num1, sizeof(int), 1, file);

    fclose(file);
}

// сколько уникальных цифр в файле

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
void insertNumber(const char* filename, int num) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int current;
    long pos = 0;

    // Find the position to insert the number
    while (fread(&current, sizeof(int), 1, file) == 1) {
        if (current < num) {
            break;
        }
        pos++;
    }

    // Shift elements to the right
    fseek(file, 0, SEEK_END);
    long end = ftell(file);
    while (end > pos * sizeof(int)) {
        fseek(file, end - sizeof(int), SEEK_SET);
        fread(&current, sizeof(int), 1, file);
        fseek(file, end, SEEK_SET);
        fwrite(&current, sizeof(int), 1, file);
        end -= sizeof(int);
    }

    
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
        //read the left element
        fseek(file, left * sizeof(int), SEEK_SET);
        fread(&num1, sizeof(int), 1, file);

        //   read the right element
        fseek(file, right * sizeof(int), SEEK_SET);
        fread(&num2, sizeof(int), 1, file);

    // swap
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
 
// write numbers to the file
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    int num;
    printf("Enter integers (enter 0 to finish):\n");
    while (scanf_s("%d", &num) == 1 && num != 0) {
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);


    printf("File contents:\n");
    printFile(filename);
// search 
    int target;
    printf("Enter a number to search: ");
    scanf_s("%d", &target);
    findNumber(filename, target);

// swap
    int pos1, pos2;
    printf("Enter positions to swap (starting from 0): ");
    scanf_s("%d %d", &pos1, &pos2);
    swapNumbers(filename, pos1, pos2);
    printf("File contents after swapping:\n");
    printFile(filename);




    int uniqueCount = countUniqueNumbers(filename);
    printf("Number of unique numbers: %d\n", uniqueCount);

//Insert
    int newNum;
    printf("Enter a number to insert: ");
    scanf_s("%d", &newNum);
    insertNumber(filename, newNum);
    printf("File contents after insertion:\n");
    printFile(filename);

//reverss
    reverseFile(filename);
    printf("File contents after reversing:\n");
    printFile(filename);

    return 0;
}
