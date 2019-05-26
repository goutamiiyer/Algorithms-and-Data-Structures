/*
Name 	: Goutami Padmanabhan
UTA ID 	: 1001669338
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 256
#define TABLESIZE 29881

typedef struct {
  int valid;
  char *key;
  char *val;
} Hashentry;

unsigned long hash(const char *s, int probe) {
  unsigned long h;
  unsigned const char *us;
  us = (unsigned const char *)s;
  h = 0;
  while (*us != '\0') {
    h = (h * BASE + *us) % TABLESIZE;
    us++;
  }
  h = (h + probe + (probe * probe)) % TABLESIZE;
  return h;
}

char *search(char *key, int *numProbes, Hashentry *ht) {
  // printf("key: -%s-\n", key);
  unsigned long hashIndex;
  char *val = NULL;
  int done = 0;
  int probe = 0;
  while (done == 0) {
    // printf("probe: %d\n", probe);
    hashIndex = hash(key, probe);
    if ((*(ht + hashIndex)).valid == 1) {
      if (strcmp((*(ht + hashIndex)).key, key) == 0) {
        val = (*(ht + hashIndex)).val;
        *numProbes = probe + 1;
        done = 1;
        // printf("search hit.. %s\n", val);
      } else {
        probe++;
      }
    } else {
      probe++;
    }
    if (probe > 10) {
      break;
    }
  }
  return val;
}

int delete (char *key, int *numProbes, Hashentry *ht) {
  int success = -1;
  *numProbes = -1;
  char *exval = search(key, numProbes, ht);
  if (exval != NULL) {
    unsigned long hashIndex = hash(key, *numProbes - 1);
    (*(ht + hashIndex)).valid = 0;
    (*(ht + hashIndex)).val = NULL;
    (*(ht + hashIndex)).key = NULL;
    success = 1;
  }
  return success;
}

void insert(char *key, char *val, int *numProbes, Hashentry *ht) {
  int numProbes1 = -1;
  char *exval = search(key, &numProbes1, ht);
  unsigned long hashIndex;
  if (exval == NULL) {
    int done = 0;
    int probe = 0;
    while (done == 0) {
      hashIndex = hash(key, probe);
      if ((*(ht + hashIndex)).valid == 0) {
        (*(ht + hashIndex)).valid = 1;
        (*(ht + hashIndex)).key = key;
        (*(ht + hashIndex)).val = val;
        *numProbes = probe + 1;
        done = 1;
        // printf("Inserting -%s- at index %lu (probe=%d)\n",
        //       (*(ht + hashIndex)).key, hashIndex, probe);
      } else {
        probe++;
      }
      if (probe > TABLESIZE) {
        hashIndex = hash(key, 0);
        (*(ht + hashIndex)).valid = 1;
        (*(ht + hashIndex)).key = key;
        (*(ht + hashIndex)).val = val;
        *numProbes = probe + 1;
        break;
      }
    }
  } else {
    hashIndex = hash(key, numProbes1 - 1);
    char *oldVal = (*(ht + hashIndex)).val;
    (*(ht + hashIndex)).val =
        (char *)malloc((strlen(oldVal) + strlen(val) + 1) * sizeof(char));
    strcat((*(ht + hashIndex)).val, oldVal);
    strcat((*(ht + hashIndex)).val, ";");
    strcat((*(ht + hashIndex)).val, val);
    *numProbes = numProbes1;
  }
}

int main() {

  Hashentry hashtable[TABLESIZE];
  int i;
  for (i = 0; i < TABLESIZE; i++) {
    hashtable[i].valid = 0;
    hashtable[i].key = NULL;
    hashtable[i].val = NULL;
  }

  printf("\nEnter the filename with the dictionary data (include the extension "
         "e.g. Spanish.txt):");
  unsigned long bufsize = 100;
  char *buffer = (char *)malloc(bufsize * sizeof(char));
  getline(&buffer, &bufsize, stdin);
  // printf("%s", buffer);
  printf("\n");
  // fflush(stdout);
  char *fileName = strndup(buffer, strlen(buffer) - 1);
  // printf("%s", fileName);
  // fflush(stdout);
  FILE *fp;
  char str[256];
  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("Unable to open file.\n");
    exit(1);
  }
  int dictTotalProbes = 0;
  float dictAvgProbes = 0.000000;
  int dictMaxProbes = -1;
  int dictProbesAtLoc[TABLESIZE] = {0};
  int dictInsertOps = 0;
  int dictUnhased = 0;

  while (fgets(str, sizeof(str), fp)) {
    char *pch;
    pch = strchr(str, '\t');
    char *key;
    char *val;
    key = strndup(str, pch - str);
    val = strndup(pch + 1, strlen(str) - 1 - (pch - str + 1));
    // printf("key: %s ", key);
    // printf("val: %s ", val);
    int numProbes;
    insert(key, val, &numProbes, &(hashtable[0]));
    if (numProbes > 0 && numProbes <= TABLESIZE) {
      dictTotalProbes += numProbes;
      dictInsertOps++;
      if (numProbes > dictMaxProbes) {
        dictMaxProbes = numProbes;
      }
      dictProbesAtLoc[numProbes - 1]++;
    } else {
      dictUnhased++;
    }
  }
  dictAvgProbes = ((double)dictTotalProbes) / ((double)dictInsertOps);
  fclose(fp);

  printf("\nHash Table\n");
  printf("  average number of probes:\t\t%.2f\n", dictAvgProbes);
  printf("  max_run of probes:\t\t\t%d\n", dictMaxProbes);
  printf("  total PROBES (for 7477 items) :\t%d\n", dictTotalProbes);
  printf("  items NOT hashed (out of 7477):\t%d\n\n", dictUnhased);

  printf("Probes|Count of keys\n");
  printf("-------------\n");
  
  int k;
  for (k = 0; k < TABLESIZE; k++) {
    if (dictProbesAtLoc[k] > 0) {
      printf(" %d| %d\n", dictProbesAtLoc[k], k);
      printf("-------------\n");
      // printf("Keys with %d probes: %d\n", k, dictProbesAtLoc[k]);
    }
  }

  printf("\nEnter words to look-up. Enter -1 to stop.\n");
  int totUserProbes = 0;
  int totUserOps = 0;
  double avgUserProbes = 0;
  while (1) {
    // printf("Type command: ");
    // unsigned long bufsize = 100;
    // char *buffer = (char *)malloc(bufsize * sizeof(char));
    getline(&buffer, &bufsize, stdin);
    // printf("%s", buffer);
    char *pch;
    pch = strchr(buffer, ' ');
    char *operation;
    if (pch == NULL) {
      operation = strndup(buffer, strlen(buffer) - 1);
    } else {
      operation = strndup(buffer, pch - buffer);
    }
    if (strcmp(operation, "q") == 0) {
      avgUserProbes = ((double)totUserProbes) / ((double)totUserOps);
      printf("\nAverage probes per operation:\t%.2f\n\n", avgUserProbes);
      // printf("Avg. probes for user operations: %f\n", avgUserProbes);
      break;
    } else if (strcmp(operation, "s") == 0) {
      char *key = strndup(pch + 1, strlen(buffer) - (pch - buffer + 2));
      int numProbes = -1;
      printf("\nREAD op:s query:%s\n", key);
      char *val = search(key, &numProbes, &(hashtable[0]));
      // printf("\t%d probes\n", totUserProbes);
      if (val == NULL) {
        printf("\tNOT found\n");
      } else {
        printf("\t%d probes\n", numProbes);
        printf("\tTranslation: %s\n", val);
        totUserProbes += numProbes;
        totUserOps++;
      }
    } else if (strcmp(operation, "d") == 0) {
      char *key = strndup(pch + 1, strlen(buffer) - (pch - buffer + 2));
      int numProbes;
      int success = delete (key, &numProbes, &(hashtable[0]));
      if (success < 0) {
        printf("\tNOT found\n");
      } else {
        printf("\tItem was deleted.\n");
        printf("\t%d probes\n", numProbes);
        totUserProbes += numProbes;
        totUserOps++;
      }
    } else if (strcmp(operation, "i") == 0) {
      char *pch1 = strchr(pch + 1, ' ');
      char *key = strndup(pch + 1, pch1 - pch - 1);
      char *val = strndup(pch1 + 1, strlen(buffer) - (pch1 - buffer + 2));
      int numProbes;
      insert(key, val, &numProbes, &(hashtable[0]));
      printf("\t%d probes\n", numProbes);
      totUserProbes += numProbes;
      totUserOps++;
    } else {
      printf("Unknown operation\n");
    }
  }

  /*
scanf("%s %s", operation, word);
if (strcmp(operation, "i") == 0) {
scanf("%s", translation);
}

printf("\nHash Table\n");
printf("  average number of probes:\t%.2f\n", averageProbes);
printf("  max_run of probes:\t\t%d\n", max_run);
printf("  total PROBES (for %d items) :\t%d\n", totalItems, totalProbes);
printf("  items NOT hashed (out of %d):\t%d\n\n", totalItems, itemsNotHashed);

printf("Probes|Count of keys\n");
printf("-------------\n");
printf("     %d|     %d\n", probes, countOfKeys);
printf("-------------\n");

printf("\nEnter words to look-up. Enter -1 to stop.\n");

while (1) {
if (strcmp(operation, "q") == 0) {
break;
}

printf("\nREAD op:%s query:%s\n", operation, word);
printf("\t%d probes\n", totalProbes);
if (strcmp(operation, "s") == 0) {
printf("\tTranslation: %s\n", translation);
}
if (strcmp(operation, "d") == 0) {
printf("\tItem was deleted.\n");
}
scanf("%s %s", operation, word);
if (strcmp(operation, "i") == 0) {
scanf("%s", translation);
}
}

printf("\nAverage probes per operation:\t%.2f\n\n", avgProbesPerOperation);
  */
  return 0;
}
