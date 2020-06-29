/*!
* \author Vincent Mozziconacci
* \verion 5.0
* \file init.h
* \brief Fonctions relatives à l'initialisation des structures et elements necessaires à la visualisation
*/

#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

/**
 * \vector2f(float x, float y)
 * \brief Initialise une structure spécifique à la SFML contenant deux coordonnées 
 *	Cette fonction cruciale existe dans la version C++ de la SFML mais est absente de la version C
 * \param x : Coordonnée x
 * \param y : Coordonnée y
 * \return sfVector2f structure de coordonnée spécifique à la SFML
 */

sfVector2f vector2f(float x, float y);

/**
 * \view_getRect(float zoomFactor, sfView *view)
 * \brief Renvoie le rectangle representant les limites de la vue courante
 *	Cette fonction  existe dans la version C++ de la SFML mais est absente de la version C
 * \param zoomFactor : niveau de zoom
 * \param view : vue courante
 * \return sfFloatRect structure representant un rectangle, specifique à la SFML
 */

sfFloatRect view_getRect(float zoomFactor, sfView *view);

/**
 * \textureLoading(sfTexture *textTab[4][5])
 * \brief Charge en mémoire toutes les textures de la carte
 *
 * \param textTab Tableau de textures
 * \return 1 lorsque le chargement s'est executé correctement, 0 sinon
 */

int textureLoading(sfTexture *textTab[4][5]);

/**
 * \spriteLoading(sfSprite *spriteTab[4][5], sfTexture *textTab[4][5])
 * \brief Initialise tous les sprites correspondant à des parties de la carte
 *
 * \param spriteTab Tableau de sprites à initialiser
 * \param textTab Tableau de textures
 * \return 1 lorsque l'initialisation des sprites s'est executé correctement, 0 sinon
 */

int spriteLoading(sfSprite *spriteTab[4][5], sfTexture *textTab[4][5]);

/**
 * \init_text(char* string, sfFont *font, sfColor color, int taille)
 * \brief Initialise un texte
 *
 * \param string Chaine de caracteres a afficher
 * \param font Police d'ecriture a utiliser
 * \param color Couleur a associer au texte
 * \param taille Taille du texte
 * \return sfText* Texte initialisé
 */

sfText* init_text(char* string, sfFont *font, sfColor color, int taille);

/**
 * \init_icon(sfTexture *texture)
 * \brief Initialise une icone de l'interface, associe le sprite crée avec la texture en paramètre
 * 
 * \param texture Texture a associer au sprite
 * \return sfSprite* Sprite initialisé avec une texture
 */

sfSprite* init_icon(sfTexture *texture);

/**
 * \init_tab(tete_liste_point *l)
 * \brief Initialise un tableau de sprite en forme de cercle pour afficher les points , la taille est récupéré dans la liste de points
 * 
 * \param l Liste de points
 * \return sfCircleShape**  Tableau de sprite en forme de cercle
 */

sfCircleShape** init_tab(tete_liste_point *l);

/**
 * \init_point(tete_liste_point *l, sfCircleShape** tab, sfVertexArray* vertexArray)
 * \brief Associe les coordonnées des points de la liste avec le centre des cercles
 * 
 * \param l Liste de points
 * \param tab Tableau de sprites en forme de cercle
  * \param vertexArray Tableau de vertex (permet de tracer les routes, un vertex = un sommet)
 * \return void 
 */

void init_point(tete_liste_point *l, sfCircleShape** tab, sfVertexArray *vertexArray);

/**
 * \init_tab_cluster(tete_liste_point *l)
 * \brief Initialise un tableau de sprite en forme de cercle pour afficher les clusters, la taille est récupéré dans les liste de points
 * 
 * \param l Liste de listes de points
 * \return sfCircleShape***  Tableau a deux dimensions de sprite en forme de cercle
 */

sfCircleShape*** init_tab_cluster(tete_liste_logs *l);

/**
 * \init_cluster_graph(tete_liste_logs *l, sfCircleShape*** tab )
 * \brief Associe les coordonnées des points des listes avec le centre des cercles
 * 
 * \param l Liste de listes de points
 * \param tab Tableau à deux dimensions de sprites en forme de cercle
 * \return void 
 */

void init_cluster_graph(tete_liste_logs *l, sfCircleShape*** tab );

/**
 * \init_cluster_temp(tete_liste_point *l, sfCircleShape** tab )
 * \brief Initialise les cluster temporels (issus de la fusion, fonction implémenté mais non-utilisé)
 * 
 * \param l Tete d'une liste de point
 * \param tab Tableau  de sprites en forme de cercle
 * \return void 
 */

void init_cluster_temp(tete_liste_point *l, sfCircleShape** tab );

/**
 * \init_vertex(int taille)
 * \brief Initialise un tableau de vertex
 * 
 * \param taille Taille du tableau de vertex à initialiser
 * \param 
 * \return sfVertex* Tableau de vertex
 */

sfVertex* init_vertex(int taille);

#endif