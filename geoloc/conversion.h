/*!
* \author Hugo Joby
* \verion 5.0
* \file conversion.h
* \brief Fonction de Conversions.
*/

#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED
#define TAILLE 2

#include "structure.h"

/**
 * \fn coordonnee LambertToGps(coordonnee co)
 * \brief Fonction convertissant les coordonnes du Lambert93 en GPS  .
 *
 * \param co Les coordonnees en Lambert 93.
 * \return coordonnees en GPS.
 */
coordonnee LambertToGps(coordonnee co);

/**
 * \fn float DegreVersRadian(float angleDegre)
 * \brief Fonction convertissant les degre en radian.
 *
 * \param angleDegre l'angle en degre.
 * \return float l'angle en radian .
 */
float DegreVersRadian(float angleDegre);

/**
 * \fn void latLonToXY(point *A)
 * \brief Fonction convertissant la latitude en longitude.
 *
 * \param A point dont les coordonnees sont a convertir.
 * \return void.
 */
void latLonToXY(point *A);

/**
 * \fn double calcul_distance(point *p1,point *p2)
 * \brief Calcul de la distance entre deux points.
 *
 * \param p1 et p2 les point dont ont doit calculer la distance.
 * \return double la distance.
 */
double calcul_distance(point *p1,point *p2);

/**
 * \fn double calcul_distance_coordonne(coordonnee p1,coordonnee p2)
 * \brief Calcul de la distance entre deux coordonnee.
 *
 * \param p1 et p2 les coordonnee dont ont doit calculer la distance.
 * \return double la distance.
 */
double calcul_distance_coordonne(coordonnee p1,coordonnee p2);

/**
 * \fn double calcul_distance_pixel(point *p1,point *p2)
 * \brief Calcul de la distance entre deux pixels.
 *
 * \param p1 et p2 les pixels dont ont doit calculer la distance.
 * \return double la distance.
 */
double calcul_distance_pixel(point *p1,point *p2);

/**
 * \fn point *coordonnee_vers_point(coordonnee coor)
 * \brief Convertit une coordonnees en point.
 *
 * \param coor coordonne a convertir.
 * \return point retourne un point .
 */
point *coordonnee_vers_point(coordonnee coor);

/**
 * \fn coordonnee point_vers_coordonnee(point *pnt)
 * \brief Convertit un point en coordonnee.
 *
 * \param point point a convertir.
 * \return coordonnee point convertit.
 */
coordonnee point_vers_coordonnee(point *pnt);

/**
 * \fn double calcul_distance_metre(point *p1, point *p2)
 * \brief Retourne la distance en metre en deux points .
 *
 * \param p1 et p2 les points dont ont doit calculer la distance.
 * \return double la distance en letre.
 */
double calcul_distance_metre(point *p1, point *p2);

/**
 * \fn double calcul_vitesse_mps(point *p1, point *p2)
 * \brief Calcul la vitesse entre deux.
 *
 * \param p1 et p2 les points dont ont doit calculer la vitesse instantanée.
 * \return double la vitesse instantanee.
 */
double calcul_vitesse_mps(point *p1, point *p2);

#endif // CONVERSION_H_INCLUDED
