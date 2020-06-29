#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "read_log.h"
#include "liste_point.h"
#include "conversion.h"


tete_liste_point_ign *init_liste_ign()
{
    tete_liste_point_ign *liste = malloc(sizeof(*liste));
    if(liste == NULL )
    {
        printf("Erreur : tete_liste_point_ign \n");
        exit(EXIT_FAILURE);
    }
    liste->suiv=NULL;
    liste->taille=0;
    return liste;
}

int liste_vide_ign(tete_liste_point_ign *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : liste_vide_ign \n");
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

element_liste_point_ign *retourner_element_id_ign(tete_liste_point_ign *pt,int a)
{
    if(pt == NULL || a>pt->taille)
    {
        printf("Erreur : retourner_element_id_ign \n");
        exit(EXIT_FAILURE);
    }
    element_liste_point_ign *element_parcour = pt->suiv;
    int i=0;
    while(i!=a)
    {
        element_parcour=element_parcour->suiv;
        i++;
    }
    return element_parcour;
}

void ajout_liste_ign(tete_liste_point_ign *pt, point_ign *pnt)
{
    element_liste_point_ign *nouveau = malloc(sizeof(*nouveau));
    if(nouveau == NULL || pt == NULL)
    {
        printf("Erreur : ajout_liste_ign \n");
        exit(EXIT_FAILURE);
    }
    nouveau->pnt=pnt;
    nouveau->suiv=pt->suiv;
    pt->suiv=nouveau;
    pt->taille++;
}

void supprimer_element_ign(tete_liste_point_ign *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : supprimer_element_ign \n");
    }
    if(pt->suiv != NULL)
    {
        element_liste_point_ign *element_suppr = pt->suiv;
        pt ->suiv = pt->suiv->suiv;
        free(element_suppr);
    }
    pt->taille--;
}

void afficher_liste_ign(tete_liste_point_ign *pt)
{
    if(pt == NULL)
    {
        printf("Erreur : afficher_liste_ign \n");
        exit(EXIT_FAILURE);
    }
    element_liste_point_ign *element_parcour = pt->suiv;
    while(element_parcour != NULL)
    {
        //completer
        element_parcour=element_parcour->suiv;
    }
}

void vider_liste_ign(tete_liste_point_ign *pt)
{
    if(pt==NULL)
    {
        printf("Erreur vider_liste_ign \n");
        exit(EXIT_FAILURE);
    }
    while(pt->suiv!=NULL)
    {
        supprimer_element_ign(pt);
    }
}

coor_tableau definir_taille_tableau(tete_liste_point_ign *pt)
{
    if(liste_vide_ign(pt))
    {
        printf("Erreur : definir_taille_tableau (taille NULL)\n");
        exit(EXIT_FAILURE);
    }
    element_liste_point_ign *element_parcour = pt->suiv;
    double h = element_parcour->pnt->pos.lat;
    double d = element_parcour->pnt->pos.lon;
    double b = element_parcour->pnt->pos.lat;
    double g = element_parcour->pnt->pos.lon;
    for(element_parcour = element_parcour->suiv;element_parcour != NULL; element_parcour = element_parcour -> suiv)
    {
        if(element_parcour->pnt->pos.lat > h)
        {
            h = element_parcour->pnt->pos.lat;
        }
        if(element_parcour->pnt->pos.lat < b)
        {
            b = element_parcour->pnt->pos.lat;
        }
        if(element_parcour->pnt->pos.lon > d)
        {
            d = element_parcour->pnt->pos.lon;
        }
        if(element_parcour->pnt->pos.lon < g)
        {
            g = element_parcour->pnt->pos.lon;
        }

    }
    //printf("coordonnee max h : %lf b : %lf d : %lf g : %lf \n",h,b,d,g);
    coor_tableau coor_return;
    coordonnee temp;
    temp.lon = g;
    temp.lat = h;
    coor_return.haut_gauche = temp;
    temp.lon = d;
    temp.lat = h;
    coor_return.haut_droite = temp;
    temp.lon = g;
    temp.lat = b;
    coor_return.bas_gauche = temp;
    temp.lon = d;
    temp.lat = b;
    coor_return.bas_droit = temp;
    return coor_return; 
}

void traitement_texte(tete_liste_point_ign *pt, coor_tableau c)
{
    FILE *f,*f2;
    int n = 30;
    zone tab[n][n];
    int cont = 0;
    int effectif= 0;
    f = fopen("../geoloc/index_traitement.bin","w+");
    f2 = fopen("../geoloc/traitement.bin","w+");
    double max_longueur = (c.haut_droite.lon - c.haut_gauche.lon);
    double max_hauteur = (c.haut_gauche.lat - c.bas_gauche.lat);
    printf("Max longeur %lf Max hauteur %lf \n",max_longueur,max_hauteur);
    double nieme_longeur = (max_longueur)/n;
    double nieme_hauteur = (max_hauteur)/n;
    printf("niem longeur %lf nieme hauteur %lf \n",nieme_longeur,nieme_hauteur);
    element_liste_point_ign *element_parcour;
    int i1,y1;
    double i=c.bas_gauche.lon + nieme_longeur,y=c.bas_gauche.lat + nieme_hauteur;
    int ligne = 1;
    int id_zone = 0;
    fprintf(f2,"id;lon;lat;id_ign;id_tr;methode;num;rep;comp;nom_voie;alias;nom_ld;code_insee;code_postal;type_loc;cote;x;y;\n");
    for(i1 =0; i1 <n; i1++)
    {     
        y=c.bas_gauche.lat + nieme_hauteur;
        for(y1 =0; y1 <n; y1++)
        {
            zone zone_temp;
            zone_temp.id_zone = id_zone;
            zone_temp.ligne =ligne;
            zone_temp.liste_point = init_liste_ign();
            id_zone ++;
            element_parcour = pt->suiv;
            effectif = 0;
            for(;element_parcour != NULL;element_parcour = element_parcour->suiv)
            {
                //printf("%lf %lf point num : %s \n",element_parcour->pnt->pos.lon,element_parcour->pnt->pos.lat,element_parcour->pnt->id);
                if((element_parcour->pnt->pos.lon < i) && (element_parcour->pnt->pos.lon >= i - nieme_longeur) && (element_parcour->pnt->pos.lat < y) && (element_parcour->pnt->pos.lat >= y - nieme_hauteur))
                {
                cont ++;
                effectif++;
                ajout_liste_ign(zone_temp.liste_point,element_parcour->pnt);
                fprintf(f2,"%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%s ;%lf ;%lf ;\n",element_parcour->pnt->id,element_parcour->pnt->id_tr,element_parcour->pnt->methode,element_parcour->pnt->num,element_parcour->pnt->rep,element_parcour->pnt->comp,element_parcour->pnt->nom_voie,element_parcour->pnt->alias,element_parcour->pnt->nom_ld,element_parcour->pnt->code_insee,element_parcour->pnt->code_postal,element_parcour->pnt->type_loc,element_parcour->pnt->cote,element_parcour->pnt->pos.lon,element_parcour->pnt->pos.lat);
                }
            }
            ligne += 0 + zone_temp.liste_point->taille; 
            zone_temp.pos.haut_gauche = ToCoordonnee(i - nieme_longeur, y - nieme_hauteur);
            zone_temp.pos.haut_droite = ToCoordonnee(i , y - nieme_hauteur);
            zone_temp.pos.bas_gauche = ToCoordonnee(i - nieme_longeur, y);
            zone_temp.pos.bas_droit = ToCoordonnee(i,y); 
            zone_temp.effectif = effectif;
            tab[i1][y1] = zone_temp;
            //printf("on remplit %d,%d \n",i1,y1);
            y+=nieme_hauteur;
        }  
        
        i+=nieme_longeur;
    }
    fseek(f,0,SEEK_SET);
    //printf("On se replace au début\n");
    //printf("N = %d\n",n);
    int i2,y2;
    for(i2=0;i2<n;i2++)
    {
        for(y2=0;y2<n;y2++)
        {
            //printf("%d;%lf;%lf;%lf;%lf;%d\n",tab[i2][y2].id_zone,tab[i2][y2].pos.haut_gauche.lon,tab[i2][y2].pos.bas_droit.lon,tab[i2][y2].pos.haut_gauche.lat,tab[i2][y2].pos.bas_droit.lat,tab[i2][y2].ligne);
            fprintf(f,"%d;%lf;%lf;%lf;%lf;%d;%d\n",tab[i2][y2].id_zone,tab[i2][y2].pos.haut_gauche.lon,tab[i2][y2].pos.bas_droit.lon,tab[i2][y2].pos.haut_gauche.lat,tab[i2][y2].pos.bas_droit.lat,tab[i2][y2].ligne,tab[i2][y2].effectif);
        }
    }
    char *txt = malloc(4096*sizeof(char));
    size_t taille = sizeof(txt);
     while (getline (&txt,&taille,f2) != -1) {
        fprintf(f, "%s\n",txt);
    }

}
