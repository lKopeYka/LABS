#include <stdio.h>
#include <stdlib.h>

void printFile();
void printEvenFile();

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: % s <filename>\n", argv[0]);
		return 1;
	}
	const char* filename = argv[1];

    //открытие файла 
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror(" Error creating file");
        return 1;
    }
    //заполнение тексового файла целыми числами
    printf("vvodite celie chisla dlia zapisi v tekstovi fail(0 dlia zavershenia zapisi)");
    int num;
    while (1) {
        int num = fputs(&num, filename);
;        
        fwrite(&num, sizeof(int), 1, filename);
    }
    fclose(filename);
    //вывод содержимого файла на экран
    printf("soderzhimoe faila");
    printFile(filename);
    //вывод на экран всех четных элементов файла
    printEvenFile(filename);


}









// Функция для безопасного ввода числа safeInput
int safeInput() {
    char buffer[100]; // Буфер для хранения ввода
    int num;

    while (1) {
        printf("Enter a number (0 to finish): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Пытаемся преобразовать строку в число
            if (sscanf_s(buffer, "%d", &num) == 1) {
                return num; // Успешный ввод числа
            }
            else {
                printf("Invalid input. Please enter an integer.\n");
            }
        }
        else {
            printf("Input error. Please try again.\n");
        }
    }
}
//функция для вывода файла 
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
//функция для вывода четных элементов массива
void printEvenFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }
    printf("Chetnie elementi faila");
    int EvenNum;
    while (fread(&EvenNum, sizeof(int), 1, file) == 1) {
        if (EvenNum % 2 == 0) {
            printf("d", EvenNum);
        }
    }
    printf("\n");
    fclose(file);
}