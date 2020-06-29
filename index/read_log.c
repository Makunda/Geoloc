#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "read_log.h"
#include "liste_point.h"
#include "conversion.h"
#include <errno.h>


#define size_max 4096
#define size_malloc 30

void afficher_point_ign(point_ign *p)
{
    printf("Id :%s\nid_tr :%s\n methode :%s\n num :%s\n rep :%s\n comp :%s\n nom_voie:%s\n alias :%s\n nom_ld:%s\n code Inse:%s\n code postal:%s\n type loc:%s\n cote :%s\n x_l93:%s\n y_l93:%s\n ",p->id,p->id_tr,p->methode,p->num,p->rep,p->comp,p->nom_voie,p->alias,p->nom_ld,p->code_insee,p->code_postal,p->type_loc,p->cote,p->x_193,p->y_193);
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
    p->x_193 = malloc(size_malloc*sizeof(char));
    p->y_193 = malloc(size_malloc*sizeof(char));
    return p;
    

}

point_ign *ini_point_ign(char *txt)
{
    point_ign *p = malloc_point();
    
    int ret;
    int test =0;
    if (15 != (ret = sscanf(txt,"%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%[^';'];%s",p->id,p->id_tr,p->methode,p->num,p->rep,p->comp,p->nom_voie,p->alias,p->nom_ld,p->code_insee,p->code_postal,p->type_loc,p->cote,p->x_193,p->y_193)))
    {
        printf("Erreur lecture fichier %d\n",ret);
        test =1;
        //exit(EXIT_FAILURE);
    }
    coordonnee temp;
    temp.lon = atoi(p->x_193); 
    temp.lat = atoi(p->y_193);
    p->pos = LambertToGps(temp);
    if(test == 1)
    {
        afficher_point_ign(p);
    }
    //afficher_point_ign(p);
    return p;
}


tete_liste_point_ign *read_ign()
{
    FILE *f;
    tete_liste_point_ign *pt = init_liste_ign();
    f = fopen("../index/adresse_ign.txt","r");
    if(f == NULL)
    {
        printf("Erreur ouverture fichier IGN : fichier manquant \n");
        exit(EXIT_FAILURE);
    }
    int i=0;
    
    ssize_t read;
    char *txt = malloc(size_max*sizeof(char));
    size_t taille = sizeof(txt);
    if((read=getline (&txt,&taille,f)) == -1)
    {
        printf("Erreur : Lecture premiere ligne\n");
        exit(EXIT_FAILURE);
    }
    while ((read=getline (&txt,&taille,f)) != -1) {
        ajout_liste_ign(pt,ini_point_ign((txt)));
        //sprintf("[%d] itérations \n",pt->taille);
    }
	
    return pt;
}


