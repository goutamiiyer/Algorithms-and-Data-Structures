/*
Name 	: Goutami Padmanabhan 
UTA ID 	: 1001669338
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
	char *name1[1000];
	char *name2[1000];
	int N = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int row = 0;
	int col = 0;
	int numOfConnections = 0;
	int rowIndex = 0;
	int colIndex = 0;
	int numOfGroups = 0;
	unsigned long buffersize = 100;
	char* buffer = (char*) malloc(buffersize*sizeof(char));

	printf("Enter number of vertices, N:");
	fflush(stdout);
	getline(&buffer,&buffersize,stdin);
	N = atoi(buffer);
	printf("N=%d\n",N);
	fflush(stdout);
	char** nodesNames;
	nodesNames = (char**) malloc(N*sizeof(char*));
	int* relationMatrix;
	relationMatrix = (int*) malloc(N*N*sizeof(int));

	for(row = 0; row < N; row++) {
		for(col = 0; col < N; col++) {
			*(relationMatrix+row*N+col) = 0;
		}
	}

	for(i=0; i<N; i++) {
		printf("Enter name1: ");
		fflush(stdout);
		getline(&buffer,&buffersize,stdin);
		if(strlen(buffer) >= 2) {
			*(buffer+strlen(buffer)-2) = '\0';	
		} else {
			*(buffer) = '\0';
		}
		*(nodesNames+i) = strndup(buffer, strlen(buffer));
	}

	while(1) {
		printf("Enter name1 name2: ");
		getline(&buffer,&buffersize,stdin);
		if(strlen(buffer) >= 2) {
			*(buffer+strlen(buffer)-2) = '\0';	
		} else {
			*(buffer) = '\0';
		}
		char *pch;
    	pch = strchr(buffer, ' ');
		*pch = '\0';
		char* t1  = strndup(buffer, pch-buffer+1);
		char* t2 = strndup(pch+1, strlen(buffer)-(pch-buffer+1));
	
		if(t1 != NULL && t2 != NULL) {
			if((strcmp(t1,"-1") == 0) && (strcmp(t2,"-1") == 0)) {
				break;
			} else {
				name1[j] = strndup(t1,strlen(t1));
				name2[j] = strndup(t2,strlen(t2));
				j++;
			}
		}
		
	}

	for(numOfConnections = 0; numOfConnections < j; numOfConnections++) {
		rowIndex = 0;
		colIndex = 0;
		for (row = 0; row < N; row++) {
			if(strcmp(name1[numOfConnections], *(nodesNames+row)) == 0) {
				rowIndex = row;
			}
		}
		for (col = 0; col < N; col++) {
			if(strcmp(name2[numOfConnections], *(nodesNames+col)) == 0) {
				colIndex = col;
			}
		}
		*(relationMatrix+N*rowIndex+colIndex) = 1;
		*(relationMatrix+N*colIndex+rowIndex) = 1;
	}
	
	printf("\nGRAPH: \n");
	printf("N = %d\n", N);
	for(i = 0; i < N; i++) {
		printf("%d-%s\n", i, *(nodesNames+i));
		fflush(stdout);
	}

	for(row = 0; row < N; row++) {
		for(col = 0; col < N; col++) {
			printf("%d ", *(relationMatrix+N*row+col));
		}
		printf("\n");
	}

	int* nodesToVisit;
	nodesToVisit = (int*) malloc(N*sizeof(int));
	for(i=0; i < N; i++) {
		*(nodesToVisit+i) = 0;
	}

	int* groupIdNode;
	groupIdNode = (int*) malloc(N*sizeof(int));

	int currGroupId = 0;
	for(i=0; i < N; i++) {
		if(*(nodesToVisit+i) == 0) {
			*(nodesToVisit+i) = 1;
			*(groupIdNode+i) = currGroupId;
			int numVisitedThisLoop = 0;
			do {
				numVisitedThisLoop = 0;
				for(j=0; j < N; j++) {
					if(*(nodesToVisit+j) == 1) {
						for(k=0; k < N; k++) {
							if(*(relationMatrix+j*N+k) == 1) {
								if(*(nodesToVisit+k) == 0) {
									*(nodesToVisit+k) = 1;
									*(groupIdNode+k) = currGroupId;
								}
							}
						}
						*(nodesToVisit+j) = 2;
						numVisitedThisLoop++;
					}	
				}
			} while(numVisitedThisLoop > 0);
			currGroupId++;
		}
	}
	printf("Number of groups: %d\n", currGroupId);

	int g;
	for(g=0; g < currGroupId; g++) {
		printf("Group: %d\n",g+1);
		for(i = 0; i < N; i++) {
			if(*(groupIdNode+i) == g) {
				printf("%s\n", *(nodesNames+i));
			}
		}
		printf("\n");
	}
	return 0;
}
