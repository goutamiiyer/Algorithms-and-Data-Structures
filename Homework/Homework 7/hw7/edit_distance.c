/*
Name 	: Goutami Padmanabhan 
UTA ID 	: 1001669338
*/
#include <stdio.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int main(){
	char str1[101];
	char str2[101];

	printf("Enter two words separated by a space (e.g.: cat someone).\n");
	printf(" Stop with: -1 -1\n\n");
	while(1) {
		scanf("%s %s", str1, str2);
		printf(" first: %s\n",str1);
		printf("second: %s\n\n",str2);
		if((strcmp(str1,"-1") == 0) && (strcmp(str2,"-1") == 0)){
			printf("=========================================================================================\n\n");
			break;
		}

		int editDistance[101][101];

		/*Computing the distance matrix*/
		int row = 0; int col = 0;
		for(row = 0; row <= strlen(str1); row++) {
			for(col = 0; col <= strlen(str2); col++) {
				if(row == 0) {
					editDistance[row][col] = col;
				} else if (col == 0) {
					editDistance[row][col] = row;
				} else {
					if(str1[row-1] == str2[col-1]) {
						editDistance[row][col] = editDistance[row-1][col-1];
					} else {
						editDistance[row][col] = MIN(MIN(editDistance[row-1][col-1],editDistance[row][col-1]),
																					editDistance[row-1][col]) + 1;
					}
				}
			}
		}

		/* printing the distance matrix */
		int dash =0;
		for(dash = 0; dash < 4*(strlen(str2)+2); dash++){
			printf("-");
		}
		printf("\n");
		for(row = 0; row <= strlen(str1)+1; row++) {
			for(col = 0; col <= strlen(str2)+1; col++) {
				if((row==0 && col==0) || (row==0 && col==1) || (row==1 && col==0)) {
					printf ("   |");
				} else {
					if(row == 0) {
						printf("  %c|",str2[col-2]);
					} else if (col == 0) {
						printf("  %c|",str1[row-2]);
					} else {
						if(editDistance[row-1][col-1] < 10) {
							printf("  ");
						} else if (editDistance[row-1][col-1] < 100) {
							printf(" ");
						}
						printf("%d|",editDistance[row-1][col-1]);
					}
				}
			}
			printf("\n");
			int dash =0;
			for(dash = 0; dash < 4*(strlen(str2)+2); dash++){
				printf("-");
			}
			printf("\n");
		}
		printf("\n");
		printf("edit distance: %d\n\n", editDistance[strlen(str1)][strlen(str2)]);
		printf("=========================================================================================\n\n");
	}
	return 0;
}
