#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "fichier.h"
#include "structure.h"
#include "liste_point.h"
#include "logs.h"
#include "route.h"
#include "stats.h"

#define NONVISITE -1
#define BRUIT -2
#define size_malloc 30

int randab(int a, int b)
{
    return rand()%(b-a) +a;
}

droite_affine calc_perpendiculaire(point p1,point p2)
{
    droite_affine droite;
    droite.a= (p2.pos.lat - p1.pos.lat)/(p2.pos.lon - p1.pos.lon);
    droite.a= -1/droite.a;
    coordonnee point_millieu;
    point_millieu.lon = (p1.pos.lon + p2.pos.lon)/2;
    point_millieu.lat = (p1.pos.lat + p2.pos.lat)/2;
    droite.b = point_millieu.lat - (droite.a)*point_millieu.lon;
    return droite;
}

coordonnee moyenne_position(tete_liste_point *pt)
{
    coordonnee retour_coordonnee;
    double somme_lat =0, somme_lon =0;
    element_liste_point *elem_parcour;
    elem_parcour = pt->suiv;
    while(elem_parcour != NULL)
    {
        somme_lat+=elem_parcour->pnt->pos.lat;
        somme_lon+=elem_parcour->pnt->pos.lon;
        elem_parcour=elem_parcour->suiv;
    }
    somme_lat/=pt->taille;
    somme_lon/=pt->taille;
    retour_coordonnee.lon = somme_lon;
    retour_coordonnee.lat = somme_lat;
    return retour_coordonnee;
}

int lister_nombre_cluster(tete_liste_point *pt)
{
    int temp = 0;
    element_liste_point *element_parcour = pt->suiv;
    while(element_parcour != NULL)
    {
        if(element_parcour->pnt->id_cluster > temp)
        {
            temp = element_parcour->pnt->id_cluster;
        }
        element_parcour = element_parcour->suiv;
    }
    return temp;
} 

tete_liste_point *lister_cluster(tete_liste_point *pt)
{
    tete_liste_point *liste_retour = init_liste();
    int i = 0;
    int nombre_cluster = lister_nombre_cluster(pt);
    for(i=0;i< nombre_cluster;i++)
    {
        tete_liste_point *liste_point_temp = init_liste();
        element_liste_point *element_parcour;
        for(element_parcour = pt->suiv;element_parcour != NULL; element_parcour=element_parcour->suiv)
        {

            if(element_parcour->pnt->id_cluster == i)
            {
                ajout_liste(liste_point_temp,element_parcour->pnt);
            }
        }
        point *p_insert = malloc(sizeof(point));
        p_insert->id = 0;
        p_insert->id_cluster = i;
        p_insert->pos = moyenne_position(liste_point_temp);
        p_insert->effectif = liste_point_temp->taille;
        p_insert->epsilon = 0;
        p_insert->color.r = 0;
        p_insert->color.g = 0;
        p_insert->color.b = 0;
        latLonToXY(p_insert);
        double rayon =0,temp =0;
        for(element_parcour = liste_point_temp->suiv;element_parcour != NULL; element_parcour=element_parcour->suiv)
        {
            if((temp = calcul_distance(p_insert,element_parcour->pnt)) >= rayon)
            {
                rayon = temp;
                p_insert->rayon = calcul_distance_pixel(p_insert,element_parcour->pnt);
            }
        }
        ajout_liste(liste_retour,p_insert);
        vider_liste(liste_point_temp);
        free(liste_point_temp);
    }
    return liste_retour;
}

void nettoyer_cluster(tete_liste_point *pt,int MinPoint)
{
    element_liste_point *element_parcour = pt->suiv;
    while(element_parcour != NULL)
    {
        if(element_parcour->pnt->effectif < MinPoint)
        {
            pt = supprimer_element_liste(pt,element_parcour);
        }
        element_parcour = element_parcour->suiv;
    }
}


tete_liste_point *retourner_epsilon_voisins(tete_liste_point *pt,element_liste_point *p,double epsilon)
{
    element_liste_point *element_parcour = pt->suiv;
    tete_liste_point *liste_retour=init_liste();
    for(element_parcour=pt->suiv; element_parcour!=NULL; element_parcour=element_parcour->suiv)
    {
        if(element_parcour->pnt->id_cluster != BRUIT)
        {
            if (point_egaux(p->pnt,element_parcour->pnt) == 1)
                continue;
            else if (calcul_distance(element_parcour->pnt,p->pnt) > epsilon)
                continue;
            else
            {
            ajout_liste(liste_retour,element_parcour->pnt);
            }
        }
        
    }
    return liste_retour;
}

void etendre_cluster(tete_liste_point *pt,element_liste_point *p,tete_liste_point *epsilon_voisins, int id_cluster,double eps, int minPoint)
{
    p->pnt->id_cluster = id_cluster;
    element_liste_point *element_parcour;
    for(element_parcour=epsilon_voisins->suiv; element_parcour!=NULL; element_parcour=element_parcour->suiv)
    {
        if(element_parcour->pnt->id_cluster == NONVISITE)
        {
            tete_liste_point *epsilon_voisins_bis = retourner_epsilon_voisins(pt,element_parcour,eps);
            if(epsilon_voisins_bis->taille >= minPoint)
            {
                liste_union(epsilon_voisins,epsilon_voisins_bis);
            }
            else
            {
                element_parcour->pnt->id_cluster == BRUIT;
            }
            element_parcour->pnt->id_cluster = id_cluster;
            free(epsilon_voisins_bis);
        }
        

    }

}



int DBSCAN(tete_liste_point *pt,double epsilon, int MinPoint)
{
    int id_cluster = 0;
    element_liste_point *element_parcour = pt->suiv;
    for(element_parcour=pt->suiv; element_parcour!=NULL; element_parcour=element_parcour->suiv)
    {
        if(element_parcour->pnt->id_cluster == NONVISITE)
        {
            element_parcour->pnt->id_cluster = 0;
            tete_liste_point *pt_voisin = retourner_epsilon_voisins(pt,element_parcour,epsilon);
            if(pt_voisin->taille < MinPoint)
            {
                element_parcour->pnt->id_cluster = BRUIT;
            }
            else
            {
                etendre_cluster(pt,element_parcour,pt_voisin,id_cluster,epsilon,MinPoint);
                id_cluster ++;
            }

        }
    }
    return id_cluster;

}




void caculer_couleur(tete_liste_point *pt,int interval)
{
    element_liste_point *element_parcour = pt->suiv;
    for(; element_parcour!=NULL; element_parcour=element_parcour->suiv)
    {
        if(element_parcour->pnt->id_cluster == -2)
        {
            //printf("ON COLORISE PAS \n");
            element_parcour->pnt->color.r = 0;
        element_parcour->pnt->color.g = 0;
        element_parcour->pnt->color.b = 0;
        }
        else
        {

            int value = element_parcour->pnt->id_cluster;
        int x = (1530/interval)*value;
    int r;
    int g;
    int b;
    if(x>=0 && x<255){
    r = 255;
    g = x;
    b = 0;
    }
    if(x>=255 && x<510){
    r = 510-x;
    g = 255;
    b = 0;
    }
    if(x>=510 && x<765){
    r = 0;
    g = 255;
    b = x-510;
    }
    if(x>=765 && x<1020){
    r = 0;
    g = 1020-x;
    b = 255;
    }
    if(x>=1020 && x<1275){
    r = x-1020;
    g = 0;
    b = 255;
    }
    if(x>=1275 && x<=1530){
    r = 255;
    g = 0;
    b = 1530-x;
    }
    element_parcour->pnt->color.r = r;
    element_parcour->pnt->color.g = g;
    element_parcour->pnt->color.b = b;
    //printf("ON COLORISE (%d,%d,%d) \n",r,g,b);
    }
        }
}

point_ign *malloc_point(){
    point_ign *p = malloc(sizeof(*p));
    p->id = malloc(size_malloc*sizeof(char));
    p->id_tr = malloc(size_malloc*sizeof(char));
    p->methode= malloc(size_malloc*sizeof(char));
    p->num = malloc(size_malloc*sizeof(char));
    p->rep = malloc(size_malloc*sizeof(char));
    p->comp = malloc(size_malloc*sizeof(char));
    p->nom_voie = malloc(size_malloc*sizeof(char));
    p->alias = malloc(size_malloc*sizeof(char));
    p->nom_ld = malloc(size_malloc*sizeof(char));
    p->code_insee = malloc(size_malloc*sizeof(char));
    p->code_postal = malloc(size_malloc*sizeof(char));
    p->type_loc = malloc(size_malloc*sizeof(char));
    p->cote = malloc(size_malloc*sizeof(char));
    return p;
}

void cluster_base_ign(tete_liste_point *pt_cluster, FILE *f_index, FILE *f_traitement)
{
    int numero,ligne,effectif;
    char *txt = malloc(100*sizeof(char));
	char *temp = malloc(100*sizeof(char));
	char *temp_x = malloc(50*sizeof(char));
	char *temp_y = malloc(50*sizeof(char));
	size_t taille_temp = sizeof(temp);
	size_t taille = sizeof(txt);
	int i,i2;
	element_liste_point *element_parcour;
	double distance_min,xmin,xmax,ymin,ymax;
	point_ign *p = malloc_point();
    printf("Taille du cluster : %i\n", pt_cluster->taille);
	for (element_parcour = pt_cluster->suiv; element_parcour != NULL; element_parcour = element_parcour->suiv)
	{
		distance_min = 999999999999999;
		fseek(f_index, 0, SEEK_SET);
    	while ((getline (&txt,&taille,f_index)) != -1) {
    		//printf("on check la boucle du cluster: %d \n",element_parcour->pnt->id_cluster);
    		//printf("txt = %s\n",txt);
        	if( 7 != sscanf(txt,"%d;%lf;%lf;%lf;%lf;%d;%d",&numero,&xmin,&xmax,&ymin,&ymax,&ligne,&effectif))
    		{
    			printf("Erreur : cluster_base_ign\n");
    			exit(EXIT_FAILURE);
    		}
    		                if((element_parcour->pnt->pos.lon < xmax) && (element_parcour->pnt->pos.lon >= xmin) && (element_parcour->pnt->pos.lat < ymax) && (element_parcour->pnt->pos.lat >= ymin))
    		                {
    		                	if (effectif == 0)
    		                	{
    		                		break;
    		                	}
    		                	else
    		                	{
    		                		fseek(f_traitement, 0, SEEK_SET);
    		                		getline (&temp,&taille_temp,f_traitement);
    		                		for (i = 0; i <= ligne; ++i) // on saute les lignes inutiles
    		                		{
    		                			if( getline (&temp,&taille_temp,f_traitement) == -1 )
    		                			{
    		                				break;
    		                			}
    		                		}
    		                		for (i2 = 0; i2 <=effectif; ++i2) // on parcourt les points possibles
    		                		{
    		                			int ret =0;
    		                			if(getline (&temp,&taille_temp,f_traitement) == -1)
    		                			{
    		                				break;
    		                			}
    		                			point_ign *p_fin = malloc_point();
    									if (15 != (ret = sscanf(temp,"%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];",p->id,p->id_tr,p->methode,p->num,p->rep,p->comp,p->nom_voie,p->alias,p->nom_ld,p->code_insee,p->code_postal,p->type_loc,p->cote,temp_x,temp_y)))
    									{
    										printf("%s\n", temp);
        									printf("Erreur lecture fichier \n");
								    	}
								    	p->pos.lon = atof(temp_x);
								    	p->pos.lat = atof(temp_y);
								    	
								    	//printf("lon : % lf lat % lf \n",p->pos.lon,p->pos.lat );
								    	//printf("distance_coordonee = %lf , distance = %lf \n",calcul_distance_coordonne( p->pos, element_parcour->pnt->pos),distance_min);
    		                			if (calcul_distance_coordonne( p->pos, element_parcour->pnt->pos) <= distance_min)
    		                			{
    		                				//printf("distance_min = %lf\n",distance_min);
    		                				sscanf(temp,"%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];",p_fin->id,p_fin->id_tr,p_fin->methode,p_fin->num,p_fin->rep,p_fin->comp,p_fin->nom_voie,p_fin->alias,p_fin->nom_ld,p_fin->code_insee,p_fin->code_postal,p_fin->type_loc,p_fin->cote,temp_x,temp_y);
    		                				distance_min = calcul_distance_coordonne( p->pos, element_parcour->pnt->pos);
    		                				p_fin->pos.lon = atof(temp_x);
								    		p_fin->pos.lat = atof(temp_y);
    		                				element_parcour->pnt->ign = p_fin;
    		                			}
    		                			
    		                		}
    		                		printf("Cluster %d situe a : %s IGN \n",element_parcour->pnt->id_cluster,element_parcour->pnt->ign->nom_voie);

    		                		
    		                	}
    		                	break;
    		                }
    	}
	}
	

}

void supprimer_cluster(element_liste_logs *element, element_liste_point * cluster)
{
	element_liste_route *element_parcour_route = element->pt_route->suiv,*temp2;
    while(element_parcour_route != NULL)
    {
        if((element_parcour_route->r.p_debut->id_cluster == cluster->pnt->id_cluster) || (element_parcour_route->r.p_fin->id_cluster == cluster->pnt->id_cluster))
        {
            //temp2 = element_parcour_route->suiv;
            supprimer_route(element->pt,element_parcour_route->r);
            //element->pt_route = supprimer_element_route_liste(element->pt_route,element_parcour_route);
            //element_parcour_route = temp2;
        }
        element_parcour_route = element_parcour_route->suiv;
    }
    element_liste_point *element_parcour = element->pt->suiv,*temp;
    element_parcour = element->pt->suiv;
    while(element_parcour != NULL )
    {
    	//printf("id cluster %d\n", cluster->pnt->id_cluster);
        if(element_parcour->pnt->id_cluster == cluster->pnt->id_cluster)
        {
        	temp = element_parcour->suiv;
            element->pt = supprimer_element_liste(element->pt,element_parcour);
            element_parcour = temp;

        }
        else
        {
        	element_parcour = element_parcour->suiv;
        }
    }
    supprimer_element_liste(element->pt_cluster,cluster);
   	enregister_log(element->pt,element->id);
    

}

int cluster_superpose(element_liste_point *c1, element_liste_point *c2)
{
	if ((c1->pnt->rayon + c2->pnt->rayon) >= calcul_distance_pixel(c1->pnt,c2->pnt))
	{
		return 1;
	}
	return 0;
}

element_liste_point * fusion_cluster(element_liste_point *c1, element_liste_point *c2)
{
	element_liste_point *nouveau = malloc(sizeof(element_liste_point));
	point *p = malloc(sizeof(point));
	p->tab_heure = fusion_tab_heure(c1,c2);
	p->id_cluster = 0;
	p->pos.lon = ( c1->pnt->pos.lon + c2->pnt->pos.lon ) /2;
	p->pos.lat = ( c1->pnt->pos.lat + c2->pnt->pos.lat ) /2;
	latLonToXY(p);
	p->effectif = c1->pnt->effectif + c2->pnt->effectif;
	if (c1->pnt->rayon >= c2->pnt->rayon )
	{
		p->rayon = c1->pnt->rayon;
		p->color = c1->pnt->color;
	}
	else
	{
		p->rayon = c2->pnt->rayon;
		p->color = c2->pnt->color;
	}
	p->epsilon = c1->pnt->epsilon;
    printf("%i\n", p->id_cluster);
    p->id_cluster = -3;
	nouveau->pnt = p;
	return nouveau;
}

tete_liste_point *init_liste_temporelle_cluster(tete_liste_logs *pt_logs)
{
	tete_liste_point *liste_retour = init_liste();
	int insert = 0;
	//
	element_liste_logs *element_parcour = pt_logs->suiv;
	element_liste_point *element_parcour_cluster,*element_parcour_cluster2,*temp;
	for (; element_parcour != NULL; element_parcour = element_parcour->suiv)
	{
		for (element_parcour_cluster = element_parcour->pt_cluster->suiv; element_parcour_cluster != NULL; element_parcour_cluster = element_parcour_cluster->suiv)
		{
			insert = 0;
            element_parcour_cluster->pnt->nom_fichier = element_parcour;
			for (element_parcour_cluster2 = liste_retour->suiv; element_parcour_cluster2 != NULL; element_parcour_cluster2 = element_parcour_cluster2->suiv)
			{
				if(cluster_superpose(element_parcour_cluster,element_parcour_cluster2))
				{
					temp = element_parcour_cluster2 ;
					element_parcour_cluster2 = fusion_cluster(element_parcour_cluster,element_parcour_cluster2);
					element_parcour_cluster2->suiv = temp->suiv;
					element_parcour_cluster2->prec = temp->prec;
					insert = 1;	
				}
			}
			if (insert == 0)
			{
				ajout_liste(liste_retour,element_parcour_cluster->pnt);
			}
		}
	}
	return liste_retour;
	
}


