#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include "structure.h"
#include "fichier.h"
#include "liste_point.h"
#include "cluster.h"
#include "graphic.h"
#include "route.h"
#include "logs.h"
#include "stats.h"


#define max_logs 100
#define epsilon 0.000300
#define MinPoint 7

tete_liste_logs *init_liste_logs()
{
    tete_liste_logs *liste = malloc(sizeof(*liste));
    if(liste == NULL )
    {
        printf("Erreur : Initialisation \n");
        exit(EXIT_FAILURE);
    }
    liste->suiv=NULL;
    liste->taille=0;
    return liste;
}

int liste_vide_logs(tete_liste_logs *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : liste_vide_logs \n");
        exit(EXIT_FAILURE);
    }
    if(pt->suiv==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

element_liste_logs *init_element_log(FILE *fichier_log, char* id, tete_liste_point *pt, tete_liste_point *pt_cluster, tete_liste_route *pt_route, couleur color)
{
	element_liste_logs *nouveau = malloc(sizeof(*nouveau));
	nouveau->fichier_log = fichier_log;
	nouveau->id = id;
	nouveau->pt = pt;
	nouveau->pt_cluster = pt_cluster;
	nouveau->pt_route = pt_route;
    nouveau->color = color;
	return nouveau;
}

void ajout_liste_logs(tete_liste_logs *pt,element_liste_logs *nouveau)
{
    
    if(nouveau == NULL || pt == NULL)
    {
        printf("Erreur : Ajout_Liste_logs \n");
        exit(EXIT_FAILURE);
    }
    nouveau->suiv = pt->suiv;
    pt->suiv=nouveau;
    pt->taille++;
}

void supprimer_element_logs(tete_liste_logs *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : supprimer_element_logs \n");
        exit(EXIT_FAILURE);
    }
    if(pt->suiv != NULL)
    {
        element_liste_logs *element_suppr = pt->suiv;
        pt->suiv = pt->suiv->suiv;
        free(element_suppr);
    }
    pt->taille--;
}


void supprimer_element_logs_liste(tete_liste_logs *pt, element_liste_logs *p)
{
    if(p == NULL)
    {
        printf("Erreur : supprimer_element_logs_liste \n");
        exit(EXIT_FAILURE);
    }
    element_liste_logs *temp;
    if(pt->suiv == p)
    {
    	pt->suiv=pt->suiv->suiv;
    }
    else
    {
    	while(temp->suiv != NULL)
    	{
    		if(temp->suiv == p)
    		{
    			temp->suiv = temp->suiv->suiv;
    		}
    		temp =temp->suiv;
    	}
    }
    
    vider_liste(p->pt);
    vider_liste(p->pt_cluster);
    vider_liste_route(p->pt_route);
    free(p);
    pt->taille--;
}



void vider_liste_logs(tete_liste_logs *pt)
{
    if(pt==NULL)
    {
        printf("Erreur vider_liste_logs \n");
        exit(EXIT_FAILURE);
    }
    while(pt->suiv!=NULL)
    {
        supprimer_element_logs(pt);
    }
}

element_liste_logs * main_logs(char *path_fichier, char *nom_fichier)
{
	if(nom_fichier != NULL)
	{
		printf("main_logs pour %s\n",path_fichier);
		element_liste_logs *element_retour;
		FILE *f;
		tete_liste_point *pt;
    	tete_liste_point *pt_cluster;
    	tete_liste_route *pt_route;
    	pt = init_liste();
    	// on ouvre le fichier log
    	f = fopen(path_fichier,"r");
    	if(f==NULL)
    	{
    		printf("%s : ",path_fichier);
        	perror("Erreur ouverture fichier ");
        	exit(EXIT_FAILURE);
    	}
    	// on ouvre le traitement
    	FILE *f_index, *f_traitement;
		f_traitement = fopen("traitement.bin","r");
		f_index = fopen("index_traitement.bin","r");
		if((f_index == NULL) || (f_traitement ==NULL))
		{
			printf("Erreur ouverture traitement.bin et index_traitement\n");
			exit(EXIT_FAILURE);
		}
    	element_retour = init_element_log(f,nom_fichier,pt,pt_cluster,pt_route, randomCouleur());
		read_log(f,pt,epsilon,element_retour);
		printf("Taille Liste %d\n",pt->taille);
		if (pt->suiv == NULL)
		{
			printf("Fichier vide : INTERRUPTION \n");
			fclose(f);
    		fclose(f_index);
    		fclose(f_traitement);
			return NULL;
		}
        DBSCAN(pt,epsilon,MinPoint);
        pt_cluster = lister_cluster(pt);
        nettoyer_cluster(pt_cluster,MinPoint);
        pt_route = route_cluster(pt);
        cluster_base_ign(pt_cluster,f_index,f_traitement);
        element_retour->pt = pt;
        element_retour->pt_cluster = pt_cluster;
        element_retour->pt_route = pt_route;
    	//init_element_log(FILE *fichier_log, char* id, tete_liste_point *pt, tete_liste_point *pt_cluster, tete_liste_route *pt_route)
    	fclose(f);
    	fclose(f_index);
    	fclose(f_traitement);
    	return element_retour;
	}
	
}

tete_liste_point *init_liste_temporelle(tete_liste_logs *pt_logs)
{
    tete_liste_point *liste_temporelle = init_liste();
    element_liste_logs *element_parcour;
    for (element_parcour = pt_logs->suiv;element_parcour != NULL;element_parcour = element_parcour->suiv)   
    {
        element_liste_point *element_parcour2;
        for (element_parcour2 = element_parcour->pt->suiv; element_parcour2->suiv != NULL; element_parcour2 = element_parcour2 -> suiv)   
        {
            ajout_liste_tri(liste_temporelle, element_parcour2->pnt);
        }
    }
    FILE *f1;
    f1 = fopen("test","w+");
    //afficher_liste(liste_temporelle,f1);
    return liste_temporelle;

}

tete_liste_logs *insertion_logs()
{
	tete_liste_logs *liste_retour = init_liste_logs();
	char **tableau_fichier = malloc(max_logs*sizeof(char*));
	char **tableau_FILE = malloc(max_logs*sizeof(char*));
	tete_liste_logs *pt_logs = init_liste_logs();
	//ici on entre à la main, à supprimer 
	int i =0;
	/////////////////////////////////////////////////////////
	// OUVERTURE DES LOGS DU DOSSIER LOGS                 //
	////////////////////////////////////////////////////////
	DIR* rep = NULL;
    rep = opendir("../logs");
    int nbr = 0;
    struct dirent* ent = NULL;
    while ((ent = readdir(rep)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && /* Si le fichier lu n'est pas . */
            strcmp(ent->d_name, "..") != 0)
            {	
            	char *nom_logs = malloc(50*sizeof(char));
            	strcpy(nom_logs,"../logs/");
				strcat(nom_logs,ent->d_name);
				tableau_fichier[nbr] = nom_logs;
				printf("%s\n",ent->d_name);
				printf("%s\n",nom_logs );
				tableau_FILE[nbr] = nom_logs;
				nbr ++;
            } 
    }
    tableau_fichier[nbr] = NULL; // dernier element 
    tableau_FILE[nbr] = NULL;
	for (int y = 0;((y+1 < 50) && (tableau_fichier[y] != NULL )); ++y)
	{
		element_liste_logs *element_retour = main_logs(tableau_FILE[y],tableau_fichier[y]);
		if (element_retour != NULL)
		{
			ajout_liste_logs(liste_retour,element_retour);
		}	
	}
    remplir_tab_heure_logs(liste_retour);

	return liste_retour;
	
}

couleur randomCouleur()
{
    couleur randomCouleur;
    randomCouleur.r = rand() % 256;
    randomCouleur.g = rand() % 256;
    randomCouleur.b = rand() % 256;
    return randomCouleur;
}

