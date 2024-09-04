/* Based on Petra Bonfert-Taylor's interactive online C Textbook */ 


#include <stdio.h>
#include <stdlib.h>

/* Learnings...
Use print statements to debug each line and see exactly 
where things went wrong. 

Make sure that a function actually does return a value. 

*/

typedef struct {
  float x; 
  float y; 

} point_t;

point_t* createPolygon(int numPoints, int*, int*); 
void printPoint(point_t* pointPointer);
void printPolygon(point_t* ptr,int size);


int main(void) {
  printf("Let's create a polygon!\n");
  int myXVals[5] = {0,1,2,1,0};
  int myYVals[5] = {0,0,1,3,1};
  point_t* ptr = createPolygon(5, myXVals,myYVals); 
  printPolygon(ptr,5);

  return 0;
}

point_t* createPolygon(int numPoints, int* xVals, int* yVals){
  point_t* poly; 
  poly = (point_t*) malloc(numPoints * sizeof(point_t));
  for(int index = 0; index < 5; index+=1){
    poly[index].x = xVals[index]; 
    poly[index].y = yVals[index];  
  }

  return poly; 
}

void printPoint(point_t* pointPointer){
  printf("Point...");
  printf("(x: %.2f, ", (*pointPointer).x); 
  printf("y: %.2f)\n", (*pointPointer).y); 
}

void printPolygon(point_t* ptr,int size){
  printf("Printing Polygon:\n");
  
  for(int i = 0; i < size; i++){
    printf("Current Pointer: %p\n", ptr + i);
    printPoint(ptr + i); 
  }
}

