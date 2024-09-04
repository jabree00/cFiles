/* Based on Petra Bonfert-Taylor's interactive online C Textbook */ 

#include <stdio.h>
#include <stdlib.h>

struct digit_t{
  int x; 
  struct digit_t* next; 

}; 

typedef struct digit_t digit; 

digit* append(digit* end, digit* current);
void printNumber(digit* start); 
digit* createDigit(int xIn);
void freeDigits(digit* start);
int search(digit* start, int target);
digit* reverse(digit* start);

int main(){
  int length = 0; 
  int currentNum = 0; 
  digit* start; 
  digit* end; 

  printf("How long is your number?\n");
  scanf("%d", &length);
  
  
  for(int i = 0; i < length; i++){
    printf("Type a number:\n");
    scanf("%d", &currentNum);
    digit* currentNumDigit = createDigit(currentNum);
    
    if(i == 0){
      start = currentNumDigit;
      end = currentNumDigit; 
      
    } else {
      end = append(end,currentNumDigit);
    }
    
  }

  printNumber(start);
  int searchNum = 0; 

  printf("\nWhat is your number to search for?\n");
  scanf("%d", &searchNum);

  printf("Result: %d\n", search(start,searchNum));

  printf("\nPrinting in Reverse:\n");
  digit* rev = reverse(start); 
  printNumber(rev);
  
  

  freeDigits(start);

  return 0; 
}


digit* createDigit(int xIn){
  digit* d = (digit*) malloc(sizeof(digit));
  //Make sure all attributes have a value 
  d->x = xIn;  
  d->next = NULL; 
  
  return (d);
}

 digit* append(digit* end, digit* current){  
   end->next = current; 
   return end->next; 
   
 }

void printNumber(digit* start){
  digit* copy = start; 
  while(copy != NULL){
    printf("%d",copy->x);
    copy = copy->next;
    
  }
  
}

void freeDigits(digit* start){
  //store a copy of where start is 
  digit* current = start; 

  while(current != NULL){
    //Each iteration, update start with the new start (current) of the list
    start = current; 
    current = current->next;
    free(start);
  }
  
}

int search(digit* start, int target){
  digit* currentPointer = start; 

  while(currentPointer != NULL){
    if(currentPointer->x == target){
      return 1; 
    }
    currentPointer = currentPointer->next;
  }
  return 0; 
}

digit* reverse(digit* start){
  digit* end = NULL; 
  digit* current = start; 
  digit* newStart = NULL;  

  //Loop until current is the end
  while(current->next != NULL){

    //Grab the next number in the list turn it into a digit object. 
    digit* d = createDigit(current->next->x);

    //Update the current digit to be the first 
    //
    d->next = current;
    newStart = d; 
    printf("New Start: %d", d->x);
    current = current->next; 
  }

  return newStart;
  
}
