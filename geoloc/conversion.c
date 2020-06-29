#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "conversion.h"

#define PI 3.14159265358979323846
float DegreVersRadian(float angleDegre) {
         return (angleDegre*PI)/180;
}



coordonnee LambertToGps(coordonnee co) {

    // définition des variables de coordonées
    double x = co.lon;
    double y = co.lat;

    // définition des constantes
    double c = 11754255.426096; //constante de la projection
    double e = 0.0818191910428158; //première exentricité de l'ellipsoïde
    double n = 0.725607765053267; //exposant de la projection
    double xs = 700000; //coordonnées en projection du pole
    double ys = 12655612.049876; //coordonnées en projection du pole
    double lam = 0.0523598775598; //longitude origine ou méridien central de la projection

    // pré-calcul
    double a = log(c/(sqrt(pow((x-xs),2)+pow((y-ys),2))))/n;

    // calcul
    co.lon = (((atan(-(x-xs)/(y-ys)))/n+lam)/PI) * 180;
    co.lat = asin(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*sin(1))))))))))))))))))))))/PI*180;
    return co;
}

coordonnee GpsToLambert(coordonnee co) {

     // définition des variables de coordonées
    double x = co.lon;
    double y = co.lat;

    // définition des constantes
    double c = 11754255.426096; //constante de la projection
    double e = 0.0818191910428158; //première exentricité de l'ellipsoïde
    double n = 0.725607765053267; //exposant de la projection
    double xs = 700000; //coordonnées en projection du pole
    double ys = 12655612.049876; //coordonnées en projection du pole
    double lam = 0.0523598775598; //longitude origine ou méridien central de la projection

    // pré-calcul
    double a = log(c/(sqrt(pow((x-xs),2)+pow((y-ys),2))))/n;

    // calcul
    co.lon = (((atan(-(x-xs)/(y-ys)))/n+lam)/PI) * 180;
    co.lat = asin(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*(tanh(a+e*atanh(e*sin(1))))))))))))))))))))))/PI*180;
    
    return co;

}

void latLonToXY(point *A)
{
    point tab[TAILLE]; //Tableau des points de reference

   //88 Bd Lahitolle
   tab[0].pos.lat=47.0826088;
   tab[0].pos.lon=2.41628479;
   tab[0].pix.x=14858;
   tab[0].pix.y=8528;


   //Rue parmentier
   tab[1].pos.lat=47.0879378;
   tab[1].pos.lon=2.397832;
   tab[1].pix.x=9269;
   tab[1].pix.y=6107;

   //Calcul de la reference + variation
   double dX = (tab[0].pos.lon - tab[1].pos.lon) / (tab[0].pix.x - tab[1].pix.x);
   double dY = (tab[0].pos.lat - tab[1].pos.lat) / (tab[0].pix.y - tab[1].pix.y);
   double lat0 = tab[1].pos.lat - tab[1].pix.y * dY;
   double long0 = tab[1].pos.lon - tab[1].pix.x * dX;

   //Calcul des coordonnées en pixels à partir des points de reference
   A->pix.x = (A->pos.lon - long0) / dX;
   A->pix.y = (A->pos.lat - lat0) / dY;
}

point *coordonnee_vers_point(coordonnee coor)
{
    point *pnt = malloc(sizeof(pnt));
    pnt->pos.lon=coor.lon;
    pnt->pos.lat=coor.lat;
    pnt->id=-1;
    return pnt;
}

coordonnee point_vers_coordonnee(point *pnt)
{
    coordonnee coor;
    coor.lon=pnt->pos.lon;
    coor.lat=pnt->pos.lat;
    return coor;
}


double calcul_distance(point *p1,point *p2)
{
    return sqrt(pow(p2->pos.lat - p1->pos.lat,2)+pow(p2->pos.lon - p1->pos.lon,2));
}

double calcul_distance_coordonne(coordonnee p1,coordonnee p2)
{
    return sqrt(pow(p2.lat - p1.lat,2)+pow(p2.lon - p1.lon,2));
}

double calcul_distance_pixel(point *p1,point *p2)
{
    return sqrt(pow(p2->pix.y - p1->pix.y,2)+pow(p2->pix.x - p1->pix.x,2));
}

double calcul_distance_metre(point *p1, point *p2)
{

	double rayon_terre = 6378137;
	double rlo1 = DegreVersRadian( p1->pos.lon);
	double rla1 = DegreVersRadian( p1->pos.lat);
	double rlo2 = DegreVersRadian( p2->pos.lon);
	double rla2 = DegreVersRadian( p2->pos.lat);
	double dlo = (rlo2 - rlo1) /2; 
	double dla = (rla2 - rla1) /2;
	double a = ( sin(dla) * sin(dla)) + cos(rla1) * cos(rla2) * (sin(dlo) * sin(dlo));
	double d = 2 * atan2(sqrt(a),sqrt(1 - a));
	return llabs(rayon_terre *d);
}

double calcul_vitesse_mps(point *p1, point *p2)
{
	printf("distance metre : %lf \n", calcul_distance_metre(p1,p2));
  return calcul_distance_metre(p1,p2)/((p1->id) - (p2->id));

}
