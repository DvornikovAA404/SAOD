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

void SelectSortSimple(int Arr[], int N, int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;

    for(int i = 0; i < N-1; i++){
        int k = i;
        for(int j = i; j < N; j++){
            (*Cf)++;
            if(Arr[j] < Arr[k]){
                k = j;
            }
        }
        if(1){ // k != i
            int buffer = Arr[i];
            Arr[i] = Arr[k];
            Arr[k] = buffer;
            (*Mf) += 2;
        }
    }
}

void SelectSortImproved(int Arr[], int N, int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;

    for(int i = 0; i < N; i++){
        int k = i;
        for(int j = i + 1; j < N; j++){ 
            (*Cf)++;
            if(Arr[j] < Arr[k]){
                k = j;
            }
        }
        if(k != i){
            int buffer = Arr[i];
            Arr[i] = Arr[k];
            Arr[k] = buffer;
            (*Mf) += 3;
        }
    }
}

void PrintTableHeader() {
    printf("| %-5s | %-15s | %-37s | %-37s |\n", "N", "M+C теоретич.", "Исходный Mfact + Cfact", "Улучшенный Mfact + Cfact");
    printf("|       |               | Убыв. | Случ. | Возр.         | Убыв. | Случ. | Возр.       |\n");
}

void PrintTableRow(int N, int M_C_theoretical, int Mf_Cf_original[], int Mf_Cf_improved[]) {
    printf("| %-5d | %-13d | %-5d | %-5d | %-13d | %-5d | %-5d | %-11d |\n",
           N, M_C_theoretical,
           Mf_Cf_original[0], Mf_Cf_original[1], Mf_Cf_original[2],
           Mf_Cf_improved[0], Mf_Cf_improved[1], Mf_Cf_improved[2]);
}

int main() {
    int sizes[] = {10, 100};
    int Cf, Mf;
    printf("\n");
    PrintTableHeader();

    for(int i = 0; i < 2; i++){
        int N = sizes[i];
        int ArrInc[N], ArrDec[N], ArrRand[N];
        int Mf_Cf_original[3] = {0};
        int Mf_Cf_improved[3] = {0};

        int M_C_theoretical = (((N*N)-N)/2)+(3*(N-1));

        // Simple SelectSort
        FillInc(ArrInc, N);
        SelectSortSimple(ArrInc, N, &Cf, &Mf);
        Mf_Cf_original[2] = Mf + Cf;

        FillDec(ArrDec, N);
        SelectSortSimple(ArrDec, N, &Cf, &Mf);
        Mf_Cf_original[0] = Mf + Cf;

        FillRand(ArrRand, N);
        SelectSortSimple(ArrRand, N, &Cf, &Mf);
        Mf_Cf_original[1] = Mf + Cf;

        // Improved SelectSort
        FillInc(ArrInc, N);
        SelectSortImproved(ArrInc, N, &Cf, &Mf);
        Mf_Cf_improved[2] = Mf + Cf;

        FillDec(ArrDec, N);
        SelectSortImproved(ArrDec, N, &Cf, &Mf);
        Mf_Cf_improved[0] = Mf + Cf;

        FillRand(ArrRand, N);
        SelectSortImproved(ArrRand, N, &Cf, &Mf);
        Mf_Cf_improved[1] = Mf + Cf;

        PrintTableRow(N, M_C_theoretical, Mf_Cf_original, Mf_Cf_improved);
    }
    printf("\n");
    return 0;
}
