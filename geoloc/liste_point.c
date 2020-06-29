#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "liste_point.h"



tete_liste_point *init_liste()
{
    tete_liste_point *liste = malloc(sizeof(*liste));
    if(liste == NULL )
    {
        printf("Erreur : Initialisation \n");
        exit(EXIT_FAILURE);
    }
    liste->suiv=NULL;
    liste->taille=0;
    return liste;
}

int liste_vide(tete_liste_point *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : liste_vide \n");
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

element_liste_point *retourner_element_id(tete_liste_point *pt,int a)
{
    if(pt == NULL || a>pt->taille)
    {
        printf("Erreur : retourner_element_id \n");
        exit(EXIT_FAILURE);
    }
    element_liste_point *element_parcour = pt->suiv;
    int i=0;
    while(i!=a)
    {
        element_parcour=element_parcour->suiv;
        i++;
    }
    return element_parcour;
}

void ajout_liste(tete_liste_point *pt, point *pnt)
{
    element_liste_point *nouveau = malloc(sizeof(element_liste_point));
    if(nouveau == NULL || pt == NULL || pnt == NULL)
    {
        printf("Erreur : Ajout_Liste \n");
        exit(EXIT_FAILURE);
    }
    nouveau->pnt=pnt;
    nouveau->suiv = NULL;
    nouveau->prec = NULL;
    if(pt->suiv == NULL)
    {
        pt->suiv = nouveau;
    }
    else
    {
        nouveau->suiv = pt->suiv;
        pt->suiv->prec = nouveau;
        pt->suiv = nouveau;
    }
    pt->taille++;
}

void ajout_liste_tri(tete_liste_point *pt, point *pnt)
{
    if(pt == NULL || pnt == NULL)
    {
        printf("Erreur : Ajout_Liste \n");
        exit(EXIT_FAILURE);
    }
    
    else
    {
    	element_liste_point *p =pt->suiv, *temp =NULL;
    	element_liste_point *nouveau = malloc(sizeof(element_liste_point ));
    	nouveau->pnt = pnt;
    	while((p != NULL)  && (p->pnt->id < pnt->id))
    	{
    		temp = p;
    		p = p->suiv;
    	}

    	if (temp == NULL)
    	{
    		nouveau->prec = NULL;
            nouveau->suiv = pt->suiv;
            pt->suiv = nouveau;
    	}
    	else if (p == NULL)
    	{
    		nouveau->suiv = NULL;
    		nouveau->prec = temp;
    		temp->suiv = nouveau;
    	}
    	else
    	{
    		nouveau->suiv = p;
    		nouveau->prec = temp;
    		p->prec = nouveau;
    		temp->suiv = nouveau;
    	}
    	pt->taille++;    	
    }
}

void ajout_liste_fin(tete_liste_point *pt, point *pnt)
{
    element_liste_point *nouveau = malloc(sizeof(nouveau));
    if(nouveau == NULL || pt == NULL)
    {
        printf("Erreur : Ajout_Liste_fin \n");
        exit(EXIT_FAILURE);
    }
    nouveau->pnt=pnt;
    nouveau->suiv=NULL;
    nouveau->prec = NULL;
    if(pt->suiv == NULL)
    {
        pt->suiv = nouveau;
    }
    else
    {
        element_liste_point *element_parcour = pt->suiv,*temp = NULL;
        while(element_parcour != NULL)
        {
        	temp = element_parcour;
            element_parcour = element_parcour->suiv;
        }
        temp->suiv=nouveau;
        nouveau->prec=temp;
    }
    pt->taille++;
}

int point_egaux(point *a,point *b)
{
    if((a->pos.lat == b->pos.lat)&&(a->pos.lon == b->pos.lon))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int existe_liste(tete_liste_point *pt, point *p)
{
    element_liste_point *element;
    for(element=pt->suiv;element != NULL;element = element->suiv)
    {
        if(point_egaux(element->pnt,p)==1)
        {
            return 1;
        }
    }
    return 0;
}

void liste_union(tete_liste_point *pt1, tete_liste_point *pt2)
{
    element_liste_point *element;
    for(element=pt2->suiv;element != NULL;element = element->suiv)
        if(!existe_liste(pt1,element->pnt))
            ajout_liste_fin(pt1,element->pnt);
}


void supprimer_element(tete_liste_point *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : supprimer_element \n");
    }
    if(pt->suiv != NULL)
    {
        element_liste_point *element_suppr = pt->suiv;
        pt ->suiv = pt->suiv->suiv;
        if (pt->suiv != NULL)
        {
        	pt ->suiv->prec= NULL;
        }
        free(element_suppr);
    }
    pt->taille--;
}

tete_liste_point * supprimer_element_liste(tete_liste_point *pt,element_liste_point *p)
{
	if(p == NULL)
    {
        printf("Erreur : supprimer_element_liste \n");
    }
    if (p->suiv == NULL &&  p->prec == NULL)
    {
    	pt->suiv = NULL;
    }
    if(p->suiv == NULL && p->prec != NULL)
    {
    	p->prec->suiv = NULL;
    }
    if ( p->prec == NULL && p->suiv != NULL)
    {
    	pt->suiv = p->suiv;
    	pt->suiv->prec = NULL;
    }
    if( p->suiv != NULL &&  p->prec != NULL)
    {
    	p->suiv->prec = p->prec;
    	p->prec->suiv = p->suiv;
    }
    free(p);
    pt->taille--;
    return pt;
}

void afficher_liste_console(tete_liste_point *pt)
{
	if (pt->suiv == NULL)
	{
		printf("liste vide : afficher_liste_console\n");
	}
	element_liste_point *element_parcour = pt->suiv;
	for (element_parcour = pt->suiv;element_parcour != NULL; element_parcour = element_parcour->suiv)
	{
		printf("|<-prec : %p |%p| suiv-> : %p | ",element_parcour->prec,element_parcour,element_parcour->suiv);
		printf("\n");
		
	}
	detecter_erreur(pt);
	
}

void detecter_erreur(tete_liste_point *pt)
{
	element_liste_point *element_parcour = pt->suiv;
	for (element_parcour = pt->suiv;element_parcour != NULL; element_parcour = element_parcour->suiv)
	{
		printf("%p adresse de pnt \n",element_parcour->pnt);
		
	}
}

void afficher_liste(tete_liste_point *pt,FILE *f1)
{
    if(pt == NULL)
    {
        printf("Erreur : afficher_liste \n");
        exit(EXIT_FAILURE);
    }
    element_liste_point *element_parcour = pt->suiv;
    while(element_parcour != NULL)
    {
        fprintf(f1, "[%d] lon : %8.8lf lat : %8.8lf id_cluster : %d effectif : %d rayon : %lf \n ",element_parcour->pnt->id,element_parcour->pnt->pos.lon,element_parcour->pnt->pos.lat,element_parcour->pnt->id_cluster,element_parcour->pnt->effectif,element_parcour->pnt->rayon);
        //printf("[%d] lon : %8.8lf lat : %8.8lf id_cluster : %d effectif : %d rayon : %lf fichier : %s \n ",element_parcour->pnt->id,element_parcour->pnt->pos.lon,element_parcour->pnt->pos.lat,element_parcour->pnt->id_cluster,element_parcour->pnt->effectif,element_parcour->pnt->rayon,element_parcour->pnt->nom_fichier);
        element_parcour=element_parcour->suiv;
    }
}
void vider_liste(tete_liste_point *pt)
{
    if(pt==NULL)
    {
        printf("Erreur vider_liste \n");
        exit(EXIT_FAILURE);
    }
    while(pt->suiv!=NULL)
    {
        supprimer_element_liste(pt,pt->suiv);
    }
}




