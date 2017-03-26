#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int characterNum, linesRead, DEFAULT_SIZE, arraySize, i;
    FILE *input, *output;
    char **inputArray, *line;
    size_t  len;
    ssize_t nread;
    DEFAULT_SIZE = 30;
    inputArray = (char **)calloc(DEFAULT_SIZE, sizeof(char));
    linesRead = 0;
    arraySize = DEFAULT_SIZE;
   // printf("%d %s %s\n", argc, argv[1], argv[2]);
   // printf("%d\n", (int) len(inputArray));
    if (argc != 3){
        printf("ERROR: Invalid number of parameters\n");
        return 1;
    }
    characterNum = atoi(argv[1]);
    if (characterNum < 25 || characterNum > 100){
        printf("ERROR: First argument isn't in the range 25 <= x <= 100\n");
        return 1;
    }
    input = fopen(argv[2], "r");
    if (input == NULL){
        printf("ERROR: Second argument isn't a valid file\n");
        return 1;
    }
    while (fgets(inputArray[linesRead])){
        if (linesRead == arraySize){
            inputArray = realloc(inputArray, (arraySize + 1) * sizeof(char*));
            arraySize++;
        }
      //  printf("Retrieved line of length %zu :\n", sizeof(line));
        printf("%s\n", line);
        inputArray[linesRead] = (char *)calloc(sizeof(line), sizeof(char));
        inputArray[linesRead] = line;
        if (linesRead != 0)
            printf("%s\n", inputArray[linesRead-1]);
        printf("%s\n", inputArray[linesRead]);
        linesRead++;
    }

    for (i = 0; i < linesRead; i++){
        printf("%s\n", inputArray[i]);
    }




    return 0;
}



// ~(character >= 25 && character <= 100)
// character < 25 || character > 100

// { "a", "b", "c" }
// { "a", "b", "c", "d"}