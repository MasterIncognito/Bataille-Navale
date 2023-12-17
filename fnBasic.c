/*! \file fnBasic.c
    \brief A file with the basic functions
    
    Contains basic functions like basic tests and emptying input buffer
*/

#include "fnBasic.h"
#include "var.h"
#include <stdio.h>

/*! \fn void viderBuffer()
    \brief Method used to empty out the input buffer
*/
void viderBuffer(){
	int c=0;
	while (c!='\n' && c != EOF)
		{c=getchar();}}

/*! \fn struct bateau New_bateau(int taille, int orientation, int x, int y)
    \brief Function that creates a new boat and defines its parameters
*/
bateau New_bateau(int taille, int orientation, int x, int y){
	bateau NB;
	NB.taille=taille;
	NB.orientation=orientation;
	NB.x=x;
	NB.y=y;
	return NB;
}

/*! \fn int Invalide(struct plateau p, int x, int y, int orientation, int taille, int taillep)
    \brief Function checking if coordinates in parameters are a correct boat placement
    \return 0 if placement correct, 1 if it's invalid
*/
int Invalide(plateau p, int x, int y, int orientation, int tailleB, int taillePl){
	if ((y+(orientation*tailleB))>=taillePl || (x+((1-orientation)*tailleB)>=taillePl)){
		return 1;
	}
	for (int j=0;j<tailleB;j++){
		if (p.tab[x+((1-orientation)*j)][y+(orientation*j)]==1){
			return 1;
		}
	}
	return 0;
}

/*! \fn int SOS (struct bateau b, struct plateau p)
    \brief Function checking if a boat is alive
    \return 0 if at least 1 spot is intact, 1 if it has been hit at every spot and is therefore not alive.
*/
int SOS(bateau b, plateau p){
	for (int i=0;i<b.taille;i++){
		if (p.tab[b.x+((1-b.orientation)*i)][b.y+(b.orientation*i)]<2){
			return 0;
		}
	}
	return 1;
}

/*! \fn int win(struct bateau * lb, int nbj)
    \brief Function checking if there are still living boats in list passed in args
    \return 0 if there is at least one boat alive, 1 if there are none
*/
int win(bateau * lb, int nbatj){
	for (int i=0; i<nbatj; i++){
		if (lb[i].orientation>=0){
			return 0;
		}
	}
	return 1;
}
