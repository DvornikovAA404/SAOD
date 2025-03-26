#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

int BSearchI(int N, int A[], int Key, int *Cf){
    int L = 1, R = N, m;
    int Bool = 0;
    while(L<=R){
        m = (L+R)/2;
        (*Cf)++;
        if(A[m]==Key){
            Bool = 1;
            break;
        }
        (*Cf)++;
        if(A[m]<Key){
            L = m+1;
        } else {
            R = m-1;
        }
    }
    return Bool;
}
int BSearchII(int N, int A[], int Key, int *Cf){
    int L = 0, R = N-1;
    int Bool = 0;
    while(L<R){
        int m = floor((L+R)/2);
        (*Cf)++;
        if(A[m] < Key ){ L = m+1; } else { R = m; }
    }
    (*Cf)++;
    if(A[R] == Key){
        Bool = 1;
    } else { Bool = 0; }
    return Bool;
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
    printf("| %-5s | %-13s | %-13s |\n", "N", "Cф I", "Cф II");
}

void PrintTableRow(int N, int Mf_Cf_I, int Mf_Cf_II) {
    printf("| %-5d | %-12d | %-12d |\n",
           N, Mf_Cf_I, Mf_Cf_II);
}


int main() {
    int sumdo, sdo, sumposle, sposle;
    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int Cf, Mf;
    printf("\n");
    PrintTableHeader();

    for(int i = 1; i <= 10; i++){
        int N = i * 100;
        int ArrInc[N], ArrDec[N], ArrRand[N];
        int I = 0, II = 0;

        FillRand(ArrRand, N);
        ShellSort(ArrRand, N, &Cf, &Mf);
        Cf = 0;
        int Find = BSearchI(N, ArrRand, 599, &Cf);
        I = Cf;

        Cf = 0;
        Find = BSearchII(N, ArrRand, 2, &Cf);
        II = Cf;
        PrintTableRow(N, I, II);
    }
    return 0;
}
