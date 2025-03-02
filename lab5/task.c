#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void BubbleSort(int Arr[], int N, int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;
    for(int i = 0; i < N; i++){
        for(int j = N; j > i+1; j--){
            (*Cf)++;
            if(Arr[j] <= Arr[j-1]){
                int buffer = Arr[j];
                Arr[j] = Arr[j-1];
                Arr[j-1] = buffer;
                (*Mf) += 3;
            }
        }
    }
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
    printf("| %-5s | %-33s | %-33s |\n", "N", "Bubble Sort", "Shaker Sort");
    printf("|       | Убыв.   | Случ.   | Возр.         | Убыв.   | Случ.   | Возр.         |\n");
}

void PrintTableRow(int N, int M_C_theoretical, int Mf_Cf_original[], int Mf_Cf_improved[]) {
    printf("| %-5d | %-7d | %-7d | %-13d | %-7d | %-7d | %-13d |\n",
           N,
           Mf_Cf_original[0], Mf_Cf_original[1], Mf_Cf_original[2],
           Mf_Cf_improved[0], Mf_Cf_improved[1], Mf_Cf_improved[2]);
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
        int Mf_Cf_original[3] = {0};
        int Mf_Cf_improved[3] = {0};

        // Theoretical M+C for SelectSort is approximately N^2
        int M_C_theoretical = (((N*N)-N)/2)+(3*(N-1));

        // BubbleSort
        FillInc(ArrInc, N);
        BubbleSort(ArrInc, N, &Cf, &Mf);
        Mf_Cf_original[2] = Mf + Cf;

        FillDec(ArrDec, N);
        BubbleSort(ArrDec, N, &Cf, &Mf);
        Mf_Cf_original[0] = Mf + Cf;

        FillRand(ArrRand, N);
        BubbleSort(ArrRand, N, &Cf, &Mf);
        Mf_Cf_original[1] = Mf + Cf;

        // Improved SelectSort
        FillInc(ArrInc, N);
        InsertSort(ArrInc, N, &Cf, &Mf);
        Mf_Cf_improved[2] = Mf + Cf;

        FillDec(ArrDec, N);
        InsertSort(ArrDec, N, &Cf, &Mf);
        Mf_Cf_improved[0] = Mf + Cf;

        FillRand(ArrRand, N);
        sumdo = CheckSum(ArrRand, N);
        sdo = RunNumber(ArrRand, N);
        InsertSort(ArrRand, N, &Cf, &Mf);
        sumposle = CheckSum(ArrRand, N);
        sposle = RunNumber(ArrRand, N);
        Mf_Cf_improved[1] = Mf + Cf;

        PrintTableRow(N, M_C_theoretical, Mf_Cf_original, Mf_Cf_improved);
    }
    return 0;
}
