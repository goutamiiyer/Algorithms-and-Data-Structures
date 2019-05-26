#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void runtime_rec(int N, char * str){
	if (N==0) {
		printf("%s\n", str);
		return;
	}

	str[N-1] = 'L';
	runtime_rec(N-1, str);
	str[N-1] = 'R';
	runtime_rec(N-1, str);
}

int main(int argc, char** argv) {
	int N = 0;
	char ch;
	char str[100];
	struct timeval  tv1, tv2;
	printf("run for: N = ");
	scanf("%d", &N);
	str[N] = '\0'; //to use it as a string of length N.
	printf("runtime_rec(%d)\n", N);
	gettimeofday(&tv1, NULL);
	runtime_rec(N, str);
	gettimeofday(&tv2, NULL);
	printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
