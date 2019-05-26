#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main_menu(void);
void writeToFile(char*,int[],int,int[],int,int,int);
void swap(int *, int *);
int binarySearch(int[], int, int, int);
int interpolationSearch(int[], int, int);

int binarySearchLoopcount = 0;
int interpSearchCount = 0;

int main()
{
	int i=0,j=0;
	int N=0;
	int S=0;
	int start_value=0;
	int end_value=0;
	
	int array_N[1000];
	int array_S[1000];
	
	int mode;
	
	char filename[100];
	
	int menu_choice;
	
	char str[1000];
	int line = 0;
	
	char newString[100][100];
	char s_string[100][100];
	int letter,read_letter,word;
	
	int input_number[1000];
	int number;
	int compartor_array[1000];
	int s_number;
	
	int binary_array[1000];
	int interp_array[1000];
	
	int binary_loop_count[1000];
	int interp_loop_count[1000];
	double binary_sum = 0.00, interp_sum = 0.00;
	double binary_avg = 0.00, interp_avg = 0.00;
	
	int arr_ind;
	int val_ind;
	
	rollback:
	menu_choice=main_menu();

	switch(menu_choice)
	{
		case 0:
			printf("Bye\n");
			break;
		case 1:
			printf("Enter: N S start_val end_val filename(with extension): ");
			scanf("%d %d %d %d %s",&N,&S,&start_value,&end_value,&filename);
			/*
			**Create random variables for N numbers and S numbers.
			*/
			srand(time(0));
			for(i = 0; i < N;i++)
			{
				array_N[i] = (rand()%(end_value-start_value+1))+start_value;
			}
			
			for(j = 0; j < S; j++)
			{
				array_S[j] = (rand()%(end_value-start_value+1))+start_value;
			}
			/*
			**Write to file.
			*/
			writeToFile(filename, array_N, N, array_S, S, start_value, end_value);
			
			goto rollback;
			break;
		case 2:
			menu2:
			printf("Enter: filename, mode(1-verbose, 2-not verbose): ");
			scanf("%s%d",&filename,&mode);
			/*
			**Check file name and print if file not found.
			*/
			if( access( filename, F_OK ) != -1 ) 
			{
				//do nothing
			} 
			else 
			{
				printf("File could not be opened.\n");
				goto rollback;
			}
			/*
			**Read the file
			*/
			FILE *fr;
			fr = fopen(filename,"r");
			line = 0;
			while(fgets(str,sizeof(str),fr))
			{
				line++;
				if (line == 2)
				{
					break;
				}
			}
			fclose(fr);
			
			/*
			**Separate the numbers as strings in the line.
			*/
			read_letter = 0; word = 0;
			for(letter = 0; letter <= (strlen(str)); letter++)
			{
				if(str[letter] == ' ' || str[letter] == '\0')
				{
					newString[word][read_letter] = '\0';
					word++;
					read_letter = 0;
				}
				else
				{
					newString[word][read_letter] = str[letter];
					read_letter++;
				}
			}
			/*
			**Convert strings to integers.
			*/
			for(number = 0; number < word-1; number++)
			{
				input_number[number] = atoi(newString[number]);
			}
			/*
			**Selection Sort
			*/
			for(i = 0; i < number-1; i++) {
				for(j = i+1; j < number; j++) {
					if(input_number[i] > input_number[j]) {
						swap(&input_number[i], &input_number[j]);
					}
				}
			}

			FILE *filereader;
			filereader = fopen(filename,"r");
			line = 0;
			while(fgets(str,sizeof(str),filereader))
			{
				line++;
				if (line == 3)
				{
					break;
				}
			}
			fclose(filereader);
			
			read_letter = 0; word = 0;
			for(letter = 0; letter <= (strlen(str)); letter++)
			{
				if(str[letter] == ' ' || str[letter] == '\0')
				{
					s_string[word][read_letter] = '\0';
					word++;
					read_letter = 0;
				}
				else
				{
					s_string[word][read_letter] = str[letter];
					read_letter++;
				}
			}
			
			for(s_number = 0; s_number < word - 1; s_number++) {
				compartor_array[s_number] = atoi(s_string[s_number]);
			}
			/*
			**Binary Search.
			*/
			binary_avg = 0.00; binary_sum = 0;
			for(i = 0; i < s_number; i++) {
				binarySearchLoopcount = 0;
				binary_array[i] = binarySearch(input_number, compartor_array[i], 0, number);
				binary_loop_count[i] = binarySearchLoopcount;
				binary_sum = binary_sum + binarySearchLoopcount;
			}
			binary_avg = (double) (binary_sum / s_number);
			/*
			**Interpolation Search
			*/
			interp_avg = 0.00; interp_sum = 0;
			for(i = 0; i < s_number; i++){
				interpSearchCount = 0;
				interp_array[i] = interpolationSearch(input_number, compartor_array[i],number);
				interp_loop_count[i] = interpSearchCount;
				interp_sum = interp_sum + interpSearchCount;
			}
			interp_avg = (double) (interp_sum / s_number);
			
			switch(mode)
			{
				case 1:
					printf("\nsorted array:\n");
					for (arr_ind = 0; arr_ind < number; arr_ind++)
					{
						printf("%d ", input_number[arr_ind]);
					}
					printf("\n|       |       | found at index|  repetitions  |\n");
					printf("|      i|  value| interp| binary| interp| binary|\n");
					for (val_ind = 0; val_ind < s_number; val_ind++)
					{
					printf("|      %d|     %d|     %d|     %d|      %d|     %d|\n",val_ind,compartor_array[val_ind],interp_array[val_ind],binary_array[val_ind],interp_loop_count[val_ind],binary_loop_count[val_ind]);
					}
					printf("|    avg|       |       |       |   %0.2lf|   %0.2lf|\n", interp_avg, binary_avg);
					goto rollback;
					break;
				case 2:
					printf("\n\n");
					printf("|       |       | found at index|  repetitions  |\n");
					printf("|      i|  value| interp| binary| interp| binary|\n");
					printf("|    avg|       |       |       |   %0.2lf|   %0.2lf|\n", interp_avg, binary_avg);
					goto rollback;
					break;
				default:
				printf("Invalid Choice. Please enter either 1 or 2\n");
				goto menu2;
			}
			
			break;
			default:
			printf("Invalid Choice. Please enter either 0, 1 or 2\n");
			goto rollback;
	}	
	return 0;
}
/**
 * This function is for displaying the Main Menu and returning the user's choice.
 */
int main_menu()
{
	int main_menu_choice;
	printf("\n0-exit\n");
	printf("1-create and save random data for search.\n");
	printf("2-load data from file, sort array and run searches.\n");
	printf("Enter your choice: ");
	scanf("%d",&main_menu_choice);
	return main_menu_choice;
}
/**
 * This function is to create a new file or append it for Menu 1. 
 * Input parameters are the filename, array with N values, N value, array with S values, S value, start value and end value.
 */
void writeToFile(char* filen,int array_Nrand[],int N_num,int array_Srand[],int S_num,int start_val,int end_val)
{
	int ind = 0, S_ind = 0;
	FILE *fp, *fp1, *fp2;
	
	fp=fopen(filen,"w+");
	fprintf(fp,"%d %d %d %d\n", N_num, S_num, start_val, end_val);
	fclose(fp);
	
	fp = fopen(filen,"a");
	for(ind = 0; ind < N_num; ind++)
	{
		fprintf(fp, "%d ", array_Nrand[ind]);
	}
	fprintf(fp,"\n");
	
	for(S_ind = 0;S_ind < S_num; S_ind++)
	{
		fprintf(fp,"%d ", array_Srand[S_ind]);
	}
	fprintf(fp,"\n");
	fclose(fp);
}

/**
 * This function is for swapping numbers in Selection sort 
 * Input parameters are addresses of two numbers to be swapped
 */

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * This function is for binary search 
 * Input parameters are the sorted array, the search value, the start value and N value
 */

int binarySearch(int arr[], int value, int left, int right) 
{ 
	binarySearchLoopcount += 1;
    if (right >= left) 
    { 
        int middle = left + (right - left)/2; 
  
        if (arr[middle] == value)   
            return middle; 
  
        if (arr[middle] > value)  
            return binarySearch(arr, value, left, middle-1); 
  
        return binarySearch(arr, value, middle+1, right);
    } 
    return -1; 
} 

/**
 * This function is for interpolation search 
 * Input parameters are the sorted array, the search value and size of the array
 */
int interpolationSearch(int interp_arr[], int search_value, int n)
{
    int low = 0, hi = (n - 1);
    while (low <= hi && search_value >= interp_arr[low] && search_value <= interp_arr[hi])
    {
		interpSearchCount += 1;
        int m = low + (((double)(hi-low) /
              (interp_arr[hi]-interp_arr[low]))*(search_value - interp_arr[low]));

        if (interp_arr[m] == search_value)
            return m;
        else if (interp_arr[m] < search_value)
            low = m + 1;
        else
            hi = m - 1;
    }
    return -1;
}


