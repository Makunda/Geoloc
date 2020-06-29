#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

 
typedef struct coordonnee{
    double lon; //x
    double lat; //y
}coordonnee;

typedef struct coor_tableau{
	coordonnee haut_gauche;
	coordonnee haut_droite;
	coordonnee bas_gauche;
	coordonnee bas_droit;

}coor_tableau;

typedef struct point_ign {
    char *id;
    char *id_tr;
    char *methode;
    char *num;
    char *rep;
    char *comp;
    char *nom_voie;
    char *alias;
    char *nom_ld;
    char *code_insee;
    char *code_postal;
    char *type_loc;
    char *cote;
    char *x_193;
    char *y_193;
    coordonnee pos;
}point_ign;

typedef struct element_liste_point_ign{
    point_ign *pnt;
    struct element_liste_point_ign *suiv;
}element_liste_point_ign;

typedef struct tete_liste_point_ign{
    int taille;
    element_liste_point_ign *suiv;
} tete_liste_point_ign;

typedef struct zone
{
    int id_zone;
    int ligne;
    int effectif;
    coor_tableau pos;
    tete_liste_point_ign *liste_point;
} zone;

#endif 