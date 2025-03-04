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

void ShakerSort(int Arr[], int N, int *Cf, int *Mf) {
    *Cf = 0;
    *Mf = 0;
    int L = 0, R = N - 1, k = N - 1; // Ð Â˜Ð Ð…Ð Ò‘Ð ÂµÐ Ñ”Ð¡ÐƒÐ Â°Ð¡â€ Ð Ñ‘Ð¡Ð Ð¡Ðƒ 0

    do {
        // Ð ÑŸÐ¡Ð‚Ð Ñ•Ð¡â€¦Ð Ñ•Ð Ò‘ Ð¡ÐƒÐ Ñ—Ð¡Ð‚Ð Â°Ð Ð†Ð Â° Ð Ð…Ð Â°Ð Â»Ð ÂµÐ Ð†Ð Ñ•
        for (int j = R; j > L; j--) {
            (*Cf)++;
            if (Arr[j] < Arr[j - 1]) {
                int buffer = Arr[j];
                Arr[j] = Arr[j - 1];
                Arr[j - 1] = buffer;
                k = j;
                (*Mf) += 3;
            }
        }
        L = k;

        // Ð ÑŸÐ¡Ð‚Ð Ñ•Ð¡â€¦Ð Ñ•Ð Ò‘ Ð¡ÐƒÐ Â»Ð ÂµÐ Ð†Ð Â° Ð Ð…Ð Â°Ð Ñ—Ð¡Ð‚Ð Â°Ð Ð†Ð Ñ•
        for (int j = L; j < R; j++) {
            (*Cf)++;
            if (Arr[j] > Arr[j + 1]) {
                int buffer = Arr[j];
                Arr[j] = Arr[j + 1];
                Arr[j + 1] = buffer;
                k = j;
                (*Mf) += 3;
            }
        }
        R = k;
    } while (L < R);
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

void BubbleSort(int Arr[], int N, int *Cf, int *Mf){
    *Cf = 0;
    *Mf = 0;
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N-i-1; j++){
            (*Cf)++;
            if(Arr[j] > Arr[j+1]){
                int buffer = Arr[j];
                Arr[j] = Arr[j+1];
                Arr[j+1] = buffer;
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
    printf("| %-5s | %-13s | %-33s |\n", "N", " M + C ", "Insert Sort");
    printf("|       |               | Убыв.   | Случ.   | Возр.         |\n");
}

void PrintTableRow(int N, int M_C_theoretical, int Mf_Cf_original[], int Mf_Cf_improved[]) {
    printf("| %-5d | %-13d | %-7d | %-7d | %-13d |\n",
           N,
           M_C_theoretical,
           Mf_Cf_improved[0], Mf_Cf_improved[1], Mf_Cf_improved[2]);
}

void PrintSecTableHeader() {
    printf("| %-5s | %-13s | %-13s | %-13s | %-13s |\n", "N", " Select Sort ", " Bubble Sort ", " Shaker Sort ", " InsertSort ");
}

void PrintSecTableRow(int N, int M_C_Select, int M_C_Bubble, int M_C_Shaker, int M_C_Insert) {
    printf("| %-5d | %-13d | %-13d | %-13d | %-13d |\n",
           N,
           M_C_Select, M_C_Bubble, M_C_Shaker, M_C_Insert);
}

int main() {
    int sumdo, sdo, sumposle, sposle;
    const int sizes[] = {100, 200, 300, 400, 500};
    int Cf = 0, Mf = 0;
    
    printf("\n");
    PrintTableHeader();

    for(int i = 0; i < 5; i++){
        int N = sizes[i];
        int ArrInc[N], ArrDec[N], ArrRand[N];
        int Mf_Cf_original[3] = {0};
        int Mf_Cf_improved[3] = {0};

        int M_C_theoretical = (((N*N)-N)/2)+((((N*N)-N)/2)) + 2 * N - 2;
        
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
        
        if (sumdo != sumposle) {
            printf("Warning: Checksum mismatch for N=%d\n", N);
        }
        
        Mf_Cf_improved[1] = Mf + Cf;
        PrintTableRow(N, M_C_theoretical, 0, Mf_Cf_improved);
    }
    
    printf("\n\n");
    PrintSecTableHeader();
    
    for(int i = 0; i < 5; i++){
        int N = sizes[i];
        int ArrRand[N];
        int Mf_Cf_Select = 0;
        int Mf_Cf_Bubble = 0;
        int Mf_Cf_Shaker = 0;
        int Mf_Cf_Insert = 0;

        FillRand(ArrRand, N);
        SelectSortSimple(ArrRand, N, &Cf, &Mf);
        Mf_Cf_Select = Mf + Cf;

        FillRand(ArrRand, N);
        BubbleSort(ArrRand, N, &Cf, &Mf);
        Mf_Cf_Bubble = Mf + Cf;

        FillRand(ArrRand, N);
        ShakerSort(ArrRand, N, &Cf, &Mf);
        Mf_Cf_Shaker = Mf + Cf;

        FillRand(ArrRand, N);
        InsertSort(ArrRand, N, &Cf, &Mf);
        Mf_Cf_Insert = Mf + Cf;

        PrintSecTableRow(N, Mf_Cf_Select, Mf_Cf_Bubble, Mf_Cf_Shaker, Mf_Cf_Insert);
    }
    return 0;
}

