#include <stdio.h>
#include <stdlib.h>

#include "diamond.h"
#include "../lib/sublimeterm.h"


int main(int argc, char **argv) {
    if (argc > 1) {
        perror("Usage: diamond");
        return EXIT_FAILURE;
    }

    clrscr();
    color(38);
    printf("Warning, the terminal background color must be black.\n");
    color(0);
    int y = 1;
    while (y) {
        printf("Do you want to play ? (yes=1/no=0)\n");
        if (scanf("%d", &y) != 1) {
            perror("Input error, the value is not of the type integer");
            exit(EXIT_FAILURE);
        }
        if (y != 1) {
            y = 0;
        } else {
            party_t *p = createParty();
            start(p);


            printf("Freeing of the memory... ");
            fflush(stdout);

            free_party(p);
            printf("done.\n");
        }
    }
    return 0;
}
