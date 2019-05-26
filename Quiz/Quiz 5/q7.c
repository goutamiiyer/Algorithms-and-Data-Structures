#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int fact_v4(int N) {

    static int res = 1; 

    if (N == 0) return res;

    res = res * N;

    fact_v4(N-1);

    return res;

}

int main(){

    int res1 = fact_v4(4);
    printf("\n\t Main res1: %d", res1);

    int res2 = fact_v4(4);
    printf("\n\t Main res2: %d", res2);

}
