#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void fact_tail_2(int N, int* res) {

    printf("\n\t fact_tail_2(N=%d,res=%d)",N,*res);

    if (N <= 1) return;

    (*res) = (*res) * N;

    //T1
    printf(",T1 res for N=%d: %d", N, res);

    fact_tail_2(N-1, res);

}

 // Wrapper  function (sets parameters).

int fact_tail_2_wrapper (int N) {

    int res = 1;

    fact_tail_2(N, &res);

    // T2: What will res be at this point?
    printf("\n\t T2 res: %d", res);

    return res;

}

int main(){

    fact_tail_2_wrapper(6);

}
