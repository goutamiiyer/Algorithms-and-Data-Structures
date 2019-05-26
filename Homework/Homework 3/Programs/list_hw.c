/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

struct node_struct {
    Item item;
    link next;
};

struct list_struct {
    link first;
    int length;
};


/* Builds and returns a list with integers read from standard input.
 * Note that it assumes the Item is int.
 * Notice that all the list access is done through it's interface (functions).
 */ 
list buildListOfInts() {
   list the_list = newList();

   link current_link = NULL;
   while(1)
   {
      Item number;
      printf("please enter an integer: ");     
      int items_read = scanf("%d", &number);
      if (items_read != 1)
      {
         break;
      }
     
      /* allocate memory for the next link */
      link next_item = newLink(number, NULL);
      insertLink(the_list, current_link, next_item);
      current_link = next_item;
   }   
   return the_list;
}


list arrayToList(int arr[], int sz)  {
	int i; 		
	link p, new_p;
	list A = newList();
	
	p = newLink(arr[0], NULL);
	insertLink(A, NULL, p);

	for (i = 1; i < sz; i++)
	{
		new_p = newLink(arr[i], NULL);
		insertLink(A, p, new_p);
		p = new_p;
	}
	
	return A;
}




// ------------- link functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
link newLink(Item value, link next_in) {
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link) {
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link) {
    if (the_link != NULL) {
        return the_link->item;
    } else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1; // NOTE: This line can be improved.
    }
}

link getLinkNext(link the_link) {
    if (the_link != NULL) {
        return the_link->next;
    } else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value) {
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next) {
    if (the_link != NULL) {
        the_link->next = next;
    }
}

/*    --------  LIST functions    */

int listIsNULL(list the_list) {
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }
    else {
        return 0;
    }
}

/* Creates and returns an empty list. */
list newList() {
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }

        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return NULL;
    }

    return the_list->first;
}

int getLength(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return -1;
    }

    return the_list->length;
}

/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */
void setEmpty(list the_list) {
    the_list->first = NULL;
    the_list->length = 0;
}

/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link) {
    if (listIsNULL(my_list) == 1) {
        return;
    }

    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    } else {
        new_link->next = previous->next;
        previous->next = new_link;
    }

    my_list->length += 1;
}

/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link) {
    setLinkNext(new_link, getFirst(my_list)); // replaces: new_link->next = my_list->first;
    my_list->first = new_link;
    my_list->length += 1;
}

/* Removes from the list and returns the link coming AFTER link x. 
 * This function DOES NOT remove link x itself. 
 */
link removeNext(list my_list, link x) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    } else {
        temp = x->next;
        x->next = x->next->next; // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
It does not free the memory for that node. */
link removeFirst(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void printList(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}

void printListHoriz(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%5d    ", curr->item);
        i++;
    }
    printf("\n");
}

void printListHorizPointer(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\nList items:    ", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%-11d  ", curr->item);
        i++;
    }
    printf("\n");
    printf("List pointers: ");
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
    printf("\n");
}

int computeLength(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return -1;
    }

    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

/*----------------------------------------------------------------
 New functions.
 Finish their implementation below. 
 If you need to use helper functions you can define them and use them in this file.
 ***You should not change the behavior of any of the functions defined above. 
 Instead, write a new function with the behavior that you want.***
 */

void deleteOccurrences(list A, Item V) {
    if(A == NULL || A->length == 0)
    {
        return;
    }
    // 1. For each link of A - linkA
    link linkA = A->first;
    link prevLinkA = NULL;
    while(linkA != NULL){
    //      1a. Compare linkA->item with V
        if(linkA->item == V)
        {
    //      1b. If equal, remove linkA
            prevLinkA->next = linkA->next;
            // linkA->next = NULL;
            destroyLink(linkA);
            A->length--;            
            linkA = prevLinkA->next;
        } else {
            prevLinkA = linkA;
            linkA = linkA->next;
        }
    }
    return;
}

list sublist(list A, list pos_list) {
    if(A == NULL || A->length == 0)
    {
        return NULL;
    }
    if(pos_list == NULL || pos_list->length == 0)
    {
        return NULL;
    }
    
    // 1. start a list which is empty -- resultList
    list resultList = newList();
    // 2. for all elements in pos_list 
    link currPosLink = pos_list->first;
    link prevResultLink = NULL;
    int ind;
    for (ind = 0; ind < pos_list->length; ind++){
    //    2a. get value of the element -- pos
        Item pos = currPosLink->item;
        currPosLink = currPosLink->next;
    //    2b. traverse list A for pos positions
        link currALink = A->first;
        int aind;

        if(pos < 0 || pos > A->length)
        {
            return NULL;
        }

        for(aind=0; aind < pos; aind++) {
            currALink = currALink->next;
        }
    //    2c. get value at position pos -- newVal
        Item newVal = currALink->item;
    //    2d. create a new link -- resultLink with item = newVal
        link resultLink = newLink(newVal,NULL);
    //    2e. insert newLink at the end of resultList
        insertLink(resultList, prevResultLink, resultLink);
        prevResultLink = resultLink;
    }
    // 3. Return resultList
    return resultList;
}

void moveAllMaxAtEnd(list A) {
    if(A == NULL || A->length == 0 || A->length == 1)
    {
        return;
    }
    // 1. maxElement is the firstElement
    Item maxElement = A->first->item;
    // 2. for every element in list A
    link currentLink = A->first->next;
    link lastLink = A->first;
    int i;
    for(i =1; i < A->length; i++)
    {
        lastLink = currentLink;
    //  2a. Compare maxElement with nextElement
    //  2b. If nextElement > maxElement
        if(currentLink->item > maxElement){
    //  2c. maxElement is nextElement
            maxElement = currentLink->item;
        }
        currentLink = currentLink->next;        
    }
    // 3. for every element in list A
    currentLink = A->first;
    link prevLink = NULL;
    for(i = 0; i < A->length; i++){
        //  3a. Check every value is equal to maxElement
        if(currentLink->item == maxElement && currentLink != lastLink) {
            //  3b. If equal, move that elemnt to end
            prevLink->next = currentLink->next;
            currentLink->next = NULL;
            lastLink->next = currentLink;
            lastLink = currentLink;
            currentLink = prevLink->next;
        } else {
            prevLink = currentLink;
            currentLink = currentLink->next;
        }
    }
    return;
}


// swaps the first and the third nodes
void swapFirstThird(list A) {
    if(A == NULL || A->length == 0 || A->length == 1)
    {
        return;
    }
    // 1. If length = 2,
    if(A->length == 2)
    {
        link firstElement = A->first;
        link secondElement = firstElement->next;
    //  1a. 2nd element-> next = first element
        secondElement->next = firstElement;
    //  1b. 1st element->next = NULL
        firstElement->next = NULL;
    //  1c. A->first = 2nd element
        A->first = secondElement;
    } else if(A->length > 2){
        // 1. Obtain first element
        link firstElement = A->first;
        // Obtain second Element
        link secondElement = firstElement->next;
        // Obtain third element
        link thirdElement = secondElement->next;
        //Obtain fourth element
        link fourthElement = thirdElement->next;
        // first element -> next = fourth element
        firstElement->next = fourthElement;
        secondElement->next = firstElement;
        thirdElement->next = secondElement;
        A->first = thirdElement;
    }
    return;
}

// Set-up and call your testing functions from this function.

int run_student_tests() {
    printf("\n Running function run_student_test.\n");
    printf("\n\n--------------------------------------\n");
    printf("Before deleting a null list\n");
    deleteOccurrences(NULL,15);
    printf("After deleting a null list\n");
    printf("Before deleting an occurance from empty list\n");
    deleteOccurrences(newList(),12);
    printf("After deleting an occurance from empty list\n");
    int deleteOcc[] = {12, 35, 20};
    list deleteOccur = arrayToList(deleteOcc, 3);
    deleteOccurrences(deleteOccur, 7);
    printf("List after not removing the non occuring value:");
    printListHoriz(deleteOccur);
    destroyList(deleteOccur);

    printf("Before calling moveAllMaxAtEnd with NULL\n");
    moveAllMaxAtEnd(NULL);
    printf("After calling moveAllMaxAtEnd with NULL\n");
    printf("Before calling moveAllMaxAtEnd with empty list\n");
    moveAllMaxAtEnd(newList());
    printf("After calling moveAllMaxAtEnd with empty list\n");
    int maxEle[] = {3};
    list maxElem = arrayToList(maxEle, 1);
    moveAllMaxAtEnd(maxElem);
    printf("Testing moveAllMaxAtEnd with one element\n");
    printListHoriz(maxElem);
    destroyList(maxElem);

    printf("Before calling swapFirstThird with NULL\n");
    swapFirstThird(NULL);
    printf("After calling swapFirstThird with NULL\n");
    printf("Before calling swapFirstThird with empty list\n");
    swapFirstThird(newList());
    printf("After calling swapFirstThird with empty list\n");

    int swapTwo[] = {7, 8};
    list swapTwoList = arrayToList(swapTwo, 2);
    swapFirstThird(swapTwoList);
    printf("List after swapping 2 elements:");
    printListHoriz(swapTwoList);
    destroyList(swapTwoList);

    printf("Before calling sublist with null lists\n");
    list out_list = sublist(NULL, NULL);
    printf("Out list should be null\n");
    printf("Before calling sublist with empty lists\n");
    list out_list1 = sublist(newList(), newList());
    printf("Out list should be null\n");
    int A[] = {15,100,7,5,100,30,8};
    list A1 = arrayToList(A, 7);
    int arr_pos[] = {3, 0, 6, 4};
    list pos_list = arrayToList(arr_pos, 4);
    list res = sublist(A1, pos_list);
    printf("List with results:");
    printListHoriz(res);
    destroyList(pos_list);
    destroyList(A1);
    destroyList(res);
    printf("Done with sublist\n");
    return;
}

