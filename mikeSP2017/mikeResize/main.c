#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main(int argc, char *argv[]){
    int characterNum, DEFAULT_SIZE, nchr, cNum, foundWords, flag;
    char **inputArray, **outputArray, **outputArray2, **temp, *token, *ln, **words;
    int *count, *temp2;
    size_t n;
    size_t it, it2;
    size_t linesRead, index;
    size_t lmax;
    size_t wordSize;
    FILE *fp;
    const char s[2] = " ";

    DEFAULT_SIZE = 30;
    inputArray = (char**)calloc((size_t) DEFAULT_SIZE, sizeof(char*));
    ln = NULL;
    n = 0;
    nchr = 0;
    it = 0;
    linesRead = 0;
    lmax = (size_t) DEFAULT_SIZE;
    fp = NULL;
    temp = NULL;
    wordSize = 0;
    index = 0;
    foundWords = 0;
/*
    printf("%d %s %s\n", argc, argv[1], argv[2]);
*/
    if(argc != 3){
        printf("ERROR: invalid number of parameters");
        return 1;
    }
    characterNum = atoi(argv[1]);



    if(characterNum < 25 || characterNum > 100){
        printf("First argument isn't in the range 25<= x <=100\n");
        return 1;
    }
    fp = fopen(argv[2], "r");

    if(fp == NULL){
        printf("ERROR: second argument isn't a valid file\n");
        return 1;
    }

    while ((nchr = (int) getline(&ln, &n, fp)) != -1){
        while(nchr > 0 && (ln[nchr - 1] =='\n' || ln[nchr-1] == '\r'))
            ln[--nchr] = 0;

        inputArray[linesRead++] = strdup(ln);

        if(linesRead == lmax){
            temp = realloc(inputArray, (lmax * 2) * sizeof(char*));
            if(!temp)
                return -1;
            inputArray = temp;
            lmax *= 2;

        }

    }
/*    printf("\nlines in file:\n\n");     print lines in file
    for (it = 0; it < linesRead; it++)
        printf ("  array [%3zu]  %s\n", it, inputArray[it]);
    printf ("\n");
*/

    if(fp)
        fclose (fp);
    if(ln)
        free (ln);


    outputArray = (char**)calloc((size_t) DEFAULT_SIZE, sizeof(char*));

    for(it = 0; it < DEFAULT_SIZE; it++){
        outputArray[it] = calloc((size_t) characterNum, sizeof(char*));

    }
    cNum = characterNum;
    lmax = (size_t) DEFAULT_SIZE;
    for(it = 0; it < linesRead; it++){
        ln = strtok(inputArray[it], s);
        while(ln != NULL){
            wordSize = strlen(ln);
            int test;
            test = (int) (cNum - wordSize - 1);

            if ( test < 0 ) {
                outputArray[index][characterNum - cNum - 1] = '\n';
                /* printf("%s", outputArray[index]);*/
                index++;


                if (index == lmax) {
                    temp = realloc(outputArray, lmax * 2 * sizeof *outputArray);
                    if (!temp)
                        return -1;
                    outputArray = temp;
                    lmax *= 2;

                    for (it2 = index; it2 < lmax; it2++)
                        outputArray[it2] = calloc((size_t) characterNum, sizeof(char *));
                }
                cNum = characterNum;
            }
            cNum -= wordSize + 1;
            strcat(outputArray[index], ln);
            strcat(outputArray[index], s);
            ln = strtok(NULL, s);
        }


    }
/*
    printf("%s\n", outputArray[index]);

    printf("\nLines in file:\n\n");

    for(it = 0; it <= index; it++)
        printf(" array [%3zu] %s", it, outputArray[it]);
    printf("\n");
*/
    outputArray2 = (char**)calloc((size_t) lmax, sizeof(char*));

    for(it = 0; it < lmax; it++){
        outputArray2[it] = calloc((size_t) characterNum, sizeof(char*));

    }

    for(it = 0; it < lmax; it++){
        outputArray2[it] = strdup (outputArray[it]);
    }


    fp = fopen("data.out", "w");
    for(it = 0; it <= index; it++){
        fprintf(fp, outputArray[it]);
    }

    fclose(fp);











/*part B*/

    lmax = 100;
    words = calloc(lmax, sizeof(char*));

    for(it = 0; it < 100; it++){
        words[it] = calloc(20, sizeof(char));
    }
    count = calloc(lmax, sizeof(int));



    for(it = 0; it <= index; it++){
        ln = strtok(outputArray[it], s);

        wordSize = strlen(ln);

        while(wordSize > 0 && (ln[wordSize - 1] =='\n'))
            ln[--wordSize] = 0;


        while(ln != NULL){
            flag = 0;
            for(it2 = 0; it2 < foundWords && !flag; it2++){
                if (!strcmp(ln, words[it2])){
                    flag = 1;
                }
            }
            if (!flag){
                if(foundWords == lmax){
                    temp = realloc(words, lmax * 2 * sizeof *words);
                    if (!temp)
                        return -1;
                    words = temp;
                    lmax *= 2;

                    for (it2 = index; it2 < lmax; it2++)
                        words[it2] = calloc(20, sizeof(char*));
                }
                words[foundWords++] = strdup (ln);
            }
            ln = strtok(NULL, s);
        }

    }
    for(it = 0; it <= foundWords; it++){
        printf(" array [%3zu] %s\n", it, words[it]);
    }
    printf("\n");

    for(it = 0; it < linesRead; it++){
        free(inputArray[it]);
    }


    free(inputArray);



    return 0;
}