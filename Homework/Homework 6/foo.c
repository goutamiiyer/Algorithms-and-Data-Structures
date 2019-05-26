/*
Name 	: Goutami Padmanabhan 
UTA ID 	: 1001669338
*/
#include <stdio.h>

int main() 
{
	int N1;
	printf("Enter N");
	scanf("%d", &N1);
	while(N1 != -1) 
	{
		printf("Result of iterative function for N=%d is %d\n", N1, foo_iterative(N1));
		printf("Result of memoized function for N=%d is %d\n", N1, foo_wrapper(N1));
		scanf("%d", &N1);
	}
}

int foo_iterative(int N)
{
    int i = 0;
    int res[N+1];
    for (i = 0; i <= N; i++) 
    {
        if(i <= 1) 
        {
            res[i] = 5;
        } 
        else 
        {
	        int res1 = 3*res[i/2];
	        int res2 = res[i-1];
        	res[i] = res1 >= res2 ? res1 : res2;
        }
    }
    return res[N];
}

int foo_wrapper(int N) 
{
	int res1[N];
	int i;
	for(i = 0; i <= N; i++) 
	{
		res1[i] = 0;
	}
    return foo_memoized(N, res1, 0);
}

int foo_memoized(int N, int res[], int depth) 
{
	int i;
	for(i = 0; i < depth; i++)
	{
		printf("  ");
	}
	printf("N=%d\n", N);
	if(res[N] == 0) {
    	if(N <= 1)
    	{
        	res[N] = 5;
    	} else {
        	int res1 = 3 * foo_memoized(N/2, res, depth + 1);
        	int res2 = foo_memoized(N-1, res, depth + 1);
		    res[N] = (res1 >= res2) ? res1 : res2;
    	}
	} 
	return res[N];
}




