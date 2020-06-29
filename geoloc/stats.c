#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "structure.h"
#include "fichier.h"
#include "liste_point.h"
#include "cluster.h"
#include "graphic.h"
#include "stats.h"

#define taille_tab 24

int **init_tab_heure()
{
	int **tab = malloc(taille_tab*sizeof(int * ));
	for (int i = 0; i < taille_tab; ++i)
	{
		tab[i] = malloc(2*sizeof( int ));
		tab[i][0] = i;
		tab[i][1] = 0;
	}
	return	tab;
}

void afficher_tab(int **tab)
{
	for (int i = 0; i < taille_tab; ++i)
	{
		printf("heure : %d  | effectif = %d \n",tab[i][0],tab[i][1]);
	}
	printf("\n");
}

void remplir_tab_heure_logs(tete_liste_logs *pt_logs)
{
	element_liste_logs *element_parcour = pt_logs->suiv;
	element_liste_point *element_parcour_cluster;
	for (; element_parcour != NULL; element_parcour = element_parcour->suiv)
	{
		for (element_parcour_cluster = element_parcour->pt_cluster->suiv; element_parcour_cluster != NULL; element_parcour_cluster = element_parcour_cluster->suiv)
		{
			remplir_tab_heure(element_parcour->pt,element_parcour_cluster);
		}
	}
}


void remplir_tab_heure(tete_liste_point *pt, element_liste_point *p_cluster) 
{
	int **tab = init_tab_heure();
	element_liste_point *temp = pt->suiv;
	char buf[80];
	time_t ts ;
	struct tm date;
	int heure;

	for (;temp != NULL;temp =temp->suiv)
	{
		ts = (time_t) temp->pnt->id;
		date = *localtime(&ts);
		strftime(buf, sizeof(buf), "%H", &date);
		sscanf(buf,"%d",&heure);
		if(temp->pnt->id_cluster == p_cluster->pnt->id_cluster)
		{
			for (int i = 0; i < taille_tab; ++i)
			{
				if ((heure >= tab[i][0]) && (heure < tab[i][0] +1))
				{
					tab[i][1]++;
				}
			}
		}
	}
	p_cluster->pnt->tab_heure = tab;

	//afficher_tab(tab);
}


int ** fusion_tab_heure(element_liste_point *p1, element_liste_point *p2)
{
	int **tab1,**tab2;

	tab1 = p1->pnt->tab_heure;
	tab2 = p2->pnt->tab_heure;
	int **tab3 = init_tab_heure();

	for (int i = 0; i < taille_tab; ++i)
	{				
		tab3[i][1] = tab1[i][1] + tab2[i][1];	
	
	}
	return tab3;
}



