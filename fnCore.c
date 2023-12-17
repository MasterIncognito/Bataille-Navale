/*! \file fnCore.c
    \brief A file with all Core functions
    
    Contains the main game functions, like display and game turns
*/

/*! \fn struct Jeu New_Jeu(int taillep, int nbj)
    \brief Function setting up the Game struct, allocating memory for both boards and later on for the boat lists
*/
#include <stdlib.h>
#include <stdio.h>
#include "fnCore.h"
#include "var.h"
#include "fnBasic.h"

Jeu New_Jeu(int taillep, int nbj){
	int templ,x,y,orientation;
	Jeu Je;
	plateau p1;
	plateau p2;
	p1.taille=taillep;
	p2.taille=taillep;
	p1.tab=malloc(taillep*sizeof(int*));
	if (p1.tab==NULL) {
		printf("Erreur de mémoire.\n");
		exit(0);
	}
	for (int i=0;i<taillep;i++){
		p1.tab[i]=malloc(taillep*sizeof(int));
		if (p1.tab[i]==NULL) {
			printf("Erreur de mémoire.\n");
			exit(0);
		}
		for (int j=0;j<taillep;j++){
			p1.tab[i][j]=0;
		}
	}
	p2.tab=malloc(taillep*sizeof(int*));
	if (p2.tab==NULL) {
		printf("Erreur de mémoire.\n");
		exit(0);
	}
	for (int i=0;i<taillep;i++){
		p2.tab[i]=malloc(taillep*sizeof(int));
		if (p2.tab[i]==NULL) {
			printf("Erreur de mémoire.\n");
			exit(0);
		}
		for (int j=0;j<taillep;j++){
			p2.tab[i][j]=0;
		}
	}
	Je.p1=p1;
	Je.p2=p2;
	bateau* b1=malloc(nbj*sizeof(bateau));
	if (b1==NULL) {
		printf("Erreur de mémoire.\n");
		exit(0);
	}
	bateau* b2=malloc(nbj*sizeof(bateau));
	if (b2==NULL) {
		printf("Erreur de mémoire.\n");
		exit(0);
	}

	for (int i=0; i<nbj;i++){
		templ=rand()%4 +2; ///Randomly chooses the size of this new pair of boats, between 2 and 5. That way, both boards will end up with equally sized boats
		do {
			x=rand()%taillep;
			y=rand()%taillep;
			orientation=rand()%2; ///0=Horizontal, 1=Vettical and -1=Sunken
		} while (Invalide(p1,x,y,orientation,templ,taillep));
		for (int j=0;j<templ;j++){
			p1.tab[x+((1-orientation)*j)][y+(orientation*j)]=1;
		}
		b1[i]=New_bateau(templ, orientation, x, y); ///Creating a boat for the first board
		do {
			x=rand()%taillep;
			y=rand()%taillep;
			orientation=rand()%2; ///0=Horizontal, 1=Vettical and -1=Sunken
		} while (Invalide(p2,x,y,orientation,templ,taillep));
		for (int j=0;j<templ;j++){
			p2.tab[x+((1-orientation)*j)][y+(orientation*j)]=1;
		}
		b2[i]=New_bateau(templ, orientation, x, y); ///And creating another boat for the second board
	}
	Je.b1=b1; ///Assigning boat lists to the game struct
	Je.b2=b2;
	return Je;

}

/*! \fn void display(struct plateau p,int taillep, int mode)
    \brief Used to display one of the two boards, mode 0 hides undiscovered boats while mode 1 displays them.
*/
void display(plateau p,int taillep, int mode){
	printf("\n\n+");
	for (int i=0;i<=taillep;i++){
		printf("-+");
	}
	printf("\n|");
	for (int j=0;j<taillep;j++){
		printf("%d|",j);
	}
	printf(" |\n+");
	for (int i=0;i<=taillep;i++){
		printf("-+");
	}
	for (int k=0;k<taillep;k++){
		printf("\n|");
		for (int j=0;j<taillep;j++){
			switch (p.tab[j][k]){
				case 0:
					printf(" ");
					break;
				case 1:
					if (mode==0){
						printf(" ");
					}else {
						printf("M");
					}
					break;
				case 2:
					printf("O");
					break;
				case 3:
					printf("X");
					break;
				case 4:
					printf("W");
					break;
			}
			printf("|");
		}
		printf("%d|",k);
		printf("\n+");
		for (int i=0;i<=taillep;i++){
			printf("-+");
		}
		
	}
	printf("\n");
}

/*! \fn struct plateau TourJ(struct plateau p, int taillep)
    \brief Runs through a player turn
*/
plateau TourJ(plateau p, int taillep){
	int x,y,t;
	printf("\nEntrer Coordonnées entre 0 et %d:\n",taillep-1);
	do{
		printf("\nx : ");
		scanf("%d",&x);
		viderBuffer();
	}while(x<0 || x>=taillep);
	do{
		printf("\ny : ");
		scanf("%d",&y);
		viderBuffer();
	}while(y<0 || y>=taillep);
	
	printf("\nTir en %d,%d...",x,y);
	getchar();			///Waits for user input
	if (p.tab[x][y]==0){		///0>Water>Missed
		printf("\nRaté !");
		p.tab[x][y]+=2;
	}else if (p.tab[x][y]==1){	///1>Boat>Hit
		printf("\nTouché !");
		p.tab[x][y]+=2;
	}else {
		printf("Cible déjà touché");	///In case user shoots same spot twice
	}
	return p;	
}

/*! \fn struct bateau * Update_B(struct bateau* bl, struct plateau p, int nbj)
    \brief Function checking if any boat from the list is sinking to update the table for a different display
*/
bateau * Update_B(bateau* bl, plateau p, int nbj){
	for (int i=0;i<nbj;i++){
		if (bl[i].orientation>=0 && SOS(bl[i],p)){
			for (int j=0;j<bl[i].taille;j++){
				p.tab[bl[i].x+((1-bl[i].orientation)*j)][bl[i].y+(bl[i].orientation*j)]=4;
			}
			bl[i].orientation=-1;
			printf("\nBateau de taille %d coulé !",bl[i].taille);
		}
	}
	return bl;
}

/*! \fn struct plateau TourO(struct plateau p, int taillep)
    \brief Runs through a computer turn
*/
plateau TourO(plateau p, int taillep){
	int x,y,t;
	printf("\nL'ordinateur tire...\n");
	do{
		x=rand()%taillep;
		y=rand()%taillep;
	}while(p.tab[x][y]>1);
	printf("\nTir en %d,%d...",x,y);
	getchar();			///Waiting for user input
	if (p.tab[x][y]==0){		///0>Water>Missed
		printf("\nRaté !");
		p.tab[x][y]+=2;
	}else if (p.tab[x][y]==1){	///1>Boat>Hit
		printf("\nTouché !");
		p.tab[x][y]+=2;
	}
	return p;	
}
