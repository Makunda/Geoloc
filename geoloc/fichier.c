#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "fichier.h"
#define size_max 4096
#define taille_fichier 50
#define bufsize 50
#define pi 3.14159265358979323846



point *ini_point(char *txt,double eps, element_liste_logs *nom_fichier){
    int i1;
    double i2,i3;
    point *p = malloc(sizeof(point));
    if (p == NULL)
    {
    	printf("Erreur : ini_point \n");
    	exit(EXIT_FAILURE);
    }
    if (3 != sscanf(txt,"%*[^0123456789]%d%*[^0123456789]%lf%*[^0123456789]%lf",&i1,&i2,&i3)) // on extrait les donnees du fichier
    {
    	printf("Erreur lecture : ini_point\n");
        return NULL;
    }
    else {
        p->id=i1;
        p->pos.lat=i2;
        p->pos.lon=i3;
        //printf("%lf lat , %lf lon , id %d\n",p->pos.lat,p->pos.lon,p->id );
        p->id_cluster = -1;
        latLonToXY(p);
        p->effectif = 1;
        p->rayon = 0;
        p->epsilon = eps;
        p->nom_fichier = nom_fichier;
        return p;
        }

}



void read_log(FILE *f, tete_liste_point *pt,double eps, element_liste_logs *nom_fichier)
{
    int i=0;
    char *txt;
    point *temp;
    txt=malloc(size_max*sizeof(char));
    for( ;fscanf(f,"%s",txt) != EOF; ){
    	if( (temp = ini_point(txt,eps,nom_fichier)) != NULL)
    	{
        	ajout_liste(pt,temp);
    	}
        i++;
    }

}


void enregister_log(tete_liste_point *pt, char *nom_fichier)
{
    //ex : date:1477150918,lat:47.080455779512846,long:2.404637457073204;
    element_liste_point *element_parcour = pt->suiv;
    int ret = 0;
    char * nouveau_fichier = malloc(100*sizeof(char));
    sprintf(nouveau_fichier,"%s_anon",nom_fichier);
    FILE *f = fopen(nouveau_fichier,"w");
    for (; element_parcour->suiv != NULL; element_parcour = element_parcour->suiv)
    {   

       fprintf(f,"data:%d,lat:%lf,long:%lf;\n",element_parcour->pnt->id,element_parcour->pnt->pos.lat,element_parcour->pnt->pos.lon);
    }
    free(nouveau_fichier);
    fclose(f);
}
