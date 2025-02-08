#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 100
#define DEBUG 0

void FillInc(int Arr[N]){
    for(int i = 0; i < N; i++){
        Arr[i] = i;
    }
}

void FillDec(int Arr[N]){
    for(int i = 0; i < N; i++){
        Arr[N-i-1] = i; 
    }
}

void FillRand(int Arr[N]){
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        Arr[i] = rand();
        if (DEBUG){
            Arr[i] = rand() % 11;
        }
    }
}

long int CheckSum(int Arr[N]){
    long int sum = 0;
    for(int i = 0; i < N; i++){
        sum += Arr[i];
    }
    return sum;
}


int AvgSeries(int Arr[N]){
    int series = 0;
    int s_counter = 0;
    for(int i = 1; i < N; i++){
        if(Arr[i-1] < Arr[i]){
            s_counter++;
        }
        else if(s_counter>0){
            s_counter = 0;
            series++;
        }
        if(i == N-1 && s_counter>0){
            series++;
        }
    }
    return series;
}

int RunNumber(int Arr[N]){
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

void PrintMas(int Arr[N]){
    for(int i = 0; i < N; i++){
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

void SelectSort(int Arr[N], int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;

    for(int i = 0; i<N; i++){
        int k = i;
        for(int j = i; j<N; j++){
            (*Cf)++;
            if(Arr[j] < Arr[k]){
                k = j;
            }
        }
        if(1){
            int buffer = Arr[i];
            Arr[i] = Arr[k];
            Arr[k] = buffer;
            (*Mf)++;
        }
    }
}

int main(){
    int A[N];
    FillRand(A); // N10 Cf 55 ; Mf 10 | N100 Cf 5050; Mf 100 
    // FillInc(A); // N10 Cf 55; Mf 10 | N100 Cf 5050; Mf 100
    // FillDec(A); // N10 Cf 55; Mf 10 | N100 Cf 5050; Mf 100
    printf("Контрольная сумма до: %ld\n", CheckSum(A));
    printf("Количество серий до: %d\n", RunNumber(A));
    //PrintMas(A);
    printf("------------------------------\n");
    int Cf, Mf;
    SelectSort(A, &Cf, &Mf);
    printf("Контрольная сумма до: %ld\n", CheckSum(A));
    printf("Количество серий до: %d\n", RunNumber(A));
    printf("Сравнений: %d\n", Cf);
    printf("Пересылок: %d\n", Mf);
    //PrintMas(A);
}