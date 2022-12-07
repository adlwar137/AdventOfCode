#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* filePointer;
char test[10];
int numberOfElves;

int cmpfunc(const void *a, const void *b) {
    return ( *(int*)b - *(int*)a );
}

int main() {
    filePointer = fopen("input.txt", "r");

    //find the number of elves
    //use a newline detection hack by counting how many lines are of length 1
    while(fgets(test, 10, filePointer) != NULL) {
        if((int)strlen(test) == 1) {
            numberOfElves++;
        }
    }

    //allocate an array of all the elves on the stack
    int *elvesArray = (int*)calloc(numberOfElves, sizeof(int));

    //seek to the beginning of the file
    fseek(filePointer, 0, SEEK_SET);

    //use the same newline detection hack
    //sum to current index until newline
    //when newline compare to the largest found
    //then increase index to do the next elf
    int index = 0;
    int largest = 0;
    while(fgets(test, 10, filePointer) != NULL) {
        if((int)strlen(test) != 1) {
            elvesArray[index] += atoi(test);
        } else {
            //store largest number come across
            if(elvesArray[index] > largest) {
                largest = elvesArray[index];
            }
            index++;
        }
    }

    //Elf with most calories
    printf("Most Calories: %d\n", largest);
    //sort the list
    qsort(elvesArray, numberOfElves, sizeof(elvesArray[0]), cmpfunc);
    //add up the top three
    printf("Top three total: %d\n", elvesArray[0] + elvesArray[1] + elvesArray[2]);
    //don't forgot to let the memory free :)
    free(elvesArray);
    fclose(filePointer);
    return 0;
}