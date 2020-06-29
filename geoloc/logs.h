/*!
* \author Hugo Joby
* \verion 5.1
* \file logs.h
* \brief gestion de la liste des logs.
*/


#ifndef LOGS_H_INCLUDED
#define LOGS_H_INCLUDED

/**
 * \fn tete_liste_logs *init_liste_logs()
 * \brief Initialise une liste de logs .
 *	Cette liste contiendra une liste  d'element log, afin de gerer plusieurs traces.
 *	Ces elements eux-même de point, une liste de cluster et de route. 
 *
 * \param void.
 * \return tete_liste_logs * pointeur sur la tete de liste.
 */
tete_liste_logs *init_liste_logs();

/**
 * \fn element_liste_logs *init_element_log(FILE *fichier_log, char* id, tete_liste_point *pt, tete_liste_point *pt_cluster, tete_liste_route *pt_route, couleur color)
 * \brief Initialise un element de la liste log .
 *
 * \param (FILE *) fichier_log , le fichier lié au log, (char*) id Le nom du fichier, pt liste des points du log, pt_cluster liste des clusters du log, pt_route liste des routes du log, color la couleur
 * \return (element_liste_logs *) un element de liste log.
 */
element_liste_logs *init_element_log(FILE *fichier_log, char* id, tete_liste_point *pt, tete_liste_point *pt_cluster, tete_liste_route *pt_route, couleur color);

/**
 * \fn int liste_vide_logs(tete_liste_logs *pt)
 * \brief Verifie si la liste est vide ou non .
 *
 * \param tete_liste_logs *pt , le pointeur sur la liste de log
 * \return (int) 1 si vide , 0 sinon.
 */
int liste_vide_logs(tete_liste_logs *pt);

/**
 * \fn tete_liste_point *init_liste_temporelle(tete_liste_logs *pt_logs)
 * \brief Initialise la liste temporelle .
 *	La liste temporelle est une liste de point, contenant tout les points de tout les logs.
 *	Elle permet un affichage dynamique de l'apparition des traces.
 * \param tete_liste_logs *pt , le pointeur sur la liste de log
 * \return (tete_liste_point *) La tete de liste contenant tout les points.
 */
tete_liste_point *init_liste_temporelle(tete_liste_logs *pt_logs);

/**
 * \fn void ajout_liste_logs(tete_liste_logs *pt, element_liste_logs *nouveau)
 * \brief Ajoute un element log dans la liste log .
 *
 * \param (tete_liste_logs *) pt, tete de liste de log, (element_liste_logs *) nouveau, element liste log
 * \return void.
 */
void ajout_liste_logs(tete_liste_logs *pt, element_liste_logs *nouveau);

/**
 * \fn element_liste_logs * main_logs(char *path_fichier, char *nom_fichier)
 * \brief Fonction "main" pour chacun des logs.
 *	Elle permet d'initialisé toute les paramètre, comme l'extraction des donnnes, la deinition des différentes listes, etc..
 * \param (char *) path_fichier , le chemin du fichier , (char *) nom_fichier , le nom du fichier
 * \return (element_liste_logs *) un element de liste log.
 */
element_liste_logs * main_logs(char *path_fichier, char *nom_fichier);

/**
 * \fn void supprimer_element_logs(tete_liste_logs *pt)
 * \brief Supprime le premier element log dans une liste log .
 *
 * \param (tete_liste_logs *) pt, tete de liste de log
 * \return void.
 */
void supprimer_element_logs(tete_liste_logs *pt);

/**
 * \fn void supprimer_element_logs_liste(tete_liste_logs *pt, element_liste_logs *p)
 * \brief Supprime un element log dans une liste log .
 *
 * \param (tete_liste_logs *) pt, tete de liste de log, (element_liste_logs *) p , element log a supprimer
 * \return void.
 */
void supprimer_element_logs_liste(tete_liste_logs *pt, element_liste_logs *p);

/**
 * \fn void vider_liste_logs(tete_liste_logs *pt)
 * \brief Vide la liste de tout element  .
 *
 * \param (tete_liste_logs *) pt, tete de liste de log a vider
 * \return void.
 */
void vider_liste_logs(tete_liste_logs *pt);

/**
 * \fn tete_liste_logs *insertion_logs()
 * \brief Initialise la liste des logs et la remplit  .
 *	La fonction insertion_logs() va lancer le main pour chacun des logs dans le dossier geoloc/logs
 * \param void
 * \return (tete_liste_logs *) tete_liste_log intialise
 */
tete_liste_logs *insertion_logs();
couleur randomCouleur();





#endif
