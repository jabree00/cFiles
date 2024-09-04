/* Based on Petra Bonfert-Taylor's interactive online C Textbook */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countWords(char* input); 

int main(void) {
  char* sentence = "I love Jesus!\n";
  /*
  int length = 0;
  printf("How many chars is the sentence?\n");
  scanf("%d",&length); 
  printf("Length: %d\n",length); 
  char* sentence = (char *) malloc((length + 1) * sizeof(char));
  printf("Bytes allocated at: %p.\n",sentence); 
  
  printf("Type in a sentence:");
  scanf("%s",sentence);
  */
  
  int num = countWords(sentence);
  printf("There were %d words in the sentence.\n",num);
  
  return 0;
}

int countWords(char* input){
  printf("This is the input: %s", input);
  char current = ' '; 
  int count = 1; 
  for(int index = 0; index < strlen(input); index++){
    current = *(input + index);
    printf("Current char is %c.\n",current);

    if(current == ' '){
      count += 1; 
    } 
  }

  return count; 
  
}
