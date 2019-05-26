#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int fact_2 (int N) {   

    int res;

    printf("\n\t fact_2(N=%d)",N);
    // printf("\n\t Before res: %d", res);

    if (N <= 1) return 1;

    res= N*fact_2 (N-1);
    printf("\n\t After res for N=%d: %d", N,res);

    //T: res is:

    return res;

}

int main(){

    fact_2(6);

}
