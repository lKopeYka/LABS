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

    //�������� ����� 
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror(" Error creating file");
        return 1;
    }
    //���������� ��������� ����� ������ �������
    printf("vvodite celie chisla dlia zapisi v tekstovi fail(0 dlia zavershenia zapisi)");
    int num;
    while (1) {
        int num = fputs(&num, filename);
;        
        fwrite(&num, sizeof(int), 1, filename);
    }
    fclose(filename);
    //����� ����������� ����� �� �����
    printf("soderzhimoe faila");
    printFile(filename);
    //����� �� ����� ���� ������ ��������� �����
    printEvenFile(filename);


}









// ������� ��� ����������� ����� ����� safeInput
int safeInput() {
    char buffer[100]; // ����� ��� �������� �����
    int num;

    while (1) {
        printf("Enter a number (0 to finish): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // �������� ������������� ������ � �����
            if (sscanf_s(buffer, "%d", &num) == 1) {
                return num; // �������� ���� �����
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
//������� ��� ������ ����� 
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
//������� ��� ������ ������ ��������� �������
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