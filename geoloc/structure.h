/*!
* \author Hugo_Joby
* \verion 5.0
* \file structure.h
* \brief Contient les différentes structures utiles au programme.
*/


#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

/*!
* \struct droite_affine structure.h
* \brief Droite affine y = ax + b
*/

typedef struct droite_affine{
    double a; 
    double b;
}droite_affine;

/*!
* \struct coordonnee structure.h
* \brief Coordonnes d'un point
* 
*   Les coordonnes sont définis par une latitude et une longitude
*/

typedef struct coordonnee{
    double lon; /*!< Longitude du point ( ou X). */
    double lat; /*!< Latitude du point ( ou Y). */
}coordonnee;

/*!
* \struct pixel structure.h
* \brief Coordonnees en pixel d'un point
* 
*   Les coordonnes en pixel pour l'affichage des elements sur la carte
*/

typedef struct pixel
{
   double x; /*!< Coordonnee en X */
   double y; /*!< Coordonnee en Y */
}pixel;

/*!
* \struct couleur structure.h
* \brief Couleurs au format RGB
* 
*   Structure de couleur RGB avec 3 differentes composantes.
*/

typedef struct couleur
{
    int r; /*!< Conposante en rouge. */
    int g; /*!< Conposante en vert. */
    int b; /*!< Conposante en bleu. */
}couleur;

/*!
* \struct point_ign structure.h
* \brief Structure d'un point IGN.
* 
*   Structure contenant toutes les informations d'un point IGN tire de
*   la base IGN.
*/

typedef struct point_ign {
    char *id; /*!< Id du point dans la base. */
    char *id_tr; /*!< Id de la trace utilisee. */
    char *methode; /*!< Methode de calcul utilise. */
    char *num; /*!< Numero de rue du point. */
    char *rep; /*!< Repetition (bis, etc..). */
    char *comp; 
    char *nom_voie; /*!< Nom de la voie. */
    char *alias; /*!< Alias du point. */
    char *nom_ld;
    char *code_insee; /*!< Code de reference INSEE. */
    char *code_postal; /*!< Code Postale. */
    char *type_loc;
    char *cote; /*!< Cote de la rue. */
    coordonnee pos_l93; /*!< Position en lambert 93. */
    coordonnee pos; /*!< Position en GPS. */
}point_ign;

/*!
* \struct point structure.h
* \brief Structure d'un point.
* 
*   Structure contenant toutes les informations d'un point tire d'un
*   log ou devant etre cree.
*   Il peut prendre la forme d'un point mais aussi d'un cluster.
*/

typedef struct point{
    struct element_liste_logs *nom_fichier; /*!< Log parent du point. */
    int **tab_heure; /*!<frequentation des clusters en fonction de l'heure. */
    int id; /*!< Timestamp du point. */
    struct point_ign *ign; /*!< Point IGN associe. */
    coordonnee pos; //longitude et latitude
    int id_cluster; /*!< Id du cluster parent (-2 si Bruit, -1 à l'initialisation) */
    pixel pix; /*!< coordonnees en pixel. */
    int effectif; /*!< Effectif du point ou du cluster. */
    double rayon; /*!< Rayon du point. */
    double epsilon; /*!< Valeur epsilon du DBSCAN utilise. */
    couleur color; /*!< Couleur du point. */
} point;


/*!
* \struct element_liste_point structure.h
* \brief Element contenant un point dans une liste.
*/

typedef struct element_liste_point{
    point *pnt; /*!< Valeur du point. */
    struct element_liste_point *suiv; /*!< Pointeur sur point suivant. */
    struct element_liste_point *prec; /*!< Pointeur sur point prec. */
}element_liste_point;

/*!
* \struct tete_liste_point structure.h
* \brief Tete d'une liste de point. 
*/

typedef struct tete_liste_point{
    int taille; /*!< Taille de la lsite. */
    element_liste_point *suiv; /*!< Pointeur sur point suivant. */
} tete_liste_point;

/*!
* \struct route structure.h
* \brief Route reliant les clusters. 
*/

typedef struct route {
    tete_liste_point *liste_point_route; /*!< Liste des points formants la route. */
    point *p_debut; /*!< Point de départ de la route. */
    point *p_fin; /*!< Point d'arrivé de la route. */
    couleur color; /*!< Couleur de la route. */
    int id_cluster_debut; /*!< Id de début du cluster. */
    int id_cluster_fin;/*!< Id de fin du cluster. */
}route;

/*!
* \struct element_liste_route structure.h
* \brief Element de la liste de route. 
*/

typedef struct element_liste_route
{
    route r;
    struct element_liste_route *suiv;/*!< Pointeur sur point suivant. */
    struct element_liste_route *prec; /*!< Pointeur sur point prec. */   
}element_liste_route;

/*!
* \struct tete_liste_route structure.h
* \brief Tete de la liste de route. 
*/

typedef struct tete_liste_route
{
    element_liste_route *suiv; /*!< Pointeur sur route suivante. */
    int taille; /*!< Taille de la lsite. */
}tete_liste_route;

/*!
* \struct element_liste_logs structure.h
* \brief element de la liste de log.
* 
*   Chaque Log contient ses propres informations, ses popres logs,
*   ses propres clusters, etc.. 
*    
*/

typedef struct element_liste_logs
{
    struct element_liste_logs *suiv; /*!< Pointeur sur l'element suivant. */
    FILE *fichier_log; /*!< Fichier log. */
    char* id; /*!< Nom du fichier log. */
    couleur color; /*!< Couleur du log. */
    tete_liste_point *pt; /*!< Liste de point du log. */
    tete_liste_point *pt_cluster; /*!< Liste des clusters du log. */
    tete_liste_route *pt_route; /*!< Liste de route du log. */
} element_liste_logs;

/*!
* \struct tete_liste_logs structure.h
* \brief Tete de la liste de log. 
*/

typedef struct
{
    element_liste_logs *suiv; /*!< Pointeur sur log suivant. */
    int taille;/*!< Taille de la lsite. */
} tete_liste_logs;



#endif // STRUCTURE_H_INCLUDED

