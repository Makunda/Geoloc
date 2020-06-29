/*!
* \author Hugo Joby
* \verion 5.7
* \file stats.h
* \brief Satistiques liés aux clusters.
*/

#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

/**
 * \fn int **init_tab_heure();
 * \brief Initialise un tableau d'heure  .
 * \param void
 * \return (int **) Tableau d'heure initialise. 
 */
int **init_tab_heure();

void afficher_tab(int **tab);

/**
 * \fn void remplir_tab_heure(tete_liste_point *pt, element_liste_point *p_cluster)
 * \brief intialise et remplie le talbeau horaire de p_cluster  .
 * \param (tete_liste_point *pt), liste de point pt, (element_liste_point *p_cluster), element de liste cluster a remplir 
 * \return void. 
 */
void remplir_tab_heure(tete_liste_point *pt, element_liste_point *p_cluster);

/**
 * \fn void remplir_tab_heure_logs(tete_liste_logs *pt_logs);
 * \brief intialise et remplie tout les talbeaux horaires de tout les clusters de pt_log  .
 * \param (tete_liste_logs *pt_logs), liste devant etre intialise
 * \return void. 
 */
void remplir_tab_heure_logs(tete_liste_logs *pt_logs);

/**
 * \fn int ** fusion_tab_heure(element_liste_point *p1, element_liste_point *p2)
 * \brief Fusionne deux tableaux horaires en un nouveau .
 * \param (element_liste_point *p1), element a fusionner  , (element_liste_point *p2), element a fusionner
 * \return int ** nouveau tableau resultant de la fusion. 
 */
int ** fusion_tab_heure(element_liste_point *p1, element_liste_point *p2);
#endif