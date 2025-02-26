#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10
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

void view(int *Arr, int size){
    printf("%d\n", size);
    for(int i = 0; i < size; i++){
        printf("%d\n", Arr[i]);
    }
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

int main(){
    int A[N];
    printf(" --- Возрастающий массив ---\n");
    FillInc(A);
    PrintMas(A);
    printf("Контрольная сумма: %ld\n", CheckSum(A));
    printf("Количество серий: %d\n", RunNumber(A));
    printf(" --- Убывающий массив ---\n");
    FillDec(A);
    PrintMas(A);
    printf("Контрольная сумма: %ld\n", CheckSum(A));
    printf("Количество серий: %d\n", RunNumber(A));
    printf(" --- Случайный массив ---\n");
    FillRand(A);
    PrintMas(A);
    printf("Контрольная сумма: %ld\n", CheckSum(A));
    printf("Количество серий: %d\n", RunNumber(A));

}