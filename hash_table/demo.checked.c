// Simple hash table demonstration program

/*
$ gcc -O2 -Wall -o demo samples/demo.c ht.c
$ echo 'foo bar the bar bar bar the' | ./demo
*/

#include "3c_ht.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Example:
// $ echo 'foo bar the bar bar bar the' | ./demo
// foo 1
// bar 4
// the 2
// 3

void exit_nomem(void) _Checked {
    _Unchecked { fprintf(stderr, "out of memory\n"); };
    exit(1);
}

int main(void) {
    ht* counts = ht_create();
    if (counts == NULL) _Checked {
        exit_nomem();
    }

    // Read next word from stdin (at most 100 chars long).
    char* word = (char*)malloc<char>(100*sizeof(char));
    while (scanf("%100s",word) != EOF) {
        // Look up word.
        void* value = ht_get(counts, word);
        if (value != NULL) {
            // Already exists, increment int that value points to.
            int* pcount = (int*)value;
            (*pcount)++;
            continue;
        }

        // Word not found, allocate space for new int and set to 1.
        int* pcount = malloc<int>(sizeof(int));
        if (pcount == NULL) _Checked {
            exit_nomem();
        }
        *pcount = 1;
        if (ht_set(counts, word, pcount) == NULL) _Checked {
            exit_nomem();
        }
    }

    // Print out words and frequencies, freeing values as we go.
    hti it = ht_iterator(counts);
    while (ht_next(&it)) {
        printf("%s %d\n", it.key, *(int*)it.value);
        free<void>(it.value);
    }

    // Show the number of unique words.
    printf("%d\n", (int)ht_length(counts));

    ht_destroy(counts);
    return 0;
}
