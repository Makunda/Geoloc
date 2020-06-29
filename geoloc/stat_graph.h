/*!
* \author Vincent Mozziconacci
* \verion 5.0
* \file stat_graph.h
* \brief Fonctions relatives à la visualisation des statistiques
*/

#ifndef STAT_GRAPH_H_INCLUDED
#define STAT_GRAPH_H_INCLUDED


/**
 * \buildQuad(sfVertexArray *array, int offset, float factor, float size, sfFloatRect rectSprite, float zoomFactor)
 * \brief Construit des quadrilatères destinés à être affiché dans le diagramme de fréquentation des clusters
 *	
 * \param array : Tableau de vertex (sommets) à tracer
 * \param offset : Ecart entre deux quadrilatères du diagramme
 * \param size : Largeur du quadrilatère
 * \param rectSprite : Rectangle representant les limites de la fenêtre dans lequel le diagramme doit être affiché
 * \param zoomFactor : Niveau de zoom actuel
 * \return void
 */

void buildQuad(sfVertexArray *array, int offset, float factor, float size, sfFloatRect rectSprite, float zoomFactor);

/**
 * \max_tab(int** tab)
 * \brief Renvoie le maximum d'un tableau. La fonction permet de déterminer la valeur maximale du diagramme, elle sera la limite de toutes les barres du diagramme.
 *	
 * \param tab : Tableau d'entiers à deux dimensions
 * \return int : Valeur maximale du tableau
 */

int max_tab(int** tab);

#endif