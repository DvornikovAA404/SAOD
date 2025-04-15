#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int C = 0; // Счетчик сравнений
int M = 0; // Счетчик пересылок

void FillInc(int Arr[], int N) {
    for(int i = 0; i < N; i++) 
        Arr[i] = i + 1;
}

void FillDec(int Arr[], int N) {
    for(int i = 0; i < N; i++)
        Arr[i] = N - i;
}

void FillRand(int Arr[], int N) {
    for(int i = 0; i < N; i++)
        Arr[i] = rand() % 1000;
}

int CheckSum(int Arr[], int N) {
    int sum = 0;
    for(int i = 0; i < N; i++)
        sum += Arr[i];
    return sum;
}

int RunNumber(int Arr[], int N) {
    int count = 1;
    for(int i = 1; i < N; i++)
        if(Arr[i] < Arr[i-1])
            count++;
    return count;
}

void PrintMas(int Arr[], int N) {
    for(int i = 0; i < N; i++)
        printf("%d ", Arr[i]);
    printf("\n");
}

void Swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
    M += 3; // Учитываем 3 пересылки при обмене
}

int Partition(int Arr[], int L, int R) {
    int x = Arr[L]; // Опорный элемент
    int i = L;
    int j = R;
    
    while(1) {
        while(Arr[i] < x) { C++; i++; }
        C++; // Учет последнего сравнения, когда условие не выполнилось
        while(Arr[j] > x) { C++; j--; }
        C++; // Учет последнего сравнения, когда условие не выполнилось
        
        if(i < j) {
            Swap(&Arr[i], &Arr[j]);
            i++;
            j--;
        } else {
            return j;
        }
    }
}

void QuickSort(int Arr[], int L, int R) {
    if(L < R) {
        int q = Partition(Arr, L, R);
        QuickSort(Arr, L, q);
        QuickSort(Arr, q+1, R);
    }
}

void PrintTableHeader() {
    printf("| %-5s | %-41s |\n", "N", "Исходный Mfact + Cfact");
    printf("|       | Убыв.   | Возр.  | Случ.          |\n");
}

void PrintTableRow(int N, int Mf_Cf_original[]) {
    printf("| %-5d | %-7d | %-6d | %-14d |\n",
           N, 
           Mf_Cf_original[0], Mf_Cf_original[1], Mf_Cf_original[2]);
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};

    printf("Трудоемкость метода Хоара (QuickSort)\n");
    PrintTableHeader();
    
    for(int i = 0; i < 5; i++) {
        int N = sizes[i];
        int Mf_Cf[3] = {0};
        
        // Теоретическая оценка (в среднем случае)
        double teor = N * log2(N);
        int teor_total = (int)teor;

        // Убывающий массив
        int ArrDec[N];
        FillDec(ArrDec, N);
        QuickSort(ArrDec, 0, N-1);
        Mf_Cf[0] = C + M;
        C = M = 0;

        // Возрастающий массив
        int ArrInc[N];
        FillInc(ArrInc, N);
        QuickSort(ArrInc, 0, N-1);
        Mf_Cf[1] = C + M;
        C = M = 0;

        // Случайный массив
        int ArrRand[N];
        FillRand(ArrRand, N);
        QuickSort(ArrRand, 0, N-1);
        Mf_Cf[2] = C + M;
        C = M = 0;

        PrintTableRow(N, Mf_Cf);
    }

    return 0;
}
