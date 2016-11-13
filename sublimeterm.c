//
// Created by guillaume on 06/11/16.
//

#include <stdio.h>
#include "sublimeterm.h"

/* color()
 * Changes the color of the text written in the terminal.
 */
void color(int i){
    switch(i){
        case 30:
            printf(noir);
            break;
        case 31:
            printf(rougefonce);
            break;
        case 32:
            printf(vertfonce);
            break;
        case 33:
            printf(jaune);
            break;
        case 34:
            printf(bleuclair);
            break;
        case 35:
            printf(rose);
            break;
        case 36:
            printf(cyanfonce);
            break;
        case 37:
            printf(blanc);
            break;
        case 38 :
            printf(orange);
            break;
        case 39 :
            printf(violetclair);
            break;
        default:
            printf(neutre);
            break;
    }
}