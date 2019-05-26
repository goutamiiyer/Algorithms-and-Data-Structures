#include<stdio.h>
#include <stdlib.h>

typedef struct Record Record;

struct Record {
  int value;
  Record* nextRecord;
};

typedef struct {
  int size;
  Record* firstRecord;
} LinkedList;

/*
firstRecord = ptr12

12 99ptr, 99 37ptr, 37 NULL

12 99ptr, 99 37ptr, 37 35ptr, 35 NULL

----
firstRecord = NULL
*/

void printLinkedList(LinkedList* ll) {
  //printf("%d size\n",ll->size);
  Record* currElementInLl = ll->firstRecord;
  if(currElementInLl == NULL) {
    printf("No elements in LinkedList\n");
  } else {
    while(currElementInLl) {
      printf("%d\t",currElementInLl->value);
      currElementInLl = currElementInLl->nextRecord;
    }
  }
  printf("\n");
}

void addElementToLinkedList(LinkedList* ll, Record* newRecord) {
  Record* currElementInLl = ll->firstRecord;

  int elementIndex = 0;
  if(currElementInLl == NULL) {
    // No elements in linked list, add newRecord as the first element
    ll->firstRecord = newRecord;
  } else {
    elementIndex++;
    while(currElementInLl->nextRecord != NULL) {
      currElementInLl = currElementInLl->nextRecord;
      elementIndex++;
    }
    currElementInLl->nextRecord = newRecord;
  }
  printf("Added %d to LinkedList at %d\n",newRecord->value,elementIndex);
  ll->size++;
}

void deleteElementInLinkedList(LinkedList* ll, int valueToDel) {
  Record* currElementInLl = ll->firstRecord;

  if(currElementInLl->value == valueToDel) {
    ll->firstRecord = currElementInLl->nextRecord;
    //free(currElementInLl->nextRecord);
  } else {
    while(currElementInLl != NULL && currElementInLl->nextRecord != NULL) {
      if(currElementInLl->nextRecord->value == valueToDel) {
        Record* newNextRecord = currElementInLl->nextRecord->nextRecord;
        //free(currElementInLl->nextRecord->nextRecord);
        currElementInLl->nextRecord = newNextRecord;
      } else {
        currElementInLl = currElementInLl->nextRecord;
      }
    }
  }
}

int main() {

  LinkedList ll;
  ll.size = 0;
  ll.firstRecord = NULL;

  // Add a record to the LinkedList
  Record* newRecord1 = malloc(sizeof(Record));
  newRecord1->value = 35;
  newRecord1->nextRecord = NULL;
  addElementToLinkedList(&ll,newRecord1);
  Record* newRecord2 = malloc(sizeof(Record));
  newRecord2->value = 40;
  newRecord2->nextRecord = NULL;
  addElementToLinkedList(&ll,newRecord2);
  Record* newRecord3 = malloc(sizeof(Record));
  newRecord3->value = 50;
  newRecord3->nextRecord = NULL;
  addElementToLinkedList(&ll,newRecord3);
  printLinkedList(&ll);
  deleteElementInLinkedList(&ll,40);
  printLinkedList(&ll);
  Record* newRecord4 = malloc(sizeof(Record));
  newRecord4->value = 60;
  newRecord4->nextRecord = NULL;
  addElementToLinkedList(&ll,newRecord4);
  printLinkedList(&ll);

  return 0;
}
