/*!
* \author Hugo Joby
* \verion 5.8
* \file route.h
* \brief Traitement des routes et fonctions liees.
*/

#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

/**
 * \fn tete_liste_route *init_liste_route()
 * \brief Initialise la liste de route  .
 * \param void
 * \return (tete_liste_route *) Liste de route 
 */
tete_liste_route *init_liste_route();

/**
 * \fn int liste_vide_route(tete_liste_route *pt)
 * \brief Verifie si la liste est vide ou non  .
 * \param pt , pointeur sur la tete de liste
 * \return (int) 1 si vide , 0 sinon 
 */
int liste_vide_route(tete_liste_route *pt);

/**
 * \fn void ajout_liste_route(tete_liste_route *pt, route r)
 * \brief Ajout une route dans la liste de route pt.
 * \param pt , pointeur sur la tete de liste, r route a ajouter
 * \return void 
 */
void ajout_liste_route(tete_liste_route *pt, route r);

/**
 * \fn void supprimer_element_route(tete_liste_route *pt);
 * \brief Supprimer le premier element de la liste de route pt.
 * \param pt , pointeur sur la tete de liste
 * \return void 
 */
void supprimer_element_route(tete_liste_route *pt);

/**
 * \fn void supprimer_route(tete_liste_point *pt, route r)
 * \brief Supprime toutes les routes r dans pt.
 *	On va parcourir la liste de point pt et supprimer tout les points de r dans pt
 * \param pt , pointeur sur la tete de liste de point, r route dont les entites sont a supprimer
 * \return void 
 */
void supprimer_route(tete_liste_point *pt, route r);

void vider_liste_route(tete_liste_route *pt);

/**
 * \fn tete_liste_route * supprimer_element_route_liste(tete_liste_route *pt, element_liste_route *p)
 * \brief Supprime l'element p dans pt.
 *	
 * \param pt , pointeur sur la tete de liste de point, p element_liste_route a supprimer
 * \return (tete_liste_route *) le pointeur vers la liste 
 */
tete_liste_route * supprimer_element_route_liste(tete_liste_route *pt, element_liste_route *p);

/**
 * \fn tete_liste_route *route_cluster(tete_liste_point *pt);
 * \brief Determine les routes entre clusters dans une liste de point
 *	La fonction va parcourir tout les points de la liste et "couper" les routes entre deux clusters
 * \param (tete_liste_point *pt) , pointeur sur la tete de liste de point
 * \return (tete_liste_route *) Liste de route cree a partir de la liste de point 
 */
tete_liste_route *route_cluster(tete_liste_point *pt);

#endif
