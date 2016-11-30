#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include "diamond.h"
#include "sublimeterm.h"
#include "queue.h"

int main(int argc, char** argv){
    if(argc>1){
        perror("Usage: diamond");
        return 1;
    }
    clrscr();
    color(38);
    printf("Warning, the terminal background color must be black.\n");
    color(0);
    party_t* p = createParty();
    start(p);
    printf("vidage de la memoire\n");
    free_party(p);
    printf("fin\n");
    party_t* c = createParty();
    start(c);

    return 0;
}



