/*!
* \author Hugo Joby
* \verion 5.0
* \file fichier.h
* \brief Fonctions relatives au fichier.
* Toutes les fonctions necessitant une interface direct entre le programme et les différents fichiers.
* Utile pour la lecture et l'ecriture de logs anonymisés.
*/


#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include "structure.h"
#include "liste_point.h"
#include "conversion.h"

/**
 * \fn point *ini_point(char *txt,double eps, element_liste_logs *nom_fichier)
 * \brief Initialisation d'un point.
 *
 * \param txt la chaine de caratere issue du log, eps epsilon du DBSCAN, nom_fichier le nom du fichier log.
 * \return point si le point est correctement initialisé, NULL sinon.
 */
point *ini_point(char *txt,double eps, element_liste_logs *nom_fichier);

/**
 * \fn void read_log(FILE *f, tete_liste_point *pt,double eps)
 * \brief Lecture d'un log complet et enregistrement des points.
 *
 * \param f le fichier LOG, pt une liste pre-initialise de point, eps epsilon du DBSCAN.
 * \return void.
 */
void read_log(FILE *f, tete_liste_point *pt,double eps, element_liste_logs *nom_fichier);

/**
 * \fn void enregister_log(tete_liste_point *pt, char *nom_fichier)
 * \brief Enregistrement d'un log.
 *
 * \param pt liste contenant les points d'un log, nom_fichier le nom du fichier log à enregistrer.
 * \return void.
 */
void enregister_log(tete_liste_point *pt, char *nom_fichier);


#endif // FICHIER_H_INCLUDED
