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
    int y=1;
    while (y){
        printf("Do you want to play ? (yes=1/no=0)\n");
        if(scanf("%d",&y)!=1){
            perror("Input error, the value is not of the type integer");
            exit(2);
        }
        if(y!=1){
            y=0;
        } else{
            party_t* p = createParty();
            start(p);

            pid_t process = fork();
            if(process==-1){
                perror("fork()");
                exit(-2);
            }
            if(process==0){
                printf("Freeing of the memory... ");
                exit(0);
            }

            free_party(p);
            printf("done.\n");
        }
    }

    return 0;
}



