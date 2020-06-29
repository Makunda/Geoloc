#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED
#include "structure.h"

coordonnee LambertToGps(coordonnee co);
float DegreVersRadian(float angleDegre);
coordonnee ToCoordonnee(double lon,double lat);

#endif