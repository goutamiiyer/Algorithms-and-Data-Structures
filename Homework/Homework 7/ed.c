/*
Name 	: Goutami Padmanabhan 
UTA ID 	: 1001669338
*/
#include <stdio.h>
#include <string.h>

int minimum_value(int num1, int num2, int num3){
	if(num1 < num2) {
		if(num1 < num3) {
			return num1;
		} else {
			return num3;
		}
	} else {
		if(num2 < num3) {
			return num2;
		} else {
			return num3;
		}
	}
}

int main(){
	char str1[100];
	char str2[100];

	while((strcmp(str1,"-1") != 0) && (strcmp(str2,"-1") != 0)){
		printf("Enter two words separated by a space (e.g.: cat someone).\n");
		printf(" Stop with: -1 -1\n\n");
		scanf("%s %s", str1, str2);
		printf(" first: %s\n",str1);
		printf("second: %s\n\n",str2);

		/*Displays each character of the string str1*/
		int i = 0;
		printf("  |   |");
		for(i = 0; str1[i] != '\0'; i++){
			printf("  %c|", str1[i]);
		}
		printf("\n");

		/*Displays "--------" */
		int dash =0;
		for(dash = 0; dash <= ((4*strlen(str1)) + 6); dash++){
			printf("-");
		}
		printf("\n");

		/*Second Row*/
		printf("  |");
		for(i =0; i <= strlen(str1); i++){
			if(i <= 9){
				printf("  %d|", i);
			}else{
				printf(" %d|", i);
			}
		}
		printf("\n");

		/*Displays "--------" */
		for(dash = 0; dash <= ((4*strlen(str1)) + 6); dash++){
			printf("-");
		}
		printf("\n");

		/*Displays each character of the string str2*/
		int editDistance[100][100];
		int j = 0;
		for(j = 0; str2[j] != '\0'; j++){
			printf(" %c|", str2[j]);

			/*Second column*/
			if(j <= 9){
				printf("  %d|", j+1);
			}else{
				printf(" %d|", j+1);
			}

			/*Remaining rows and columns filled with edit distance*/
			for(i = 0; str1[i] != '\0'; i++){
				if(str1[i] == str2[j]){
					editDistance[i][j] = 0;
				}else{
					editDistance[i][j] = 1;
				}

				if(editDistance[i][j] <= 9){
					printf("  %d|", editDistance[i][j]);
				}else{
					printf(" %d|", editDistance[i][j]);
				}
			}

			printf("\n");

			/*Displays "--------" */
			for(dash = 0; dash <= ((4*strlen(str1)) + 6); dash++){
				printf("-");
			}
			printf("\n");
		}
		printf("\n");
		printf("edit distance: %d\n\n", editDistance);
		printf("=========================================================================================\n\n");
	}
}
