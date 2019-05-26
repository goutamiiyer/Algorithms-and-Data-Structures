#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	rand_N();
}

int rand_N()
{
	int i,j,k,l,N,S;
	int start_value_N=0;
	int end_value_N=0;
	
	printf("Start Value:");
	scanf("%d",&start_value_N);
	
	printf("End value:");
	scanf("%d",&end_value_N);
	
	printf("How many random values do you want? Value of N\n");
	printf("N:");
	scanf("%d", &N);
	printf("S:");
	scanf("%d", &S);
	int array_N[N];
	int array_S[S];
	
	srand(time(0));
	
	for(i=0;i<N;i++)
	{
//		printf("%d\n", rand() %(end_value));
		array_N[i]=(rand() %(end_value_N));
		printf("%d\n", array_N[i]);
	}
	for(j=0;j<S;j++)
	{
//		printf("%d\n", rand() %(end_value));
		array_S[j]=(rand() %(end_value_N));
		printf("%d\n", array_S[j]);
	}
	
	printf("Array N is \n");
	for(k=0; k<N; k++) {
		printf("%d ", array_N[k]);
	}
	printf("\n");
	printf("Array S is \n");
	for (l = 0; l < S; l++) {
		printf("%d ", array_S[l]);
	}
	return 0;
}
