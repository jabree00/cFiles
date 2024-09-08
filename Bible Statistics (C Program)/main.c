#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char book[20];
  int chapters;
  int verses;
  int words;
  char testament[5];

} biblebook;

void printTable(biblebook *mainArray, const int *numBooks);
void handleInput(int choice, FILE *filePtr, biblebook *mainArray,
                 const int *numBooks);
char *toString(biblebook *book, biblebook *mainArray, const int *numBooks);
char *search(char *query, biblebook *mainArray, const int *numBooks);
char *getAndPrintSearchResults(biblebook *mainArray, const int *numBooks);
void saveResults(FILE *filePtr, char *resultsTextPtr);
void sortResults(biblebook *mainArray, const int *numBooks);

int main(void) {
  const int NUM_BOOKS = 66;

  printf("Welcome to the Bible Statistics Database!\n\n");

  // Create array of biblebooks
  biblebook books[NUM_BOOKS];

  // Set variables for reading
  char line[60];
  char book[20];
  int chapters;
  int verses;
  int words;
  char testament[4];

  // Grab the file
  FILE *filePointer;
  filePointer = fopen("bible.csv", "r");

  int index = 0;
  if (filePointer != NULL) {
    // grab the file line and store it in the variable

    while (fgets(line, 60, filePointer) != NULL) {
      // scans a string line with the given format and stores the results in
      char *currentFormat = "%[^,],%d,%d,%d,%s";
      sscanf(line, currentFormat, book, &chapters, &verses, &words, testament);

      // Create a new biblebook object
      // Arrays are NOT assignable, so we use strcpy.
      biblebook current;
      strcpy(current.book, book);
      current.chapters = chapters;
      current.verses = verses;
      current.words = words;
      strcpy(current.testament, testament);

      // Add the biblebook to the array
      books[index] = current;
      index += 1;
    }

    printf("The data was loaded successfully - Hallelujah!\n");
    int input = -1;
    while (input != 0) {
      printf("\n\nWhat would you like to do?\n");
      printf("1-View the data.\n2-Search the data.\n3-Sort the data by the number of verses.\n4-Save "
             "the results.\n0-Quit.\n");
      scanf("%d", &input);
      handleInput(input, filePointer, books, &NUM_BOOKS);
    }

  } else {
    printf("The database could not be accessed.");
  }

  return 0;
}

void handleInput(int choice, FILE *filePtr, biblebook *mainArray,
                 const int *numBooks) {
  char lastResults[6600];
  if (choice == 0) {
    printf("The database is now closed until next time. God bless you!");
    
  } else if (choice == 1) {
    printTable(mainArray, numBooks);
    
  } else if (choice == 2) {
    char *results = getAndPrintSearchResults(mainArray, numBooks);
    strcpy(lastResults, results);

    // Clear the character array
    memset(results, '\0', sizeof(results[0]));

  } else if (choice == 3) {
    sortResults(mainArray, numBooks);

  } else if (choice == 4) {
    saveResults(filePtr, lastResults);

    // Clear the character array
    memset(lastResults, '\0', sizeof(lastResults[0]));

  } else {
    printf("Please type a number from the menu above");
  }
}

void printTable(biblebook *mainArray, const int *numBooks) {
  char tableHeader[100];
  char *format = "|%-20s| %-4s| %-5s| %-6s| %-8s|\n";

  // Print out the struct variables in a formatted way to the result variable.
  snprintf(tableHeader, sizeof(tableHeader), format, "Title", "Chp.", "Vs.",
           "Words", "New/Old");
  char *lineSeparator =
      "----------------------------------------------------\n";
  printf("%s,%s,%s", lineSeparator, tableHeader, lineSeparator);
  for (int i = 0; i < *numBooks; i++) {
    biblebook current = mainArray[i];
    char *book = toString(&current, mainArray, numBooks);
    printf("%s", book);
  }

  printf("%s", lineSeparator);
  printf("\nData Source: "
         "https://versenotes.org/"
         "a-list-of-books-in-the-bible-by-number-of-chapters/\n\n");
}

char *toString(biblebook *book, biblebook *mainArray, const int *numBooks) {
  // Rounded number of characters needed
  char result[100];

  /*
    Explanation of the format:
    1. A left-aligned book title with a min length of 20
    2. A left-aligned number of chapters with a min length of 3
    3. A left-aligned number of verses with a min length of 5
    4. A left-aligned number of words with a min length of 6
    5. A left-aligned category of "New" or "Old" with a min length of 4

  */

  char *format = "|%-20s| %-4d| %-5d| %-6d| %-8s|\n";

  // Print out the struct variables in a formatted way to the result variable.
  snprintf(result, sizeof(result), format, book->book, book->chapters,
           book->verses, book->words, book->testament);

  return result;
}

void printTableHeader() {
  char *lineSeparator =
      "----------------------------------------------------\n";
  printf("%s", lineSeparator);
  char tableHeader[100];
  char *format = "|%-20s| %-4s| %-5s| %-6s| %-8s|\n";
  snprintf(tableHeader, sizeof(tableHeader), format, "Title", "Chp.", "Vs.",
           "Words", "New/Old");
  printf("%s", tableHeader);
  printf("%s", lineSeparator);
}

char *getAndPrintSearchResults(biblebook *mainArray, const int *numBooks) {
  // Add one more space to the buffer than the string size for
  // the null character
  char buffer[51];
  printf("What would you like to search for?\n");

  // Scan user input
  scanf("%50s", buffer);

  printf("You typed: \"%s\"\n", buffer);
  printf("Here are your results:\n");

  // Print the table header
  printTableHeader();

  // Generate the result string
  char results[6600];
  for (int i = 0; i < *numBooks; i++) {
    biblebook current = mainArray[i];
    char *book = toString(&current, mainArray, numBooks);
    if (strstr(book, buffer)) {
      // concatenate book to the results
      strcat(results, book);
    }
  }

  // Print the results
  printf("%s", results);

  return results;
}

void sortResults(biblebook *mainArray, const int *numBooks) {
  biblebook *bookReferences[*numBooks];

  // fill the aray with reference
  for (int i = 0; i < *numBooks; i++) {
    bookReferences[i] = &mainArray[i];
  }

  // For each book (except first)
  for (int i = 1; i < *numBooks; i++) {

    /*Check if there are any biblebooks with a smaller number of verses
      Keep swapping until we reach the end of the array OR compare is
      no longer smaller. Start with the biblebook to the left of the
      one at index i.*/

    int k = i;
    biblebook *current = bookReferences[k];
    int j = i - 1;


    switjc

    while ((bookReferences[j]->verses > current->verses) && j >= 0) {
      // swap references

      biblebook *temp = bookReferences[k];
      bookReferences[k] = bookReferences[j];
      bookReferences[j] = temp;

      // decrease the index
      j = j - 1;
      k = k - 1;
    }

  } // end loop

  char tableHeader[100];
  char *format = "|%-20s| %-4s| %-5s| %-6s| %-8s|\n";

  // Copy the table headers, in a formatted way, to the tableHeader variable
  snprintf(tableHeader, sizeof(tableHeader), format, "Title", "Chp.", "Vs.",
           "Words", "New/Old");
  char *lineSeparator =
      "----------------------------------------------------\n";
  char *dataSource =
      "\nData Source: https://versenotes.org/"
      "a-list-of-books-in-the-bible-by-number-of-chapters/\n\n";
  
  printf("%s%s%s", lineSeparator, tableHeader, lineSeparator);

  // Print out the verses to test if sorted
  for (int i = 0; i < *numBooks; i++) {
    printf("%s\n", toString(bookReferences[i],mainArray,numBooks));
  }

  printf("%s", lineSeparator);

} // end sort

void saveResults(FILE *filePtr, char *resultsTextPtr) {
  // Grab the file
  FILE *filePointer;
  filePointer = fopen("search.txt", "w");

  if (filePointer != NULL) {
    char tableHeader[100];
    char *format = "|%-20s| %-4s| %-5s| %-6s| %-8s|\n";

    // Copy the table headers, in a formatted way, to the tableHeader variable
    snprintf(tableHeader, sizeof(tableHeader), format, "Title", "Chp.", "Vs.",
             "Words", "New/Old");
    char *lineSeparator =
        "----------------------------------------------------\n";
    char *dataSource =
        "\nData Source: https://versenotes.org/"
        "a-list-of-books-in-the-bible-by-number-of-chapters/\n\n";
    fprintf(filePtr, "%s%s%s%s%s", lineSeparator, tableHeader, lineSeparator,
            resultsTextPtr, dataSource);

    fclose(filePtr);

    printf("The results have been saved. Hallelujah!");

  } else {
    printf("Results could not be saved due to an internal error - in "
           "everything we give thanks!");
  }
}