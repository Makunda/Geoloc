#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "read_log.h"
#include "liste_point.h"

#define chemin_geoloc "../geoloc/traitement.bin"

int main(int argc, char *argv[])
{
	time_t debut, fin;
	time(&debut);
	if((fopen("../geoloc/traitement.bin","r") == NULL) || (fopen("../geoloc/traitement.bin","r") == NULL))
	{
		tete_liste_point_ign *pt;
		pt = read_ign();
		//printf("La taille de la liste :%d \n",pt->taille);
		traitement_texte(pt,definir_taille_tableau(pt));
		vider_liste_ign(pt);
		time(&fin);
		//printf("Temps execution : %lf sec \n",difftime(fin,debut));
	}
	else
	{
		printf(" \n Fichier \"traitement.bin\" et \"index_traitement.bin\" existent déja .\n");
	}
}
//a faire , traiter cas interruption du traitement , avec hashage possible 
