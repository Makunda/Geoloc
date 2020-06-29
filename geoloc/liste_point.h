/*!
* \author Hugo Joby
* \verion 4.7
* \file liste_point.h
* \brief Fonctions relatives au listes doublement chainees de points.
* Toutes les fonctions necessitant une interface directe entre le programme et les différents fichiers.
* Utile pour la lecture et l'ecriture de logs anonymisés.
*/

#ifndef LISTE_POINT_H_INCLUDED
#define LISTE_POINT_H_INCLUDED
#include "structure.h"

/**
 * \fn tete_liste_point *init_liste()
 * \brief Initialise une liste de point .
 *
 * \param void.
 * \return tete_liste_point une liste initialisée.
 */
tete_liste_point *init_liste();

/**
 * \fn int liste_vide(tete_liste_point *pt)
 * \brief Verifie si une liste est vide ou non .
 *
 * \param pt Pointeur sur une liste de point.
 * \return 1 si liste vide , 0 sinon.
 */
int liste_vide(tete_liste_point *pt);

/**
 * \fn element_liste_point *retourner_element_id(tete_liste_point *pt,int a)
 * \brief Retourne un element en fonction de sa place.
 *
 * \param pt Pointeur sur une liste de point, a position de l'element.
 * \return element si position valable.
 */
element_liste_point *retourner_element_id(tete_liste_point *pt,int a);

/**
 * \fn int existe_liste(tete_liste_point *pt, point *p)
 * \brief Cherche si un element existe dans la liste.
 *
 * \param pt Pointeur sur une liste de point, p point a verifier.
 * \return 1 si trouvé, 0 sinon.
 */
int existe_liste(tete_liste_point *pt, point *p);

/**
 * \fn void liste_union(tete_liste_point *pt1, tete_liste_point *pt2)
 * \brief Realise l'union de deux listes.
 *
 * \param pt1 et pt2 listes contenant des points.
 * \return void.
 */
void liste_union(tete_liste_point *pt1, tete_liste_point *pt2);

/**
 * \fn int point_egaux(point *a,point *b)
 * \brief Verifie si deux points sont egaux.
 *
 * \param a et b les points a tester.
 * \return 1 si egaux, 0 sinon.
 */
int point_egaux(point *a,point *b);

/**
 * \fn void ajout_liste_fin(tete_liste_point *pt, point *pnt)
 * \brief Ajoute un element a la fin d'une liste.
 *
 * \param pt Liste de point, pnt Point a inserer.
 * \return void.
 */
void ajout_liste_fin(tete_liste_point *pt, point *pnt);

/**
 * \fn void ajout_liste(tete_liste_point *pt, point *pnt)
 * \brief Ajoute un element au debut d'une liste.
 *
 * \param pt Liste de point, pnt Point a inserer.
 * \return void.
 */
void ajout_liste(tete_liste_point *pt, point *pnt);

/**
 * \fn void ajout_liste_tri(tete_liste_point *pt, point *pnt)
 * \brief Ajout "trie' dans une liste.
 *
 * On trie les listes suivant l'id des points ( le Timestamp ), en inserant chaque element à la bonne place.
 *	Gain de temps et de moyen par rapport aux autres methodes de tri.
 * \param pt Liste de point, pnt Point a inserer.
 * \return void.
 */
void ajout_liste_tri(tete_liste_point *pt, point *pnt);

/**
 * \fn void supprimer_element(tete_liste_point *pt)
 * \brief Supprimer un element au debut d'une liste.
 *
 * \param pt Liste de point.
 * \return void.
 */
void supprimer_element(tete_liste_point *pt);

/**
 * \fn tete_liste_point * supprimer_element_liste(tete_liste_point *pt,element_liste_point *p)
 * \brief Supprimer un element dans une liste.
 *
 * \param pt Liste de point, pnt Point a supprimer.
 * \return tete_liste_point* Nouvelle liste de point.
 */
tete_liste_point * supprimer_element_liste(tete_liste_point *pt,element_liste_point *p);

/**
 * \fn void afficher_liste_console(tete_liste_point *pt)
 * \brief Affiche les adresses des elements de la liste dans la console.
 * Pratique pour la phase de Debuggage
 * \param pt Liste de point.
 * \return void.
 */
void afficher_liste_console(tete_liste_point *pt);
void detecter_erreur(tete_liste_point *pt);

/**
 * \fn void afficher_liste(tete_liste_point *pt,FILE *f1)
 * \brief Affiche les adresses des elements de la liste dans un fichier.
 * Pratique pour la phase de Debuggage
 * \param pt Liste de point, f1 fichier dans lequel afficher.
 * \return void.
 */
void afficher_liste(tete_liste_point *pt,FILE *f1);

/**
 * \fn void vider_liste(tete_liste_point *pt)
 * \brief Supprime une liste de point.
 *
 * \param pt Liste de point.
 * \return void.
 */
void vider_liste(tete_liste_point *pt);

#endif // LISTE_POINT_H_INCLUDED
