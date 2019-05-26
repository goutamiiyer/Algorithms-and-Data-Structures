#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//**Task 1
int increasing(int * A, int N)
{
	int i;
	//for an empty array it returns 1
	//for an array with 1 element it returns 1.
	if (N == 0 || N == 1)
	{
		return 1;
	}

	//returns 1 if the elements in the array are in increasing order and 0 otherwise.
	//if all the array elements are equal it should return 1.

	for(i = N-1; i > 0; i--)
	{
		if(A[i] >= A[i-1])
		{
			increasing(A,i);
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
//**End of Task 1

//**Task 2
int min_rec_1(int* A, int N, int* base_ct, int* rec_ct, int* max_depth)
{
	int temp;

	if (N==1)
	{
		*base_ct = *base_ct + 1;
		*max_depth = *max_depth + 1;
		return A[0];
	}
	*max_depth = *max_depth + 1;
	temp = min_rec_1(A,N-1,base_ct,rec_ct,max_depth);
	*rec_ct = *rec_ct + 1;

	if (temp < A[N-1])
	{
		return temp;
	}
	else 
	{
		return A[N-1];	
	}
}

int min_rec_2(int* A, int N, int* base_ct, int* rec_ct, int* max_depth)
{	
	if (N==1)
	{
		*base_ct = *base_ct + 1;
		return A[0];	
	}
	if (min_rec_2(A,N-1,base_ct, rec_ct,max_depth) < A[N-1])
	{
		*rec_ct = *rec_ct + 1;
		return min_rec_2(A,N-1,base_ct, rec_ct,max_depth);
	}
	else
	{
		*rec_ct = *rec_ct + 1;
		return A[N-1];	
	}
}

int min_rec_tail(int* A, int N, int* base_ct, int* rec_ct, int* max_depth, int min)
{
	*rec_ct += 1;
	if(N == 1)
	{
		*base_ct = *base_ct + 1;
		return A[0];
	}
	N -= 1;
	if(A[0] > A[N]) 
	{
		min = min_rec_tail(A+1, N, base_ct, rec_ct, max_depth, min);
	}
	else
	{
		min = min_rec_tail(A, N, base_ct, rec_ct, max_depth, min);
	}
	return min;
}

int min_rec_wrapper(int* A, int N, int* base_ct, int* rec_ct, int* max_depth)
{
	if(N == 1)
	{
		*base_ct = *base_ct + 1;
		return A[0];
	}
	int min;
	return min_rec_tail(A,N,base_ct,rec_ct,max_depth,min);
}
//**End of Task 2

//**Task 3
bool isPalindrome(char str[],int s,int e) 
{ 
    // Keep comparing characters while they are same 
    while (s < e) 
    { 
        if (str[s++] != str[e--]) 
        { 
            //printf("%s is Not Palindrome\n", str); 
            return false; 
        } 
    } 
    //printf("%s is palindrome\n", str); 
    return true;
} 


void palindromicSubstring(char* str, int start, int length, int* currIndexMatrix, int* indexMatrix, int* row, int* col)
{
	int i;
	if(start >= length)
	{
		int iCol;
    for(iCol=0; iCol < length; iCol++) {
			*(indexMatrix+((*row)*length)+iCol) = *(currIndexMatrix+iCol);
		}	
		*row = *row + 1;
		return;
	}
	for(i = start; i < length; i++)
	{
		if(isPalindrome(str,start,i))
		{
			*(currIndexMatrix+*col) = start;
			*col += 1;
			palindromicSubstring(str,i+1,length, currIndexMatrix, indexMatrix, row, col);
			*col -= 1;
			*(currIndexMatrix+*col) = -1;
      //int iCol;
    	//for(iCol=0; iCol < length; iCol++) {
			//	printf("%d,",*(currIndexMatrix+iCol));
			//}	
			//printf(":\n");
		}
	}
}

//**End of Task 3

int main()
{
	int A[100];
	int N1,N2,i;
	//Task 2
	int rec_ct = 0;
	int base_ct = 0;
	int max_depth = 0;
	// Task 3
	char str[100];
	int decomp_ct = 0;
	int row,col;
	int rowSize,colSize;

//**Task 1
	printf("Enter size of array. (Stop with -1.) ");
	scanf("%d", &N1);
	while (N1 != -1)
	{
		printf("Enter array elements separated by spaces: ");
		for(i = 0; i < N1; i++)
		{
			scanf("%d", &A[i]);	
		}
		int task1Result;
		task1Result = increasing(A, N1);
		printf("increasing: %d\n", task1Result);
		printf("Enter size of array. (Stop with -1.) ");
		scanf("%d", &N1);
	}
//**End of Task 1

	printf("\n\n");

//**Task 2
	printf("Enter size of array. (Stop with -1.) ");
	scanf("%d", &N2);
	while(N2 != -1 && N1 == -1)
	{
		printf("Enter array elements separated by spaces: ");
		for(i = 0; i < N2; i++)
		{
			scanf("%d", &A[i]);	
		}
		int rec_1;
		rec_1 = min_rec_1(A,N2,&base_ct,&rec_ct,&max_depth);
		printf("\nsmallest_1:	smallest = %d, base_ct = %d, rec_ct = %d,	max_depth = %d\n", rec_1, base_ct, rec_ct, max_depth);
		base_ct = 0; rec_ct = 0; max_depth = 0;
		int rec_2;
		rec_2 = min_rec_2(A,N2,&base_ct,&rec_ct,&max_depth);
		printf("smallest_2:	smallest = %d, base_ct = %d, rec_ct = %d,	max_depth = %d\n", rec_2, base_ct, rec_ct, max_depth);
		base_ct = 0; rec_ct = 0; max_depth = 0;
		int rec_3;
		rec_3 = min_rec_wrapper(A,N2, &base_ct, &rec_ct,&max_depth);
		printf("smallest_tail:	smallest = %d, base_ct = %d, rec_ct = %d,	max_depth = %d\n", rec_3, base_ct, rec_ct, max_depth);
		base_ct = 0; rec_ct = 0; max_depth = 0;

		printf("Enter size of array. (Stop with -1.) ");
		scanf("%d", &N2);
	}
//**End of Task 2

	printf("\n\n");

//**Task 3
	printf("Enter strings. Stop with -1.");
	scanf("%s",str);

	while( N1 == -1 && N2 == -1 && (strcmp(str,"-1") != 0))
	{
		colSize = strlen(str);
		int outMatrixIndex[5][colSize];
		for(row = 0; row < 5; row++)
		{
			for(col = 0; col < colSize; col++) {
				outMatrixIndex[row][col] = -1;
			}
		}
	  int currMatrixIndex[colSize];
		for(col = 0; col < colSize; col++) {
			currMatrixIndex[col] = -1;
		}
		int masterRow = 0;
    int masterCol = 0;
		palindromicSubstring(str, 0, colSize, currMatrixIndex, outMatrixIndex, &masterRow, &masterCol);
		//Iterate over the palindrome set and print every row
		//printf("deepak\n");
		for(row = 0; row < 5; row++) 
		{
			for(col = 0; col < colSize; col++)
			{
				//printf("%d,", outMatrixIndex[row][col]);
				if(outMatrixIndex[row][col] != -1) {
					if(col == colSize-1) {
							int lc;
							for(lc = outMatrixIndex[row][col]; lc < colSize; lc++) {
								printf("%c",str[lc]);
							} 
					} else {
						if(outMatrixIndex[row][col+1] == -1) {
							int lc;
							for(lc = outMatrixIndex[row][col]; lc < colSize; lc++) {
								printf("%c",str[lc]);
							} 
						} else {
							int lc;
							for(lc = outMatrixIndex[row][col]; lc < outMatrixIndex[row][col+1]; lc++) {
								printf("%c",str[lc]);
							} 
							printf(",");
						}
					}
				}
			}
			if(outMatrixIndex[row][0] != -1) {
				printf("\n");	
			}
		}
		printf("Enter strings. Stop with -1. \n");
		scanf("%s", str);
	}
}
