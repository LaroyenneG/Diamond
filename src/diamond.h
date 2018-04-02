//
// Created by Guillaume LAROYENNE on 06/11/16.
//

#ifndef __DIAMOND_H__
#define __DIAMOND_H__

/* define and struct for the board */
#define VOID_CELL -1
#define NO_NEIGHBOR -1

typedef struct gameboard {
    char board[13];
    char neighbors[13][6];
    int blueScore;
    int redScore;
} board_t;

/* defines and structs for the tree */

#define NO_RESULT -1
#define DRAW_PARTY 0
#define BLUE_WINS 1
#define RED_WINS 2

/* NOTE :
   refer to the subject of the project from some explanations about
   the struct node** children field used below
 */
typedef struct node {
    char idCell; // NB : a char is sufficient because the board has 13 cells.
    char turn; // NB : a char is sufficent because there are at most 12 turns.
    char result;
    struct node **children;
    char nbChildren; // NB :  a char is sufficient because there are at most 12 children
} node_t;


typedef struct tree {
    node_t *root;
    node_t *saveNode; //In memory where the game finds in the tree.
} tree_t;

typedef struct party {
    board_t *board;
    tree_t *tree;
} party_t;

/* declared as global instead of a field in tree */
extern int nbConfigurations;

/* functions to manage the board */
board_t *createBoard();

void clearBoard(board_t *b);

int voidCellIndex(board_t *b);

void computeScore(board_t *b);

void setPawn(board_t *b, int idCell, char value);

void printBoard(board_t *b);

void free_board(board_t *b);

/* functions to manage the node */
node_t *createNode(int idCell, int turn);

node_t *addChild(node_t *n, int idCell);

void printNode(node_t *n);

void free_node(node_t *n);

/* functions to manage the tree */
tree_t *createTree();

void setFirstBlueChoice(tree_t *t, board_t *b, int idCell);

void setFirstRedChoice(tree_t *t, board_t *b, int idCell);

void buildTree(tree_t *t, board_t *b);

void computePossibilities(node_t *n, board_t *b);

int computeBlueVictories(node_t *n);

int computeRedVictories(node_t *n);

int computeDraws(node_t *n);

node_t **seekPossibility(node_t *parent, int idCell);

int seekNbPossibility(node_t *parent, int idCell);

char findGoodChoice(tree_t *t, int bleuCell);

void free_tree(tree_t *t);

/* functions to manage the party */
party_t *createParty();

char bleuPlayer(party_t *p);

void start(party_t *p);

void free_party(party_t *p);

#endif
