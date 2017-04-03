#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LMAX 20
ssize_t getline (char **ln, size_t *n, FILE *fp);
char * strdup (const char *ln);

int cmpfunc (const void * a, const void * b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}



int main (int argc, char **argv) {

    if (argc < 3 ) {
        fprintf (stderr, "error: insufficient input, usage: %s <resize> <filename>\n",
                 argv[0]);
        return 1;
    }

    char **inputArray, **outputArray, **outputArray2, **tmp;        /* array of pointers to char        */
    char **words;
    int *count, foundWords = 0, flag, test;
    char *ln = NULL;                                /* NULL forces getline to allocate  */
    size_t n = 0;                                   /* buf size, 0 use getline default  */
    ssize_t nchr;                                   /* number of chars actually read    */
    size_t idx = 0, idy = 0;                        /* array index for number of lines  */
    size_t it, it2;                                 /* general iterator variable        */
    size_t lmax = LMAX;                             /* current array pointer allocation */
    FILE *fp;                                       /* file pointer                     */
    int resizeNum;                                  /* line resize value                */
    const char s[2] = " ";                          /* String s for strtok delim        */
    size_t wordSize;
    int charNum;

    if (!(fp = fopen (argv[2], "r"))) { /* open file for reading    */
        fprintf (stderr, "error: file open failed '%s'.", argv[2]);
        return 1;
    }

    resizeNum = atoi(argv[1]);
    if (resizeNum < 25 || resizeNum > 100){
        fprintf(stderr, "error: resize value is not in the proper range of 25 <= x <= 100 '%d'", resizeNum);
    }

    /* allocate LMAX pointers and set to NULL. Each of the 255 pointers will
       point to (hold the address of) the beginning of each string read from
       the file below. This will allow access to each string with array[x].
    */
    if (!(inputArray = calloc (LMAX, sizeof *inputArray))) {
        fprintf(stderr, "error: memory allocation failed.");
        return 1;
    }

    /* prototype - ssize_t getline (char **ln, size_t *n, FILE *fp)
       above we declared: char *ln and size_t n. Why don't they match? Simple,
       we will be passing the address of each to getline, so we simply precede
       the variable with the urinary '&' which forces an addition level of
       dereference making char* char** and size_t size_t *. Now the arguments
       match the prototype.
    */
    while ((nchr = getline(&ln, &n, fp)) != -1)    /* read line    */
    {
        while (nchr > 0 && (ln[nchr-1] == '\n' || ln[nchr-1] == '\r'))
            ln[--nchr] = 0;     /* strip newline or carriage rtn    */

        /* allocate & copy ln to array - this will create a block of memory
           to hold each character in ln and copy the characters in ln to that
           memory address. The address will then be stored in array[idx].
           (idx++ just increases idx by 1 so it is ready for the next address)
           There is a lot going on in that simple: array[idx++] = strdup (ln);
        */
        inputArray[idx++] = strdup (ln);

        if (idx == lmax) {      /* if lmax lines reached, realloc   */
            tmp = realloc (inputArray, lmax * 2 * sizeof *inputArray);
            if (!tmp)
                return -1;
            inputArray = tmp;
            lmax *= 2;
        }
    }

    fclose (fp);                /* close file */
    if (ln) free (ln);          /* free memory allocated to ln  */

    /*
        process/use lines in array as needed
        (simple print all lines example below)
    */

    if (!(outputArray = calloc (LMAX, sizeof *outputArray))) {
        fprintf(stderr, "error: memory allocation failed.");
        return 1;
    }

    for(it = 0; it < LMAX; it++){
        if(!(outputArray[it] = calloc((size_t) resizeNum, sizeof(char*)))){
            fprintf(stderr, "error: memory allocation failed.");
            return 1;
        }
    }

    charNum = resizeNum;
    lmax = LMAX;
    for (it = 0; it < idx; it++){
        ln = strtok(inputArray[it], s);
        while ( ln != NULL){
            wordSize = strlen(ln);
            test = (int) (charNum - wordSize - 1);
            if (test < 0){
                outputArray[idy][resizeNum - charNum - 1] = '\n';
               // printf("%s", outputArray[idy]);
                idy++;
                if (idy == lmax) {      /* if lmax lines reached, realloc   */
                    tmp = realloc (outputArray, lmax * 2 * sizeof *outputArray);
                    if (!tmp)
                        return -1;
                    outputArray = tmp;
                    lmax *= 2;
                    for(it2 = idy; it2 < lmax; it2++){
                        if(!(outputArray[it2] = calloc((size_t) resizeNum, sizeof(char*)))){
                            fprintf(stderr, "error: memory allocation failed.");
                            return 1;
                        }
                    }
                }
                charNum = resizeNum;
            }
            charNum -= wordSize + 1;
            strcat(outputArray[idy], ln);
            strcat(outputArray[idy], s);
            ln = strtok(NULL, s);
        }
    }
    outputArray[idy][resizeNum - charNum - 1] = '\n';
  //  printf("%s\n", outputArray[idy]);



//    printf("\nLines in file:\n\n");    /* print lines in file  */
//    for (it = 0; it <= idy; it++)
//        printf ("array [%3zu]  %s", it, outputArray[it]);
//    printf("\n");

    if (!(outputArray2 = calloc (lmax, sizeof *outputArray))) {
        fprintf(stderr, "error: memory allocation failed.");
        return 1;
    }

    for(it = 0; it < lmax; it++){
        if(!(outputArray2[it] = calloc((size_t) resizeNum, sizeof(char*)))){
            fprintf(stderr, "error: memory allocation failed.");
            return 1;
        }
    }
    for (it = 0; it < lmax; it++){
        outputArray2[it] = strdup (outputArray[it]);
    }

    fp = fopen("data.out", "w");
    for (it = 0; it <= idy; it++){
        fprintf(fp, "%s", outputArray[it]);
    }
    fclose(fp);

    lmax = 100;
    words = calloc(lmax, sizeof(char*));
    for(it = 0; it < 100; it++){
        words[it] = calloc(20, sizeof(char));
    }



    for (it = 0; it <= idy; it++){
        ln = strtok(outputArray[it], s);
        while ( ln != NULL){
            wordSize = strlen(ln);
            while (wordSize > 0 && (ln[wordSize-1] == '\n' )){
                ln[--wordSize] = 0;
            }
            flag = 0;
            for (it2 = 0; it2 < foundWords && !flag; it2++){
                if (!strcmp(ln, words[it2])){
                    flag = 1;
                }
            }
            if (!flag){
                if (foundWords == lmax){
                    tmp = realloc (words, lmax * 2 * sizeof *words);
                    if (!tmp)
                        return -1;
                    words = tmp;
                    lmax *= 2;
                    for(it2 = idy; it2 < lmax; it2++){
                        if(!(words[it2] = calloc(20, sizeof(char*)))){
                            fprintf(stderr, "error: memory allocation failed.");
                            return 1;
                        }
                    }
                }
                words[foundWords++] = strdup (ln);
            }
            ln = strtok(NULL, s);
        }
    }

    qsort(words, (size_t) foundWords, sizeof(char *), cmpfunc);
    count = calloc((size_t) (foundWords - 1), sizeof(int));
    for (it = 0; it <= idy; it++){
        ln = strtok(outputArray2[it], s);
        while ( ln != NULL){
            wordSize = strlen(ln);
            while (wordSize > 0 && (ln[wordSize-1] == '\n' ))
                ln[--wordSize] = 0;
            for (it2 = 0; it2 < foundWords; it2++){
                if (!strcmp(ln, words[it2])){
                    count[it2]++;
                }
            }
            ln = strtok(NULL, s);
        }
    }

//    for (it = 0; it < foundWords; it++)
//        printf ("array [%3zu]  %s : %d\n", it, words[it], count[it]);
//    printf("\n");

    fp = fopen("data.words", "w");
    for (it = 0; it < foundWords; it++){
        fprintf(fp, "%s - %d\n", words[it], count[it]);
    }
    fclose(fp);

    for (it = 0; it < idx; it++)        /* free array memory    */
        free (inputArray[it]);
    free (inputArray);

    return 0;
}

/*resize = 60
 * charNum = 5
 *
 * 0 1 2 3 4
 * T o
 * charNum = 2
 */