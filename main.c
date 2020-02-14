#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/

    hashMap ht;
    FILE* f;
    char* nextWord;
    int i;
    hashLink* curr;

    initMap(&ht, 20);

    f = fopen("input.txt", "r");

    nextWord = getWord(f);
    while(nextWord) {
        if(containsKey(&ht, nextWord)) {
            insertMap(&ht, nextWord, *atMap(&ht, nextWord) + 1);
        }
        else insertMap(&ht, nextWord, 1);
        nextWord = getWord(f);
    }

    for(i = 0; i < ht.tableSize; i++) {

        curr = ht.table[i];
        while(curr) {

            printf("%s: %i\n", curr->key, curr->value);
            free(curr->key);
            curr = curr->next;

        }

    }

    fclose(f);

    free(nextWord);
    freeMap(&ht);

    return 0;

}

int isCharValid(char c) {

    return c == '\'' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');

}

char* getWord(FILE *file) {

    char c, buffer[32], * word;
    int n = 0, i, flag = 0;

    c = fgetc(file);
    while(1) {
        
        if(c == EOF) return 0;
        else if(isCharValid(c)) {
            buffer[n++] = c;
            flag = 1;
        } else if(!flag) {
            while(!isCharValid(c)) {
                c = fgetc(file);
                if(c == EOF) return 0;
            }
            flag = 2;
        } else break;

        if(flag != 2) c = fgetc(file);

    }

    word = (char*)malloc(sizeof(char) * n + 1);
    for(i = 0; i < n; i++) word[i] = buffer[i];
    word[n] = '\0';

    return word;
    
}