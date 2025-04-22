#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int C = 0;
int M = 0;

int C_build = 0;
int M_build = 0;

void FillInc(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000;
    }
}

int CheckSum(int n, int A[]) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

void PrintMas(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

double calculate_M(int n) {
    return n * log2(n) + 6.5 * n - 4;
}

double calculate_C(int n) {
    return 2 * n * log2(n) + n + 2;
}

double calculate_M_build(int n) {
    return log2(n) + 2;
}

double calculate_C_build(int n) {
    return 2 * log2(n) + 1;
}

void HeapBuild(int A[], int L, int R) {
    int x = A[L];
    M++;
    M_build++;
    int i = L;
    while (1) {
        int j = 2 * i + 1;
        if (j > R)
            break;

        C++;
        C_build++;
        if (j < R && A[j + 1] > A[j]) {
            j++;
        }

        C++;
        C_build++;
        if (x >= A[j])
            break;

        A[i] = A[j];
        M++;
        M_build++;
        i = j;
    }

    if (i != L) {
        M++;
        M_build++;
    }
    M++;
    M_build++;
    A[i] = x;
}

void HeapSort(int A[], int n) {
    int temp;
    for (int L = n / 2 - 1; L >= 0; L--) {
        HeapBuild(A, L, n - 1);
    }

    for (int R = n - 1; R > 0; R--) {
        temp = A[0];
        M++;
        A[0] = A[R];
        M++;
        A[R] = temp;
        M++;

        HeapBuild(A, 0, R - 1);
    }
}

void PrintTableHeader() {
    printf("| %-5s | %-15s | %-41s |\n", "N", "M+C теоретич.", "Исходный Mfact + Cfact");
    printf("|       |               | Убыв.   | Случ.  | Возр.          |\n");
}

void PrintTableRow(int N, int M_C_theoretical, int Mf_Cf_original[]) {
    printf("| %-5d | %-13d | %-7d | %-6d | %-14d |\n",
           N, M_C_theoretical,
           Mf_Cf_original[0], Mf_Cf_original[1], Mf_Cf_original[2]);
}

void PrintTableHeader2() {
    printf("| %-5s | %-41s |\n", "N", "Исходный Mfact + Cfact");
    printf("|       | Убыв.   | Случ.  | Возр.          |\n");
}

void PrintTableRow2(int N, int M_C_theoretical, int Mf_Cf_original[]) {
    printf("| %-5d | %-7d | %-6d | %-14d |\n",
           N,
           Mf_Cf_original[0], Mf_Cf_original[1], Mf_Cf_original[2]);
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};

    printf("Таблица 1: Трудоемкость построения пирамиды\n");
    PrintTableHeader();

    for (int i = 0; i < 5; i++) {
        int N = sizes[i];
        int teor = (int)(calculate_M_build(N) + calculate_C_build(N));
        int Mf_Cf_original[3] = {0};

        int ArrDec[N];
        FillDec(N, ArrDec);
        HeapBuild(ArrDec, 0, N - 1);
        Mf_Cf_original[0] = C_build + M_build;
        C_build = 0;
        M_build = 0;

        int ArrRand[N];
        FillRand(N, ArrRand);
        HeapBuild(ArrRand, 0, N - 1);
        Mf_Cf_original[1] = C_build + M_build;
        C_build = 0;
        M_build = 0;

        int ArrInc[N];
        FillInc(N, ArrInc);
        HeapBuild(ArrInc, 0, N - 1);
        Mf_Cf_original[2] = C_build + M_build;
        C_build = 0;
        M_build = 0;

        PrintTableRow(N, teor, Mf_Cf_original);
    }

    printf("\nТаблица 2: Трудоемкость сортировки\n");
    PrintTableHeader2();

    for (int i = 0; i < 5; i++) {
        int N = sizes[i];
        int teor = (int)(calculate_M(N) + calculate_C(N));
        int Mf_Cf_original[3] = {0};

        int ArrDec[N];
        FillDec(N, ArrDec);
        HeapSort(ArrDec, N);
        Mf_Cf_original[0] = C + M;
        C = 0;
        M = 0;

        int ArrRand[N];
        FillRand(N, ArrRand);
        HeapSort(ArrRand, N);
        Mf_Cf_original[1] = C + M;
        C = 0;
        M = 0;

        int ArrInc[N];
        FillInc(N, ArrInc);
        HeapSort(ArrInc, N);
        Mf_Cf_original[2] = C + M;
        C = 0;
        M = 0;

        PrintTableRow2(N, teor, Mf_Cf_original);
    }

    return 0;
}