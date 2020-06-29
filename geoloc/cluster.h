/*!
* \author Hugo Joby
* \verion 5.0
* \file cluster.h
* \brief Traitement des points avec la detection des centres d'interets.
*/

#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED


/**
 * \fn int randab(int a, int b) 
 * \brief Retour un nombre aleatoire.
 *
 * \param a Valeur minimum, b Valeur Maximale.
 * \return int valeur entiere entre a et b aleatoire.
 */
int randab(int a, int b); //nombre aleatoire en [a;b[

/**
 * \fn tete_liste_point *lister_cluster(tete_liste_point *pt)
 * \brief Liste de cluster traitee.
 *
 * \param pt Liste pre-initialisee dans laquelle stocker les clusters.
 * \return tete_liste_point le pointeur de la liste contenant les clusters.
 */
tete_liste_point *lister_cluster(tete_liste_point *pt);

/**
 * \fn tete_liste_point *liste_voisinage(tete_liste_point *pt,point p,double eps)
 * \brief Liste des plus proches voisins d'un point p dans la liste pt.
 *
 * \param pt Liste pre-initialisee dans laquelle stocker les clusters, p point, eps valeur d'epsilon du DBSCAN
 *	Fonction propre à l'algorithme DBSCAN
 *
 * \return tete_liste_point le pointeur de la liste des plus proches voisins.
 */
tete_liste_point *liste_voisinage(tete_liste_point *pt,point p,double eps);

/**
 * \fn void caculer_couleur(tete_liste_point *pt,int interval)
 * \brief Genere une couleur aleatoire dans un intervalle 0 - intervalle, et l'assigne aux points.
 *
 * \param pt Liste pre-initialisee dans laquelle sont stockes les clusters, interval valeur maximal d'entite 
 *	
 *
 * \return void.
 */
void caculer_couleur(tete_liste_point *pt,int interval);

/**
 * \fn void etendre_cluster(tete_liste_point *pt,element_liste_point *p,tete_liste_point *epsilon_voisins, int id_cluster,double eps, int minPoint)
 * \brief Etend la recherche des clusters et stocke les points dans epsilon_voisins.
 *
 * \param pt Liste pre-initialisee dans laquelle sont stockes les points, p point, epsilon_voisins liste des voisins, id_cluster numero du cluster, eps valeur de epsilon, minPoint Minimum de point d'un cluster. 
 *	Fonction propre à l'algorithme DBSCAN.
 *
 * \return void.
 */
void etendre_cluster(tete_liste_point *pt,element_liste_point *p,tete_liste_point *epsilon_voisins, int id_cluster,double eps, int minPoint);

/**
 * \fn int DBSCAN(tete_liste_point *pt, double eps , int MinPoint)
 * \brief Fonction DBSCAN calculant les centres d'interets.
 *
 *  L'algorithme DBSCAN est un algorithme de partitionement basé sur la densité des clusters. Il prend deux parametres espilon, la distance minimale entre les point d'un cluster 
 *	et min_point le nombre de point minimum dans un cluster.
 * \param pt Liste pre-initialisee dans laquelle sont stockes les points, eps valeur de epsilon, minPoint Minimum de point d'un cluster. 
 *	
 *
 * \return int nombre de cluster crees.
 */
int DBSCAN(tete_liste_point *pt, double eps , int MinPoint);

/**
 * \fn droite_affine calc_perpendiculaire(coordonnee p1,coordonnee p2)
 * \brief Ancienne fonction utilisee pour l'algorithme K-Means.
 */
droite_affine calc_perpendiculaire(coordonnee p1,coordonnee p2);

/**
 * \fn int position_droite(droite_affine droite,point p1)
 * \brief Ancienne fonction utilisee pour l'algorithme K-Means.
 */
int position_droite(droite_affine droite,point p1);

/**
 * \fn coordonnee moyenne_position(tete_liste_point *pt)
 * \brief Calcul la position moyenne des point de la liste.
 *
 * \param pt Liste pre-initialisee dans laquelle sont stockes les points.
 *
 * \return coordonnee Les coordonnees moyenne en lat et lon de tout les point de la liste
 */
coordonnee moyenne_position(tete_liste_point *pt);

/**
 * \fn point_ign *malloc_point()
 * \brief Initialise un point IGN et le retourne
 *
 * \param void.
 *
 * \return Pointeur sur un point_ign initialise
 */
point_ign *malloc_point();

/**
 * \fn void cluster_base_ign(tete_liste_point *pt_cluster, FILE *f_index, FILE *f_traitement)
 * \brief Relie les clusters et la base IGN
 *
 * Trouve le point le plus proche du centre du cluster dans la base IGN.
 * \param pt_cluster Liste des clusters, f_index Fichier index du cluster, f_traitement Fichier contenant la base IGN traitee.
 *
 * \return void
 */
void cluster_base_ign(tete_liste_point *pt_cluster, FILE *f_index, FILE *f_traitement);

/**
 * \fn void supprimer_cluster(element_liste_logs *element, element_liste_point * cluster)
 * \brief Supprime un cluster et ses routes.
 *
 * \param element Log contenant le cluster, cluster le cluster a supprimer .
 *
 * \return void
 */
void supprimer_cluster(element_liste_logs *element, element_liste_point * cluster);


int lister_nombre_cluster(tete_liste_point *pt);

/**
 * \fn void nettoyer_cluster(tete_liste_point *pt,int MinPoint)
 * \brief Nettoye la liste des clusters et selectionne les clusters valides.
 *
 * \param pt Liste contenant les clusters, MinPoints Minimum de point dans un cluster.
 *
 * \return void
 */
void nettoyer_cluster(tete_liste_point *pt,int MinPoint);


/**
 * \fn tete_liste_point *init_liste_temporelle_cluster(tete_liste_logs *pt_log)
 * \brief Initialise la liste de cluster fusionnés.
 *
 * \param pt_log Liste contenant les logs.
 *
 * \return la liste de clusters fusionnés
 */
tete_liste_point *init_liste_temporelle_cluster(tete_liste_logs *pt_log);

#endif // CLUSTER_H_INCLUDED
