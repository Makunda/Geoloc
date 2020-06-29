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

sfVector2f vector2f(float x, float y)
{
	sfVector2f vect;
	vect.x = x;
	vect.y = y;
	return vect;
}

sfFloatRect view_getRect(float zoomFactor, sfView *view)
{
	sfFloatRect rect;
	sfVector2f centerView = sfView_getCenter(view);
	sfVector2f viewSize = sfView_getSize(view);

	rect.left = (centerView.x - WINDOW_WIDTH/2 * zoomFactor);
	rect.top = (centerView.y - WINDOW_HEIGHT/2 * zoomFactor);
	rect.width = WINDOW_WIDTH * zoomFactor;
	rect.height = WINDOW_HEIGHT * zoomFactor;

	return rect;
}

int textureLoading(sfTexture *textTab[4][5])
{
	/* Chargement des textures de la carte */

	textTab[0][0] = sfTexture_createFromFile("ressources/map/A1.jpg", NULL);
	textTab[0][1] = sfTexture_createFromFile("ressources/map/A2.jpg", NULL);
	textTab[0][2] = sfTexture_createFromFile("ressources/map/A3.jpg", NULL);
	textTab[0][3] = sfTexture_createFromFile("ressources/map/A4.jpg", NULL);
	textTab[0][4] = sfTexture_createFromFile("ressources/map/A5.jpg", NULL);

	textTab[1][0] = sfTexture_createFromFile("ressources/map/B1.jpg", NULL);
	textTab[1][1] = sfTexture_createFromFile("ressources/map/B2.jpg", NULL);
	textTab[1][2] = sfTexture_createFromFile("ressources/map/B3.jpg", NULL);
	textTab[1][3] = sfTexture_createFromFile("ressources/map/B4.jpg", NULL);
	textTab[1][4] = sfTexture_createFromFile("ressources/map/B5.jpg", NULL);

	textTab[2][0] = sfTexture_createFromFile("ressources/map/C1.jpg", NULL);
	textTab[2][1] = sfTexture_createFromFile("ressources/map/C2.jpg", NULL);
	textTab[2][2] = sfTexture_createFromFile("ressources/map/C3.jpg", NULL);
	textTab[2][3] = sfTexture_createFromFile("ressources/map/C4.jpg", NULL);
	textTab[2][4] = sfTexture_createFromFile("ressources/map/C5.jpg", NULL);

	textTab[3][0] = sfTexture_createFromFile("ressources/map/D1.jpg", NULL);
	textTab[3][1] = sfTexture_createFromFile("ressources/map/D2.jpg", NULL);
	textTab[3][2] = sfTexture_createFromFile("ressources/map/D3.jpg", NULL);
	textTab[3][3] = sfTexture_createFromFile("ressources/map/D4.jpg", NULL);
	textTab[3][4] = sfTexture_createFromFile("ressources/map/D5.jpg", NULL);

	int i, j;
	for(i=0; i<4; i++)
	{
		for(j=0; j<5; j++)
		{
			if(!textTab[i][j])
			{
				printf("Erreur de chargement d'une texture\n");
				return 0;
			}
		}
	}

	printf("Texture loading succesful\n");
	return 1;
}

int spriteLoading(sfSprite *spriteTab[4][5], sfTexture *textTab[4][5])
{
	int i, j;
	sfIntRect textureSize;
	for(i=0; i<4; i++)
	{
		for(j=0; j<5; j++)
		{
			spriteTab[i][j] = sfSprite_create();
			if(!spriteTab[i][j])
			{
				return 0;
			}
			sfSprite_setTexture(spriteTab[i][j], textTab[i][j], 1);
			textureSize = sfSprite_getTextureRect(spriteTab[i][j]);
			sfSprite_setPosition(spriteTab[i][j], vector2f(j*textureSize.width, i*textureSize.height) );
		}
	}

	printf("Sprite loading succesful\n");
	return 1;
}


sfVertex* init_vertex(int taille)
{
	sfVertex* vertexTab = (sfVertex*)malloc(sizeof(sfVertex)*taille);
	return vertexTab;
}

sfText* init_text(char* string, sfFont *font, sfColor color, int taille)
{
	char buffer[80];
	sfText *text = sfText_create();
	sprintf(buffer, "%s", string);
	sfText_setFont(text, font);
	sfText_setString(text, buffer);
	sfText_setColor(text, color);
	sfText_setCharacterSize(text, taille);
	return text;
}

sfSprite* init_icon(sfTexture *texture)
{
	sfSprite *sprite;
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	return sprite;
}

sfCircleShape** init_tab(tete_liste_point *l)
{
	sfCircleShape** tab = (sfCircleShape**)malloc(sizeof(sfCircleShape*)*l->taille);
	return tab;
}

sfCircleShape*** init_tab_cluster(tete_liste_logs *l)
{
	element_liste_logs *element = l->suiv;
	sfCircleShape*** tab = (sfCircleShape***)malloc(sizeof(sfCircleShape**)*l->taille);
	int i;
	for(i=0; i<l->taille; i++)
	{
		if(element != NULL)
		{
			tab[i] = (sfCircleShape**)malloc(sizeof(sfCircleShape*)*element->pt_cluster->taille);
			element = element->suiv;
		}
	}
	return tab;
}

void init_cluster_temp(tete_liste_point *l, sfCircleShape** tab )
{
	int i;
	element_liste_point *elementpoint = l->suiv;
	for(i=0; i<l->taille; i++)
	{
		tab[i] = sfCircleShape_create();
		sfCircleShape_setRadius(tab[i], elementpoint->pnt->rayon);
		sfCircleShape_setOrigin(tab[i], vector2f(sfCircleShape_getRadius(tab[i]) , sfCircleShape_getRadius(tab[i]) ));
		sfCircleShape_setPosition(tab[i], vector2f(elementpoint->pnt->pix.x, elementpoint->pnt->pix.y) );
		sfCircleShape_setFillColor(tab[i], sfColor_fromRGBA(255, 255, 255, 0));
		sfCircleShape_setOutlineThickness(tab[i], 5);
		sfCircleShape_setOutlineColor(tab[i], sfBlack);
		elementpoint = elementpoint->suiv;

	}

}

void init_cluster_graph(tete_liste_logs *l, sfCircleShape*** tab )
{
	int i, j;
	element_liste_logs *element = l->suiv;
	element_liste_point *elementpoint;
	for(i=0; i<l->taille; i++)
	{
		if(element != NULL)
		{
			elementpoint = element->pt_cluster->suiv;
			for(j=0; j<element->pt_cluster->taille; j++)
			{
				if(elementpoint != NULL)
				{
					tab[i][j] = sfCircleShape_create();
					sfCircleShape_setRadius(tab[i][j], elementpoint->pnt->rayon);
					sfCircleShape_setOrigin(tab[i][j], vector2f(sfCircleShape_getRadius(tab[i][j]) , sfCircleShape_getRadius(tab[i][j]) ));
					sfCircleShape_setPosition(tab[i][j], vector2f(elementpoint->pnt->pix.x, elementpoint->pnt->pix.y) );
					sfCircleShape_setFillColor(tab[i][j], sfColor_fromRGBA(element->color.r, element->color.g, element->color.b, 128));
					sfCircleShape_setOutlineThickness(tab[i][j], 5);
					sfCircleShape_setOutlineColor(tab[i][j], sfColor_fromRGB(element->color.r, element->color.g, element->color.b));
					elementpoint = elementpoint->suiv;
				}
			}
			element = element->suiv;
		}
	}
}

void init_point(tete_liste_point *l, sfCircleShape** tab, sfVertexArray *vertexArray)
{
	int i;
	sfVertex *vertexTab = init_vertex(l->taille);
	element_liste_point *element = l->suiv;
	for(i=0; i<l->taille; i++)
	{
		if(element != NULL)
		{
			/* Création des sprites/formes correspondant aux points */
			tab[i] = sfCircleShape_create();
			sfCircleShape_setRadius(tab[i], RADIUS);
			sfCircleShape_setOrigin(tab[i], vector2f(sfCircleShape_getRadius(tab[i]) , sfCircleShape_getRadius(tab[i]) ));
			sfCircleShape_setPosition(tab[i], vector2f(element->pnt->pix.x, element->pnt->pix.y) );
			sfCircleShape_setFillColor(tab[i], sfColor_fromRGB(element->pnt->nom_fichier->color.r, element->pnt->nom_fichier->color.g, element->pnt->nom_fichier->color.b));

			/* Création des routes reliant les points */
			vertexTab[i].position = vector2f(element->pnt->pix.x, element->pnt->pix.y);
			vertexTab[i].color = sfBlack;
			sfVertexArray_append(vertexArray, vertexTab[i]);

			element = element->suiv;
		}
	}
}
