#include <stdio.h>

int main(void) {
  //initialize vars 
  int num1 = 0; 
  int num2 = 0; 
  int num3 = 0; 

  printf("Find the average!\n\n");
  printf("Type your first number:\n");
  scanf("%d",&num1);
  printf("Type your second number:\n");
  scanf("%d",&num2);
  printf("Type your third number:\n");
  scanf("%d",&num3);

  printf("Your average is: %d ", (num1 + num2 + num3)/3);
}
