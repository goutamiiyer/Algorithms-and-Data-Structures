#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int fact_v3(int N) {

    int res = 1; 

    if (N == 0) return res;

    res = res * N;

    fact_v3(N-1);
    printf("\n\t res: %d", res);

    return res;

}
int main(){

    int res = fact_v3(4);
    printf("\n\t Main res: %d", res);

}
