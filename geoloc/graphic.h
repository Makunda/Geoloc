/*!
* \author Vincent Mozziconacci
* \verion 5.0
* \file graphic.h
* \brief Fonctions relatives à la visualisation.
*/



#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "structure.h"
#include <SFML/Graphics.h>

#define RADIUS 10 /*!<Rayon par défaut des points affichés*/
#define WINDOW_WIDTH 1280 /*!<Largeur par défaut de la fenêtre d'affichage*/
#define WINDOW_HEIGHT 720 /*!<Hauteur par défaut de la fenêtre d'affichage*/
#define ZOOM 2.0 /*!<Pas du niveau de zoom*/
#define OFFSET 100 /*!<Longueur du pas du deplacement au clavier*/

/**
 * \graphic(tete_liste_point *l, tete_liste_logs *liste_retour)
 * \brief Boucle graphique principale, gère l'affichage et la gestion des évènements
 *
 * \param l Pointeur sur la liste des points triés chronologiquement
 * \param liste_retour Pointeur sur la liste contenant toutes les listes de points, de cluster
  * \param liste_cluster Pointeur sur la liste des cluster temporelle (résultant de fusion de cluster, implémenté mais pas utilisé)
 * \return 0 lorsque la boucle graphique s'est executé correctement
 */

int graphic(tete_liste_point *l, tete_liste_logs *liste_retour, tete_liste_point *liste_cluster);



#endif 
