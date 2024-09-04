/* 
Based on Petra Bonfert-Taylor's online interactive C Textbook assignments. 
*/

#include <stdio.h>
void printArray(int* pointer, int size);
void bubbleSort(int* pointer, int size);
void selectionSort(int* pointer, int size);
void insertionSort(int* pointer, int size);
void shiftArray(int* pointer,int size, int index);

int main(void) {
  int nums[10] = {10,5,7,3,280,40,2,1,9,8};
  //shiftArray(nums,10,1);
  printArray(nums,10);
  printf("\n");
  insertionSort(nums,10);
  printArray(nums,10);
  
}

void printArray(int* pointer, int size){
  for(int i = 0; i < 10; i++){
    printf("%d ",pointer[i]); 
  }
}


void bubbleSort(int* pointer, int size){

  /*the element at the ith spot is ignored
    the inner loop repeats n times, where 
    n is the numebr of elements in the aray.*/
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < (10 - i); j++){

      if(pointer[j] > pointer[j+1]){
        //Swap
        int temp = pointer[j+1]; 
          pointer[j+1] = pointer[j];
          pointer[j] = temp; 
      }
    }
  } //end outer loop 
  
}


void selectionSort(int* pointer, int size){

  /*the element at the ith spot is ignored
    the inner loop repeats n times, where 
    n is the numebr of elements in the aray.*/
  for(int i = 0; i < 10; i++){
    int minIndex = i; 
    for(int j = i; j < 10; j++){
      if(pointer[j] < pointer[minIndex]){
        minIndex  = j; 
      }
    }

    //Swap
    int temp = pointer[minIndex]; 
    pointer[minIndex] = pointer[i];
    pointer[i] = temp; 
  } //end outer loop 

}

void insertionSort(int* pointer, int size){

  /*the element at the ith spot is ignored
    the inner loop repeats n times, where 
    n is the numebr of elements in the aray.*/
  for(int i = 0; i < 10; i++){
    int minIndex = i; 
    //printf("Min Index: %d\n",minIndex);
    for(int j = i; j < 10; j++){
      if(pointer[j] < pointer[minIndex]){
        minIndex  = j; 
      }
    }

    int k = minIndex - 1; 
    while(k >= i){
      //Swap
      int temp = pointer[k+1];
      pointer[k+1] = pointer[k];
      pointer[k] = temp; 
      k--;
   }
    
  } //end outer loop 

}

void shiftArray(int* pointer,int size, int index){
  for(int i = size - 1; i > index; i--){
    pointer[i] = pointer[i-1];
  }

}


