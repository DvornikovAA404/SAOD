#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEBUG 0

void FillInc(int Arr[], int N){
    for(int i = 0; i < N; i++){
        Arr[i] = i;
    }
}

void FillDec(int Arr[], int N){
    for(int i = 0; i < N; i++){
        Arr[N-i-1] = i;
    }
}

void FillRand(int Arr[], int N){
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        Arr[i] = rand();
        if (DEBUG){
            Arr[i] = rand() % 11;
        }
    }
}

int StepGen(int N){
    int i = 2;
    int h = 0;
    while(i <= N){
        i = i * 2;
        h++;
    }
    h--;
    return h;
}

void InsertSort(int * A, int n, int * Mf, int * Cf){

    (*Mf) = 0;
    (*Cf) = 0;
    for(int i = 1; i < n; i++){
        (*Mf)++;int t = A[i];
        int j = i-1;
        while(j >= 0 && ((*Cf)=(*Cf)+1,t < A[j])){
            (*Mf)++;A[j+1] = A[j];
            j = j-1;
        }
        (*Mf)++;A[j+1] = t;
    }

}

void ShellSort(int Arr[], int N, int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;
    int l = StepGen(N);
    int B[l];
    B[0] = 1;
    for (int i = 1; i<l; i++){
        B[i] = B[i-1]*2+1;
    }
    for(; l>0; l--){
        int k = B[l-1];
        for(int i = k; i<N; i++){
            int t = Arr[i];
            (*Mf)++;
            int j = i-k;
            while(j>=0 && ((*Cf)++, t<Arr[j])){
                Arr[j+k] = Arr[j];
                (*Mf)++;
                j -= k;
            }
            Arr[j+k] = t;
            (*Mf)++;
        }
    }
}


void PrintMas(int N, int Arr[N]){
    for(int i = 0; i < N; i++){
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

long int CheckSum(int Arr[], int N){
    long int sum = 0;
    for(int i = 0; i < N; i++){
        sum += Arr[i];
    }
    return sum;
}

int RunNumber(int Arr[], int N){
    int series = 0;
    int s_counter = 1;
    for(int i = 1; i < N; i++){
        if(Arr[i] >= Arr[i-1]){
            s_counter++;
        }
        else{
            s_counter = 1;
            series++;
        }
        if(i == N-1 && s_counter>0){
            series++;
        }
    }
    return series;
}



void PrintTableHeader() {
    printf("| %-5s | %-19s | %-13s | %-13s |\n", "N", "h1 ... hm", "Insert Sort", "Shell Sort");
}

void PrintTableRow(int N, int l, int B[l], int Insert, int Mf_Cf_original) {
    // Инициализация буфера str нулевым символом
    char str[35] = "";

    // Объединение элементов массива B в строку
    for (int i = 0; i < l; i++) {
        char buffer[30];
        sprintf(buffer, "%d ", B[i]);
        if (strlen(str) + strlen(buffer) < sizeof(str) - 1) {
            strcat(str, buffer);
        } else {
            break; // Прекращаем, если строка слишком длинная
        }
    }

    // Добавляем пробелы для выравнивания
    while (strlen(str) < 19) {
        strcat(str, " ");
    }

    // Вывод таблицы
    printf("| %-5d | ", N);
    printf("%-19s ", str);
    printf("| %-13d | %-13d |\n", Insert, Mf_Cf_original);
}


int main() {
    int sumdo, sdo, sumposle, sposle;
    int sizes[] = {100, 200, 300, 400, 500};
    int Cf, Mf;
    printf("\n");
    PrintTableHeader();

    for(int i = 0; i < 5; i++){
        int N = sizes[i];
        int ArrInc[N], ArrDec[N], ArrRand[N];
        int Mf_Cf_original = 0;
        int InsertT = 0;

        int l = StepGen(N);
        int B[l];
        B[0] = 1;
        for (int i = 1; i<l; i++){
            B[i] = B[i-1]*2+1;
        }

        FillRand(ArrRand, N);
        ShellSort(ArrRand, N, &Cf, &Mf);
        Mf_Cf_original = Cf + Mf;

        FillRand(ArrRand, N);
        InsertSort(ArrRand, N, &Mf, &Cf);
        InsertT = Cf + Mf;

        PrintTableRow(N, l, B, InsertT, Mf_Cf_original);
    }
    return 0;
}
