//
// Created by guillaume on 06/11/16.
//

#ifndef PROJETALGOC_SUBLIMETERM_H
#define PROJETALGOC_SUBLIMETERM_H

#define noir "\e[0;30m"
#define gris "\e[1;30m"
#define rougefonce "\e[0;31m"
#define rose "\e[1;31m"
#define vertfonce "\e[0;32m"
#define vertclair "\e[1;32m"
#define orange "\e[0;33m"
#define jaune "\e[1;33m"
#define bleufonce "\e[0;34m"
#define bleuclair "\e[1;34m"
#define violetfonce "\e[0;35m"
#define violetclair "\e[1;35m"
#define cyanfonce "\e[0;36m"
#define cyanclair "\e[1;36m"
#define grisclair "\e[0;37m"
#define blanc "\e[1;37m"
#define neutre "\e[0;m"

/* clrscr()
 * Cleans the terminal display.
 */
#define clrscr() printf("\033[H\033[2J");

void color(int i);

#endif //PROJETALGOC_SUBLIMETERM_H
