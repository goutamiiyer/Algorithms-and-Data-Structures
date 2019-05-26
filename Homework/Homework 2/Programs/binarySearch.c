#include <stdio.h> 
  
int binarySearch(int arr[], int value, int left, int right) 
{ 
   if (right >= left) 
   { 
        int middle = left + (right - left)/2; 
  
        if (arr[middle] == value)   
            return middle; 
  
        if (arr[middle] > value)  
            return binarySearch(arr, left, middle-1, value); 
  
        return binarySearch(arr, middle+1, right, value); 
   } 
  
   return -1; 
} 
  
int main(void) 
{ 
   int arr[] = {2, 3, 4, 10, 40}; 
   int n = sizeof(arr)/ sizeof(arr[0]); 
   int x = 10; 
   int result = binarySearch(arr, 0, n-1, x); 
   (result == -1)? printf("Element is not present in array") 
                 : printf("Element is present at index %d", 
                                                   result); 
   return 0; 
} 