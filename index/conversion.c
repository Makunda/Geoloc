#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "conversion.h"
#include "structure.h"

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

coordonnee ToCoordonnee(double lon,double lat)
{
    coordonnee temp;
    temp.lon = lon;
    temp.lat = lat;
    return temp;
}


