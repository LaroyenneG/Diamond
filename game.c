#include <stdio.h>
#include <stdlib.h>
#include "diamond.h"
#include "sublimeterm.h"
#include "queue.h"

int main(int argc, char** argv){
    if(argc>1){
        perror("Usage diamond");
        return 1;
    }
    clrscr();
    color(38);
    printf("Warning, the terminal background color must be black.\n");
    color(0);
    party_t* p =createParty();
    start(p);
    return 0;
}



