#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "structure.h"
#include "fichier.h"
#include "liste_point.h"
#include "cluster.h"
#include "graphic.h"
#include "route.h"
#include "init.h"


void buildQuad(sfVertexArray *array, int offset, float factor, float size, sfFloatRect rectSprite, float zoomFactor)
{
	sfVertex quad, quad2, quad3, quad4;

    quad.position = vector2f( rectSprite.left + (offset + 10) * zoomFactor, rectSprite.top + (30 + 256) * zoomFactor);
    quad2.position = vector2f( rectSprite.left + (offset + 10) * zoomFactor, rectSprite.top + (30 +(256 - factor))* zoomFactor);
    quad3.position = vector2f( rectSprite.left + (offset + 10 + size) * zoomFactor, rectSprite.top + (30 + (256 - factor)) * zoomFactor);
    quad4.position = vector2f(  rectSprite.left + (offset + 10 + size) * zoomFactor, rectSprite.top + (30 + 256) * zoomFactor);

    quad.color = sfWhite;
    quad2.color = sfWhite;
    quad3.color = sfWhite;
    quad4.color = sfWhite;

    
    quad.texCoords = vector2f(0, 0);
    quad2.texCoords = vector2f(25, 0);
    quad3.texCoords = vector2f(25, 50);
    quad4.texCoords = vector2f(0, 50);


	sfVertexArray_append(array, quad);
	sfVertexArray_append(array, quad2);
	sfVertexArray_append(array, quad3);
	sfVertexArray_append(array, quad4);
}

int max_tab(int** tab)
{
    int i, max = tab[0][1];
    for(i=0; i<24; i++)
    {
        if(tab[i][1] > max)
        {
            max = tab[i][1];
        }
    }
    return max;
}
