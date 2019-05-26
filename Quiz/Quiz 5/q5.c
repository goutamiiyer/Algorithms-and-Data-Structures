#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int fact_pr(int N, int res) {

    printf("\n\t fact_pr(N=%d,res=%d)",N,res);

    if (N <= 1) return res;

    res = res * N;

    return fact_pr(N-1, res);

}

  // Wrapper  function (sets parameters).

int fact_pr_wrapper(int N) {

    int res = 1;

    int temp = fact_pr(N, res);

    // T2: What will res be at this point?
    printf("\n\t T2 res: %d", res);

    return temp;

}

 

int main(){

    fact_pr_wrapper(6);

}