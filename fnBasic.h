#include "var.h"

void viderBuffer();

bateau New_bateau(int taille, int orientation, int x, int y);

int Invalide(plateau p, int x, int y, int orientation, int taille, int taillep);

int SOS (bateau b, plateau p);

int win(bateau * lb, int nbj);
