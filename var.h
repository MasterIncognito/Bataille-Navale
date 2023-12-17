/*! \file var.h
    \brief A file with the variables and classes
    
    Contains 3 struct and 3 variables
*/

/*! \struct bateau
    \brief Class for every boat
*/

#ifndef var
#define var
typedef struct S_bateau{
	int taille;
	int x;
	int y;
	int orientation;///< 0=Horizontal, 1=Vettical and -1=Sunken
} bateau;


/*! \struct plateau
    \brief Board class
*/
typedef struct S_plateau{
	int x;
	int y;
	int taille;
	int** tab;
} plateau;


/*! \struct Jeu
    \brief Main game class containing 2 boat struct arrays and 2 boards
*/
typedef struct S_Jeu{
	plateau p1;
	plateau p2;
	bateau * b1;
	bateau * b2;
} Jeu;


#endif
