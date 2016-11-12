#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "diamond.h"
#include "sublimeterm.h"
#include "queue.h"


int nbConfigurations;

/**********************************
   functions to mangage the board
***********************************/
board_t* createBoard() {
    board_t* b = NULL;
    b=malloc(sizeof(board_t));
    clearBoard(b);

    for(int i=0; i<13; i++) {
        for(int j=0;j<6;j++) {
            b->neighbors[i][j] = NO_NEIGHBOR;
        }
    }

    // define neighbors for cell 0
    b->neighbors[0][0] = 1;
    b->neighbors[0][1] = 3;
    b->neighbors[0][2] = 4;
    // define neighbors for cell 1
    b->neighbors[1][0] = 0;
    b->neighbors[1][1] = 2;
    b->neighbors[1][2] = 4;
    b->neighbors[1][3] = 5;
    // define neighbors for cell 2
    b->neighbors[2][0] = 1;
    b->neighbors[2][1] = 5;
    b->neighbors[2][2] = 6;
    // define neighbors for cell 3
    b->neighbors[3][0] = 0;
    b->neighbors[3][1] = 4;
    b->neighbors[3][2] = 7;
    // define neighbors for cell 4
    b->neighbors[4][0] = 0;
    b->neighbors[4][1] = 1;
    b->neighbors[4][2] = 3;
    b->neighbors[4][3] = 5;
    b->neighbors[4][4] = 7;
    b->neighbors[4][5] = 8;
    // define neighbors for cell 5
    b->neighbors[5][0] = 1;
    b->neighbors[5][1] = 2;
    b->neighbors[5][2] = 4;
    b->neighbors[5][3] = 6;
    b->neighbors[5][4] = 8;
    b->neighbors[5][5] = 9;
    // define neighbors for cell 6
    b->neighbors[6][0] = 2;
    b->neighbors[6][1] = 5;
    b->neighbors[6][2] = 9;
    // define neighbors for cell 7
    b->neighbors[7][0] = 3;
    b->neighbors[7][1] = 4;
    b->neighbors[7][2] = 8;
    b->neighbors[7][3] = 10;
    // define neighbors for cell 8
    b->neighbors[8][0] = 4;
    b->neighbors[8][1] = 5;
    b->neighbors[8][2] = 7;
    b->neighbors[8][3] = 9;
    b->neighbors[8][4] = 10;
    b->neighbors[8][5] = 11;
    // define neighbors for cell 9
    b->neighbors[9][0] = 5;
    b->neighbors[9][1] = 6;
    b->neighbors[9][2] = 8;
    b->neighbors[9][3] = 11;
    // define neighbors for cell 10
    b->neighbors[10][0] = 7;
    b->neighbors[10][1] = 8;
    b->neighbors[10][2] = 11;
    b->neighbors[10][3] = 12;
    // define neighbors for cell 11
    b->neighbors[11][0] = 8;
    b->neighbors[11][1] = 9;
    b->neighbors[11][2] = 10;
    b->neighbors[11][3] = 12;
    // define neighbors for cell 12
    b->neighbors[12][0] = 10;
    b->neighbors[12][1] = 11;

    return b;
}

void clearBoard(board_t* b) {
    for(int i=0;i<13;i++) {
        b->board[i] = VOID_CELL;
    }
    b->blueScore = 0;
    b->redScore = 0;
}

int voidCellIndex(board_t* b) {
    int id = -1;
    for(int i=0;i<13;i++) {
        if (b->board[i] == VOID_CELL) {
            return i;
        }
    }
    return id;
}

void computeScore(board_t* b) {
    b->blueScore = 0;
    b->redScore = 0;
    int idVoid = voidCellIndex(b);
    for(int i=0;i<6;i++) {
        if (b->neighbors[idVoid][i] != NO_NEIGHBOR) {
            if (b->board[(int)b->neighbors[idVoid][i]] <= 6) {
                b->blueScore += b->board[(int)b->neighbors[idVoid][i]];
            }
            else {
                b->redScore += (b->board[(int)b->neighbors[idVoid][i]]-6);
            }
        }
    }
}

void setPawn(board_t* b, int idCell, char value) {
    b->board[idCell] = value;
}

char getPawn(board_t* b, int idCell) { return b->board[idCell]; }

void printBoard(board_t* b){
    int indentation=5;
    const char grid[] ={'\n',' ','+','-','+','-','+','-','+','\n',' ','|','n','|','n','|','n','|','\n','+','-','+','-','+','-','+','-','+','\n','|','n','|','n','|','n','|','n','|','\n','+','-','+','-','+','-','+','-','+','\n',' ','|','n','|','n','|','n','|','\n',' ','+','-','+','-','+','-','+','\n',' ',' ','|','n','|','n','|','\n',' ',' ','+','-','+','-','+','\n',' ',' ',' ','|','n','|','\n',' ',' ',' ','+','-','+','\n'};
    int count=0;
    for (int i=0; i<97;i++){
        color(37);
        if(grid[i]!='n'){
            printf("%c",grid[i]);
        }else {
            if(b->board[count]==NO_NEIGHBOR){
                printf("%d",count);
            }else {
                if(b->board[count]<=6){
                    color(34);
                    printf("%d",b->board[count]);
                }else{
                    color(35);
                    printf("%d",b->board[count]-6);
                }
            }
            count++;
        }
        if(grid[i]=='\n'){
            for(int i=0; i<indentation; i++){
                printf(" ");
            }
        }
    }
    printf("\n");
}

/**********************************
   functions to mangage the nodes
***********************************/

node_t* createNode(int idCell, int turn) {
    node_t* n = NULL;
    n=malloc(sizeof(node_t));
    n->idCell=(char)idCell;
    n->turn=(char)turn;
    if(turn ==1){
        n->children=malloc(sizeof(node_t*));
    } else if (turn<12){
        n->children=malloc(sizeof(node_t*)*(13-turn));
    } else {
        n->children=NULL;
    }
    n->nbChildren = 0;
    n->result = NO_RESULT;
    return n;
}

node_t* addChild(node_t* n, int idCell) {
    node_t* child = NULL;
    child=createNode(idCell, n->turn+1);
    n->children[(int)n->nbChildren]=child;
    n->nbChildren += 1;
    return child;
}

void printNode(node_t* n){
    printf("Node :\n idClell= %d\n turn= %d\n nbChildren= %d\n result= %d\n",n->idCell, n->turn, n->nbChildren, n->result);
}

/**********************************
   functions to mangage the tree
***********************************/

tree_t* createTree() {
    tree_t* t = NULL;

    t=malloc(sizeof(tree_t));
    t->root=NULL;
    t->saveNode=NULL;

    return t;
}

void setFirstBlueChoice(tree_t* t, board_t* b, int idCell) {
    t->root=createNode(idCell,1);
    setPawn(b ,idCell,1);
}

void setFirstRedChoice(tree_t* t, board_t* b, int idCell) {
    addChild(t->root, idCell);
    setPawn(b ,idCell,7);
}

void buildTree(tree_t* t, board_t* b) {
    node_t* n = t->root->children[0];
    computePossibilities(n,b);
    printf(" done.\n");
}

void computePossibilities(node_t* n, board_t* b) {
    if (n->turn == 12) {
        computeScore(b);
        int red = b->redScore;
        int blue = b->blueScore;
        if (blue == red) {
            n->result = DRAW_PARTY;
        }
        else if (blue < red) {
            n->result = BLUE_WINS;
        }
        else {
            n->result = RED_WINS;
        }
        nbConfigurations += 1;
        if ((nbConfigurations % 1000000) == 0){
            if(fork()==0){
                printf(".");
                exit(0);
            }
        }
        return;
    }
    int nextPawnValue = (n->turn+2)/2;
    if ((n->turn+1)%2 == 0) nextPawnValue += 6;
    for(int i=0;i<13;i++) {
        if (b->board[i] == VOID_CELL) {
            setPawn(b,i,(char)nextPawnValue);
            node_t* child = addChild(n,i);
            computePossibilities(child, b);
            setPawn(b,i,VOID_CELL);
        }
    }
}

int computeBlueVictories(node_t* n) {
    int nb = 0;
    if(n->nbChildren==0){
        if(n->result==BLUE_WINS){
            return 1;
        }
        return 0;
    }
    for(int i=0; i<n->nbChildren; i++){
        nb+=computeBlueVictories(n->children[i]);
    }
    return nb;
}

int computeRedVictories(node_t* n) {
    int nb = 0;
    if(n->nbChildren==0){
        if(n->result==RED_WINS){
            return 1;
        }
        return 0;
    }
    for(int i=0; i<n->nbChildren; i++){
        nb+=computeRedVictories(n->children[i]);
    }
    return nb;
}

int computeDraws(node_t* n) {
    int nb = 0;
    if(n->nbChildren==0){
        if(n->result==DRAW_PARTY){
            return 1;
        }
        return 0;
    }
    for(int i=0; i<n->nbChildren; i++){
        nb+=computeDraws(n->children[i]);
    }
    return nb;
}

/*
 * seekPossibility()
 * Returns the list of possible nodes to play.
 */
node_t** seekPossibility(node_t* parent, int idCell){
    if(parent->idCell==idCell){
        return parent->children;
    }
    queue_t* queue = createQueue();
    for(int i=0; i<parent->nbChildren; i++){
        offer(queue, parent->children[i]);
    }
    while (!isEmpty(queue)){
        node_t* n = poll(queue);
        if(n->idCell==idCell){
            free_queue(queue);
            return n->children;
        }else {
            for(int i=0; i<n->nbChildren; i++){
                offer(queue, n->children[i]);
            }
        }
    }
    free_queue(queue);
    return NULL;
}

/*
 * seeknbPossibility()
 * Returns the number of game possibilities.
 */
int seeknbPossibility(node_t* parent, int idCell){
    if(parent->idCell==idCell){
        return parent->nbChildren;
    }
    queue_t* queue = createQueue();
    for(int i=0; i<parent->nbChildren; i++){
        offer(queue, parent->children[i]);
    }
    while (!isEmpty(queue)){
        node_t* n = poll(queue);

        if(n->idCell==idCell){
            free_queue(queue);
            return n->nbChildren;
        }else {
            for(int i=0; i<n->nbChildren; i++){
                offer(queue, n->children[i]);
            }
        }
    }
    free_queue(queue);
    return 0;
}

/*
 * findGoodChoise()
 * Returns the choice of the red player, depending on the choice of the blue player.
 * Searches the node with the most victory in the tree.
 */
char findGoodChoise(tree_t* t, int bleuCell){
    node_t** nodes=NULL;
    int nbPossibility=0;
    if(t->saveNode==NULL){
        nodes=seekPossibility(t->root, bleuCell);
        nbPossibility=seeknbPossibility(t->root, bleuCell);
    }else {
        nodes=seekPossibility(t->saveNode, bleuCell);
        nbPossibility=seeknbPossibility(t->saveNode, bleuCell);
    }
    int nbWin[nbPossibility];
    int nbDraw[nbPossibility];
    for (int i=0; i<nbPossibility; i++){
        nbWin[i]=computeRedVictories(nodes[i]);
        nbDraw[i]=computeDraws(nodes[i]);
    }
    int bestNode=0;
    int bestStat=0;
    for (int i=0; i<nbPossibility;i++){
        if(bestStat<nbWin[i]){
            bestNode=i;
            bestStat=nbWin[i];
        }
    }
    for (int i=0; i<nbPossibility;i++){
        if(bestStat<nbDraw[i]){
            bestNode=i;
            bestStat=nbDraw[i];
        }
    }
    t->saveNode=nodes[bestNode];
    return nodes[bestNode]->idCell;
}


/**********************************
   functions to mangage the party
***********************************/

party_t* createParty(){
    party_t* p = NULL;
    p=malloc(sizeof(party_t*));
    p->board=createBoard();
    p->tree=createTree();
    return p;
}

char bleuPlayer(party_t* p){
    int c=-1;
    while (c<0||c>12||getPawn(p->board,c)!=NO_NEIGHBOR){
        printf("The bleu player must play :\n");
        scanf("%d",&c);
    }
    return (char) c;
}

void start(party_t* p){
    clearBoard(p->board);
    color(36);
    printf("Game start\n");
    color(37);
    char turn=1;
    char pawn=1;
    printf("Turn number %d\n",turn);
    printBoard(p->board);
    int idCellBlue = bleuPlayer(p);
    setPawn(p->board,idCellBlue,pawn);
    turn++;
    srand((unsigned int) time(NULL));
    int idCellRed = rand()%12;
    while (getPawn(p->board,idCellRed)!=NO_NEIGHBOR){
        if(idCellRed<12){
            idCellRed++;
        }else{
            idCellRed--;
        }
    }
    setPawn(p->board, idCellRed, (char) (pawn + 6));
    turn++;
    setFirstBlueChoice(p->tree,p->board,idCellBlue);
    setFirstRedChoice(p->tree,p->board,idCellRed);
    color(33);
    printf("Tree calculation in process :\n");
    buildTree(p->tree,p->board);
    color(37);
    int nbBlueVictories = computeBlueVictories(p->tree->root);
    int nbRedVictories = computeRedVictories(p->tree->root);
    int nbDraws = computeDraws(p->tree->root);
    printf("nb configuration: %d, nb blue victories: %d, nb red victories: %d, nb draws: %d\n",nbConfigurations,nbBlueVictories, nbRedVictories, nbDraws);
    sleep(2);
    int c=-1;
    while (turn<=12){
        clrscr();
        printf("Turn number %d\n",turn);
        printBoard(p->board);

        if(turn%2==1){
            pawn++;
            c=bleuPlayer(p);
            setPawn(p->board,c,pawn);
        }else {
            setPawn(p->board, findGoodChoise(p->tree,(char) c),(char) (pawn+6));
        }
        turn++;
    }
    clrscr();
    printBoard(p->board);
    computeScore(p->board);
    printf("Bleu score : %d | Red score : %d\n",p->board->blueScore, p->board->redScore);
    if(p->board->blueScore==p->board->redScore){
        color(32);
        printf("Draw party\n");
    }else if (p->board->blueScore>p->board->redScore){
        color(31);
        printf("Game over :/\n");
        printf("The winner is the red player\n");
    }else {
        color(34);
        printf("The winner is the bleu player\n");
    }
    color(0);
}