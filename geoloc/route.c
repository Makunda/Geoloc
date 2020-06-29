#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "structure.h"
#include "fichier.h"
#include "liste_point.h"
#include "cluster.h"
#include "graphic.h"

tete_liste_route *init_liste_route()
{
    tete_liste_route *liste = malloc(sizeof(*liste));
    if(liste == NULL )
    {
        printf("Erreur : Initialisation \n");
        exit(EXIT_FAILURE);
    }
    liste->suiv=NULL;
    liste->taille=0;
    return liste;
}

int liste_vide_route(tete_liste_route *pt)
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

void ajout_liste_route(tete_liste_route *pt, route r)
{
    element_liste_route *nouveau = malloc(sizeof(element_liste_route));
    if(nouveau == NULL || pt == NULL)
    {
        printf("Erreur : ajout_liste_route \n");
        exit(EXIT_FAILURE);
    }
    nouveau->r=r;
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

void supprimer_element_route(tete_liste_route *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : supprimer_element \n");
        exit(EXIT_FAILURE);
    }
    if(pt->suiv != NULL)
    {
        element_liste_route *element_suppr = pt->suiv;
        pt ->suiv = pt->suiv->suiv;
        if (pt->suiv != NULL)
        {
            pt ->suiv->prec= NULL;
        }
        free(element_suppr);
    }
    pt->taille--;
}

void supprimer_route(tete_liste_point *pt, route r)
{
    //vider_liste(r.liste_point_route);
    element_liste_point *elem1 = pt->suiv, *elem2 = r.liste_point_route->suiv;
    for (;elem2 != NULL;elem2 = elem2->suiv)
    {
        for (elem1 = pt->suiv;elem1 != NULL;elem1 = elem1->suiv)
        {
            if(point_egaux(elem2->pnt,elem1->pnt))
                supprimer_element_liste(pt,elem1);
        }
    }
    

}

tete_liste_route * supprimer_element_route_liste(tete_liste_route *pt, element_liste_route *p)
{
    if(p == NULL)
    {
        printf("Erreur : supprimer_element_route_liste \n");
        exit(EXIT_FAILURE);
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



void vider_liste_route(tete_liste_route *pt)
{
    if(pt==NULL)
    {
        printf("Erreur vider_liste \n");
        exit(EXIT_FAILURE);
    }
    while(pt->suiv!=NULL)
    {
        supprimer_element_route(pt);
    }
}

tete_liste_route *route_cluster(tete_liste_point *pt)
{
	tete_liste_route *liste_retour = init_liste_route();
    int id_cluster = -1;
    int boleon =1;
    element_liste_point *element = pt->suiv,*temp;
    while(element != NULL)
    {
    	if(element->pnt->id_cluster == -2)
    	{
    		while((element!= NULL) && (element->suiv->pnt->id_cluster != -2))
    		{
    			element= element->suiv;
    		}
       	}

    	if(element->suiv != NULL)
    	{
    		route route_point_cluster;
    		tete_liste_point *liste_point_route = init_liste();
    		route_point_cluster.p_debut = element->pnt;
            route_point_cluster.id_cluster_debut = element->pnt->id_cluster;  
    		for(;(element->suiv != NULL) && (element->pnt->id_cluster == -2);element = element->suiv)
    		{
    			ajout_liste(liste_point_route,element->pnt);
    		}
    		route_point_cluster.p_fin = element->pnt;
            route_point_cluster.id_cluster_fin = element->pnt->id_cluster;
    		route_point_cluster.color.r = element->pnt->color.r;
			route_point_cluster.color.g = element->pnt->color.g;
			route_point_cluster.color.b = element->pnt->color.b;
			
			if(liste_point_route->taille == 0) // cluster trop proche
			{
				vider_liste(liste_point_route);
                free(liste_point_route);
			}
			else
			{
                route_point_cluster.liste_point_route = liste_point_route;
				ajout_liste_route(liste_retour,route_point_cluster);
			}
    	}
    	
		element = element->suiv;
		
    }
    return liste_retour;
}