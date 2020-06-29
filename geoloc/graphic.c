#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Audio.h>
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
#include "stat_graph.h"
#include "logs.h"

int graphic(tete_liste_point *l, tete_liste_logs *l_logs, tete_liste_point *l_cluster)
{
	sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
	sfRenderWindow* window;
	sfEvent event;
	sfView *view;
	sfTexture *background, *loadingTexture;
	sfSprite *bgSprite, *loadingSprite;
	sfClock *animClock, *mapClock, *animClock2;
	element_liste_point *tmp;
	int unixTime = 0;
	char buffer[80];
	int nbClic = 0;
	int alpha = 0;

	int i, j, k;
	float zoomFactor = 1;
	float drawSpeed;
	float echelle = 2;

	/* Booléens */
	int drawSprite = 0;
	int drawClusterinfo = 0;
	int cinematicMode = 0;
	int drawAll = 0;
	int drawCluster = 0;
	int drawLog = 0;
	int drawRoad = 0;
	int drawMenu = 1;
	int drawHelp = 0;
	int drawAbout = 0;
	int fondu = 1;
	int drawClusterTemp = 0;
	int lock = 0;

	/* Tableau de points (Vertex) */
	sfVertexArray *vertexArray = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(vertexArray, sfLinesStrip);
	sfVertex *vertexTab = init_vertex(l->taille);

	/* Graphique des statistiques */

	sfVertexArray *quadArray = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(quadArray, sfQuads);

    int offsetGraph = 0;
    float maxFactor = 100, factor = maxFactor;
    float ratio = 0.8;
    float winl = 256;
    float size = (winl/24-34/24);

	/* Coordonnées */
	sfVector2f offset, worldPos, centerView, defaultCenter, center, viewSize, mousePosWorld, posCluster;
	sfVector2i mousePos, localPos, point;
	sfFloatRect rectView, rectSprite, rectHome;
	sfIntRect rectIntSprite;

    /* Création de la fenêtre de rendu */
	window = sfRenderWindow_create(mode, "Geoloc", sfClose | sfResize, NULL);
	if (!window)
		return EXIT_FAILURE;

	/* Création de la caméra */
	view = sfView_create();
	if(!view)
		return EXIT_FAILURE;
  
	animClock =sfClock_create();
	if(!animClock)
		return EXIT_FAILURE;

	mapClock = sfClock_create();
	if(!mapClock)
		return EXIT_FAILURE;

	animClock2 = sfClock_create();

	/* Création de la police d'écriture */

	sfFont *font = sfFont_createFromFile("ressources/font/HelveticaNeueLTCom-Bd.ttf");
	if (!font)
		return EXIT_FAILURE;

     /* Texte de chargement */

	sfText *textLoading = init_text("CHARGEMENT DE LA CARTE", font, sfColor_fromRGB(236, 240, 241), 60);
	if(!textLoading)
		return EXIT_FAILURE;

	/* Initialisation des sprites et textures de l'interface */

	sfTexture *barre_text = sfTexture_createFromFile("ressources/icons/barre.png", NULL);
	sfSprite *barre = init_icon(barre_text);

	sfTexture *play_text = sfTexture_createFromFile("ressources/icons/play.png", NULL);
	sfSprite *play = init_icon(play_text);

	sfTexture *stop_text = sfTexture_createFromFile("ressources/icons/stop.png", NULL);
	sfSprite *stop = init_icon(stop_text);

	sfTexture *fast_forward_text = sfTexture_createFromFile("ressources/icons/fast_forward.png", NULL);
	sfSprite *fast_forward = init_icon(fast_forward_text);

	sfTexture *pause_text = sfTexture_createFromFile("ressources/icons/pause.png", NULL);
	sfSprite *pause = init_icon(pause_text);

	sfTexture *home_text = sfTexture_createFromFile("ressources/icons/home.png", NULL);
	sfSprite *home = init_icon(home_text);

	sfTexture *rond_text = sfTexture_createFromFile("ressources/icons/rond.png", NULL);
	sfSprite *rond = init_icon(rond_text);

	sfTexture *arrow_text = sfTexture_createFromFile("ressources/icons/arrow.png", NULL);
	sfSprite *up = init_icon(arrow_text);
	sfSprite_setRotation(up, -90);

	sfSprite *down = init_icon(arrow_text);
	sfSprite_setRotation(down, 90);

	sfSprite *left = init_icon(arrow_text);
	sfSprite_setRotation(left, 180);

	sfSprite *right = init_icon(arrow_text);

	sfTexture *clock_text = sfTexture_createFromFile("ressources/icons/clock.png", NULL);
	sfSprite *clockIcon = init_icon(clock_text);

	sfSprite *barre2 = init_icon(barre_text);

	sfTexture *clusterBarre_text = sfTexture_createFromFile("ressources/icons/cluster_affichage.png", NULL);
	sfSprite *clusterBarre = init_icon(clusterBarre_text);

	sfTexture *anon_text = sfTexture_createFromFile("ressources/icons/anon.png", NULL);
	sfSprite *anon = init_icon(anon_text);

	sfTexture *cluster_text = sfTexture_createFromFile("ressources/icons/cluster.png", NULL);
	sfSprite *cluster = init_icon(cluster_text);

	sfSprite *cluster2 = init_icon(cluster_text);
	sfSprite_setColor(cluster2, sfColor_fromRGBA(255, 255, 255, 128));

	sfTexture *gps_text = sfTexture_createFromFile("ressources/icons/gps.png", NULL);
	sfSprite *gps = init_icon(gps_text);

	sfTexture *about_text = sfTexture_createFromFile("ressources/icons/about.png", NULL);
	sfSprite *about = init_icon(about_text);

	sfTexture *help_text = sfTexture_createFromFile("ressources/icons/help.png", NULL);
	sfSprite *help = init_icon(help_text);

	sfSprite *home2 = init_icon(home_text);

	sfTexture *dot_text = sfTexture_createFromFile("ressources/icons/point.png", NULL);
	sfSprite *dot = init_icon(dot_text);
	sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 128));

	sfTexture *road_text = sfTexture_createFromFile("ressources/icons/road.png", NULL);
	sfSprite *road = init_icon(road_text);
	sfSprite_setColor(road, sfColor_fromRGBA(255, 255, 255, 128));

	sfTexture *camera_text = sfTexture_createFromFile("ressources/icons/camera.png", NULL);
	sfSprite *camera = init_icon(camera_text);
	sfSprite_setColor(camera, sfColor_fromRGBA(255, 255, 255, 128));

	sfSprite *barre3 = init_icon(barre_text);





	/* Boolen etat de lancement */
	int chargement = 1;
	int menu = 0;

	/* Position du texte de chargement */
	sfFloatRect textRect = sfText_getLocalBounds(textLoading);
	sfText_setOrigin(textLoading, vector2f(textRect.left + textRect.width/2.0,textRect.top  + textRect.height/2.0));
	sfText_setPosition(textLoading, vector2f(WINDOW_WIDTH/2.0,WINDOW_HEIGHT/2.0 + 250));

	/* Tableaux de sprites et de textures de la map */
	sfTexture *textTab[4][5];
	sfSprite *spriteTab[4][5];

	/*Chargement des points GPS */
	sfCircleShape** tab = init_tab(l);
	init_point(l, tab, vertexArray);

	sfCircleShape*** clusterTab = init_tab_cluster(l_logs);
	init_cluster_graph(l_logs, clusterTab);

	sfCircleShape** clusterTabTemp = init_tab(l_cluster);
	init_cluster_temp(l_cluster, clusterTabTemp);

	int nbPoint = 1;

	/* Sprite de chargement */

	loadingSprite = sfSprite_create();
	loadingTexture=sfTexture_createFromFile("ressources/menu/geolocloading2.jpg", NULL);
	sfSprite_setTexture(loadingSprite, loadingTexture, 1);
	sfView_setSize(view, vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	/* Sprite de menu */
	sfSprite *menuLogo = sfSprite_create();
	sfTexture *menuLogoTexture = sfTexture_createFromFile("ressources/menu/geoloc.png", NULL);
	sfSprite_setTexture(menuLogo, menuLogoTexture, 1);

	sfSprite *menuAbout = sfSprite_create();
	sfTexture *menuAboutTexture = sfTexture_createFromFile("ressources/menu/geoloc_apropos.jpg", NULL);
	sfSprite_setTexture(menuAbout, menuAboutTexture, 1);

	sfSprite *menuHelp = sfSprite_create();
	sfTexture *menuHelpTexture = sfTexture_createFromFile("ressources/menu/geoloc_aide.jpg", NULL);
	sfSprite_setTexture(menuHelp, menuHelpTexture, 1);

	/* Conversion epoch -> date */
	char buf[80];
	time_t ts = (time_t) unixTime;
	struct tm date;
	date = *localtime(&ts);
	strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &date);

	/* Initialisation de l'horloge */
	sfText *horloge = init_text(buf, font, sfWhite, 24);

	/* Texte de l'interface */
	sfText *vitesse = init_text("1x", font, sfWhite, 24);
	sfText *nom_log = init_text("", font, sfWhite, 24);

	/* Texte de description des clusters */
	sfText *cluster_position = init_text("", font, sfWhite, 12);
	sfText *cluster_adresse = init_text("", font, sfWhite, 12);
	sfText *cluster_proprietaire = init_text("", font, sfWhite, 12);
	sfText *affluence1 = init_text("6h", font, sfWhite, 10);
	sfText *affluence2 = init_text("9h", font, sfWhite, 10);
	sfText *affluence3 = init_text("12h", font, sfWhite, 10);
	sfText *affluence4 = init_text("15h", font, sfWhite, 10);
	sfText *affluence5 = init_text("18h", font, sfWhite, 10);


	printf("\n *********** SFML LOOP *********** \n");

	/* Texte de menu */

	sfText *demarrage = init_text("Demarrage", font, sfWhite, 48);
	sfText *aboutText = init_text("A propos", font, sfWhite, 48);
	sfText *helpText = init_text("Aide", font, sfWhite, 48);

	sfView_setCenter(view, vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));


    /* Debut de la boucle de jeu */
	while (sfRenderWindow_isOpen(window))
	{
		/* Ecran de chargement de la carte */
		while(chargement)
		{
			sfRenderWindow_clear(window, sfBlack);

			sfRenderWindow_drawSprite(window, loadingSprite, NULL);
			sfRenderWindow_drawText(window, textLoading, NULL);

			sfRenderWindow_display(window);

			/* Chargement des textures de la carte */

			if(!textureLoading(textTab))
			{
				return EXIT_FAILURE;
			}


			if(!spriteLoading(spriteTab, textTab))
			{
				return EXIT_FAILURE;
			}

			/* Booléen qui marque la fin du chargement */
			chargement = 0;
			menu = 1;
		}
		//sfMusic_play(music);
		while(menu)
		{
			sfRenderWindow_setView(window, view);
			while (sfRenderWindow_pollEvent(window, &event))
			{
				if (event.type == sfEvtClosed)
				{
					sfRenderWindow_close(window);
					return 0;
				}
				if(event.type == sfEvtMouseButtonPressed)
				{
					if(event.key.code == sfMouseLeft)
					{
						mousePos.x = event.mouseButton.x;
						mousePos.y = event.mouseButton.y;

						mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mousePos, view);

						rectSprite = sfSprite_getGlobalBounds(gps);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							menu = 0;

							/*Vue par défault */
							sfView_setCenter(view, vector2f(14660, 8770) ); // Coordonnées de l'INSA
						}
						rectSprite = sfSprite_getGlobalBounds(about);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							drawAbout = 1;
							drawMenu = 0;

						}
						rectSprite = sfSprite_getGlobalBounds(help);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							drawHelp = 1;
							drawMenu = 0;
						}
						rectSprite = sfSprite_getGlobalBounds(home2);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{

							drawHelp = 0;
							drawAbout = 0;
							drawMenu = 1;
						}
					}
				}
				if(event.type == sfEvtMouseMoved)
				{
					mousePos.x = event.mouseMove.x;
					mousePos.y = event.mouseMove.y;

					mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mousePos, view);

					if(!fondu)
					{
						rectSprite = sfSprite_getGlobalBounds(gps);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							sfSprite_setColor(gps, sfColor_fromRGB(52, 152, 219));
						}
						else
						{
							sfSprite_setColor(gps, sfColor_fromRGB(255, 255, 255));
						}
						rectSprite = sfSprite_getGlobalBounds(about);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							sfSprite_setColor(about, sfColor_fromRGB(52, 152, 219));
						}
						else
						{
							sfSprite_setColor(about, sfColor_fromRGB(255, 255, 255));
						}
						rectSprite = sfSprite_getGlobalBounds(help);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							sfSprite_setColor(help, sfColor_fromRGB(52, 152, 219));
						}
						else
						{
							sfSprite_setColor(help, sfColor_fromRGB(255, 255, 255));
						}
						rectSprite = sfSprite_getGlobalBounds(home2);
						if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
						{
							sfSprite_setColor(home2, sfColor_fromRGB(52, 152, 219));
						}
						else
						{
							sfSprite_setColor(home2, sfColor_fromRGB(255, 255, 255));
						}
					}
				}
			}



			sfRenderWindow_clear(window, sfColor_fromRGB(46, 63, 81));

			sfVector2f centre = sfView_getCenter(view);

			sfSprite_setPosition(menuLogo, vector2f(355, 75));

			sfSprite_setPosition(gps, vector2f(centre.x - 200  , centre.y ));
			sfText_setPosition(demarrage, vector2f(centre.x- 120, centre.y ));

			sfSprite_setPosition(about, vector2f(centre.x - 200  , centre.y + 70));
			sfText_setPosition(aboutText, vector2f(centre.x- 120, centre.y + 70));

			sfSprite_setPosition(help, vector2f(centre.x - 200  , centre.y  + 140));
			sfText_setPosition(helpText, vector2f(centre.x - 120, centre.y + 140));

			sfSprite_setPosition(home2, vector2f(centre.x - 550 , centre.y + 250));


			if(sfTime_asSeconds(sfClock_getElapsedTime(animClock)) > 0.005)
			{
				if(alpha < 255)
				{
					alpha++;
					sfSprite_setColor(menuLogo, sfColor_fromRGBA(255, 255, 255, alpha));
					sfSprite_setColor(gps, sfColor_fromRGBA(255, 255, 255, alpha));
					sfSprite_setColor(about, sfColor_fromRGBA(255, 255, 255, alpha));
					sfSprite_setColor(help, sfColor_fromRGBA(255, 255, 255, alpha));

					sfText_setColor(demarrage, sfColor_fromRGBA(255, 255, 255, alpha));
					sfText_setColor(aboutText, sfColor_fromRGBA(255, 255, 255, alpha));
					sfText_setColor(helpText, sfColor_fromRGBA(255, 255, 255, alpha));
				}
				else
				{
					fondu = 0;
				}

				sfClock_restart(animClock);
			}

			if(drawMenu)
			{
				sfRenderWindow_drawSprite(window, menuLogo, NULL);
				sfRenderWindow_drawSprite(window, gps, NULL);
				sfRenderWindow_drawSprite(window, about, NULL);
				sfRenderWindow_drawSprite(window, help, NULL);
				sfRenderWindow_drawText(window, demarrage, NULL);
				sfRenderWindow_drawText(window, aboutText, NULL);
				sfRenderWindow_drawText(window, helpText, NULL);
			}

			if(drawAbout)
			{
				sfRenderWindow_drawSprite(window, menuAbout, NULL);
				sfRenderWindow_drawSprite(window, home2, NULL);
			}
			if(drawHelp)
			{
				sfRenderWindow_drawSprite(window, menuHelp, NULL);
				sfRenderWindow_drawSprite(window, home2, NULL);
			}

			sfRenderWindow_display(window);
			
		}

		sfRenderWindow_setView(window, view);
		viewSize = sfView_getSize(view);


		/* Placement de l'interface */

		rectView = view_getRect(zoomFactor, view); // Left = x, top = y

		sfSprite_setPosition(barre, vector2f(rectView.left, rectView.top + 600 * zoomFactor));
		sfSprite_setScale(barre, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(play, vector2f(rectView.left + 210 * zoomFactor , rectView.top + 610 * zoomFactor));
		sfSprite_setScale(play, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(fast_forward, vector2f(rectView.left + 310 * zoomFactor, rectView.top + 610 * zoomFactor));
		sfSprite_setScale(fast_forward, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(pause, vector2f(rectView.left + 120 * zoomFactor, rectView.top + 610 * zoomFactor));
		sfSprite_setScale(pause, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(stop, vector2f(rectView.left + 30 * zoomFactor, rectView.top + 610 * zoomFactor));
		sfSprite_setScale(stop, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(rond, vector2f(rectView.left + rectView.width - 230 * zoomFactor , rectView.top + rectView.height - 230 * zoomFactor));
		sfSprite_setScale(rond, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(home, vector2f(rectView.left + rectView.width - 160 * zoomFactor  , rectView.top + rectView.height - 165 * zoomFactor));
		sfSprite_setScale(home, vector2f(zoomFactor, zoomFactor));

		rectHome = sfSprite_getGlobalBounds(home);

		sfSprite_setPosition(up, vector2f(rectHome.left , rectHome.top - 20 * zoomFactor));
		sfSprite_setScale(up, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(left, vector2f(rectHome.left - 30 * zoomFactor, rectHome.top + 50 * zoomFactor));
		sfSprite_setScale(left, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(right, vector2f(rectHome.left + 70 * zoomFactor, rectHome.top));
		sfSprite_setScale(right, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(down, vector2f(rectHome.left + 50 * zoomFactor , rectHome.top + 70 * zoomFactor));
		sfSprite_setScale(down, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(barre2, vector2f(rectView.left + rectView.width - 400 * zoomFactor, rectView.top));
		sfSprite_setScale(barre2, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(clockIcon, vector2f(rectView.left + rectView.width - 370 * zoomFactor, rectView.top + 10 * zoomFactor));
		sfSprite_setScale(clockIcon, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(horloge, vector2f(rectView.left + rectView.width - 300 * zoomFactor, rectView.top + 20 * zoomFactor));
		sfText_setScale(horloge, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(vitesse, vector2f(rectView.left + 270* zoomFactor , rectView.top + 620 * zoomFactor));
		sfText_setScale(vitesse, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(nom_log, vector2f(rectView.left + rectView.width - 300 * zoomFactor, rectView.top + 80 * zoomFactor));
		sfText_setScale(nom_log, vector2f(zoomFactor, zoomFactor));

		rectSprite = sfSprite_getGlobalBounds(clusterBarre);

		sfSprite_setPosition(cluster, vector2f(rectSprite.left + (rectSprite.width / 2) - 30*zoomFactor, rectSprite.top + 10 * zoomFactor));
		sfSprite_setScale(cluster, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(anon, vector2f(rectSprite.left + (rectSprite.width / 2) - 30*zoomFactor, rectSprite.top + rectSprite.height - 60*zoomFactor ));
		sfSprite_setScale(anon, vector2f(zoomFactor, zoomFactor));

		sfSprite_setScale(clusterBarre, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(cluster_position, vector2f(rectSprite.left + 10 * zoomFactor , rectSprite.top + 70 * zoomFactor));
		sfText_setScale(cluster_position, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(cluster_adresse, vector2f(rectSprite.left + 10 * zoomFactor , rectSprite.top + 100 * zoomFactor));
		sfText_setScale(cluster_adresse, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(cluster_proprietaire, vector2f(rectSprite.left + 10 * zoomFactor , rectSprite.top + 130 * zoomFactor));
		sfText_setScale(cluster_proprietaire, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(affluence1, vector2f(rectSprite.left + 75 * zoomFactor , rectSprite.top + 290 * zoomFactor));
		sfText_setScale(affluence1, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(affluence2, vector2f(rectSprite.left + 110 * zoomFactor , rectSprite.top + 290 * zoomFactor));
		sfText_setScale(affluence1, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(affluence3, vector2f(rectSprite.left + 145 * zoomFactor , rectSprite.top + 290 * zoomFactor));
		sfText_setScale(affluence2, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(affluence4, vector2f(rectSprite.left + 180 * zoomFactor , rectSprite.top + 290 * zoomFactor));
		sfText_setScale(affluence3, vector2f(zoomFactor, zoomFactor));

		sfText_setPosition(affluence5, vector2f(rectSprite.left + 215 * zoomFactor , rectSprite.top + 290 * zoomFactor));
		sfText_setScale(affluence4, vector2f(zoomFactor, zoomFactor));


		sfText_setString(horloge, buf);

		sfSprite_setPosition(barre3, vector2f(rectView.left , rectView.top));
		sfSprite_setScale(barre3, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(dot, vector2f(rectView.left + 30 * zoomFactor, rectView.top + 10 * zoomFactor ));
		sfSprite_setScale(dot, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(cluster2, vector2f(rectView.left + 120 * zoomFactor, rectView.top + 10 * zoomFactor ));
		sfSprite_setScale(cluster2, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(road, vector2f(rectView.left + 210 * zoomFactor , rectView.top + 10 * zoomFactor ));
		sfSprite_setScale(road, vector2f(zoomFactor, zoomFactor));

		sfSprite_setPosition(camera, vector2f(rectView.left + 310 * zoomFactor, rectView.top + 10 * zoomFactor ));
		sfSprite_setScale(camera, vector2f(zoomFactor, zoomFactor));


        /* Gestion des événements */
		while (sfRenderWindow_pollEvent(window, &event))
		{

			centerView = sfView_getCenter(view);

			/* Recuperation des coordonnes  de la souris */

			localPos = sfMouse_getPosition( (sfWindow*) window); //Coordonnées locales
			worldPos = sfRenderWindow_mapPixelToCoords(window, localPos, view); //Coordonnées globales : sur la map


            /* Close window : exit */
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}
			if(event.type == sfEvtKeyPressed)
			{
				switch(event.key.code)
				{
					//Fermeture de la fenêtre
					case sfKeyEscape:
					sfRenderWindow_close(window);
					break;

					/* Gestion des déplacements avec le clavier */
					case sfKeyUp:
					offset.x = 0;
					offset.y = -OFFSET;
					sfView_move(view, offset);
					break;

					case sfKeyDown:
					offset.x = 0;
					offset.y = OFFSET;
					sfView_move(view, offset);
					break;

					case sfKeyLeft:
					offset.x = -OFFSET;
					offset.y = 0;
					sfView_move(view, offset);
					break;

					case sfKeyRight:
					offset.x = OFFSET;
					offset.y = 0;
					sfView_move(view, offset);
					break;

					case sfKeySpace:
					sfView_setCenter(view, vector2f(14660, 8770));
					break;

					case sfKeyF1:
					if(drawAll)
					{
						drawAll = 0;
						sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 128));
					}
					else
					{
						drawAll = 1;
						drawSprite = 0;
						drawLog = 0;
						nbPoint = 0;
						sfText_setString(vitesse, "1x");

						ts = (time_t) unixTime;
						date = *localtime(&ts);
						strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &date);
						drawSpeed = 1;
						sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 255));
					}
					break;

					case sfKeyF2:
					if(drawCluster)
					{
						drawCluster = 0;
						sfSprite_setColor(cluster2, sfColor_fromRGBA(255, 255, 255, 128));
					}
					else
					{
						drawCluster = 1;
						sfSprite_setColor(cluster2, sfColor_fromRGBA(255, 255, 255, 255));
					}
					break;

					case sfKeyF3:
					if (drawRoad)
					{
						drawRoad = 0;
						sfSprite_setColor(road, sfColor_fromRGBA(255, 255, 255, 128));
					}
					else
					{
						drawRoad = 1;
						sfSprite_setColor(road, sfColor_fromRGBA(255, 255, 255, 255));
					}
					break;

					case sfKeyF4:
					if(cinematicMode)
					{
						cinematicMode = 0;
						sfSprite_setColor(camera, sfColor_fromRGBA(255, 255, 255, 128));
					}
					else
					{
						cinematicMode = 1;
						sfSprite_setColor(camera, sfColor_fromRGBA(255, 255, 255, 255));
					}
					break;

					case sfKeyF5:
					if(drawClusterTemp)
					{
						drawClusterTemp = 0;
					}
					else
					{
						drawClusterTemp = 1;
					}
					break;

					default:
					break;
				}
			}
			if(event.type == sfEvtMouseWheelScrolled)
			{

				/* Gestion du zoom*/
				
				if(event.mouseWheelScroll.delta >0 ) //Zoom avant
				{
					if(zoomFactor > 0.5)
					{
						sfView_zoom(view, 1/ZOOM);
						zoomFactor *= 1/ZOOM;
						point.x = event.mouseWheelScroll.x;
						point.y = event.mouseWheelScroll.y;
						center = sfRenderWindow_mapPixelToCoords(window, point, view);
						sfView_setCenter(view, center);
					}
				}
				else //Zoom arriere
				{
					sfView_zoom(view, ZOOM);
					zoomFactor *= ZOOM;
					rectView = view_getRect(zoomFactor, view);
					if(rectView.left <0  || rectView.top <0 || rectView.left > 20000 - rectView.width || rectView.top > 16000 - rectView.height)
					{
						sfView_zoom(view, 1/ZOOM);
						zoomFactor *=1/ZOOM;
						rectView = view_getRect(zoomFactor, view);
					}
				}
				if(drawClusterinfo)
				{

					offsetGraph = 0;
					sfVertexArray_clear(quadArray);
					for(i=0; i<24; i++)
					{			
						sfFloatRect rectTest = sfSprite_getGlobalBounds(clusterBarre);
						factor = tmp->pnt->tab_heure[i][1] * 20;
						if(factor == 0)
						{
							factor = 5;
						}
						buildQuad(quadArray, offsetGraph, factor, size, rectTest, zoomFactor);
						offsetGraph = offsetGraph + (size + 5);
					}
				}
			}
			if(event.type == sfEvtMouseButtonPressed)
			{
				if(event.mouseButton.button == sfMouseLeft)
				{
					/* Recuperation des coordonnées du clic gauche */

					mousePos.x = event.mouseButton.x;
					mousePos.y = event.mouseButton.y;

					mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mousePos, view);


					//Retour à la position par défaut
					rectSprite = sfSprite_getGlobalBounds(home);
					if ( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y)   )
					{
						sfView_setCenter(view, vector2f(14660, 8770));
					}
					rectSprite = sfSprite_getGlobalBounds(up);
					if ( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y)   )
					{
						sfView_move(view, vector2f(0, -100));
					}
					rectSprite = sfSprite_getGlobalBounds(down);
					if ( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y)   )
					{
						sfView_move(view, vector2f(0, 100));	
					}
					rectSprite = sfSprite_getGlobalBounds(left);
					if ( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y)   )
					{
						sfView_move(view, vector2f(-100, 0));	
					}
					rectSprite = sfSprite_getGlobalBounds(right);
					if ( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y)   )
					{
						sfView_move(view, vector2f(100, 0));
					}
					//Lancement du dessin des points
					rectSprite = sfSprite_getGlobalBounds(play);
					if( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y) )
					{
						drawSprite = 1;
						drawSpeed = 1;
					}
					//Arrêt du dessin des points
					rectSprite = sfSprite_getGlobalBounds(pause);
					if( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y) )
					{
						drawSpeed = 1000000;
					}
					//Acceleration du dessin des points
					rectSprite = sfSprite_getGlobalBounds(fast_forward);
					if( sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y) )
					{
						if(drawSpeed > 0.125)
						{
							drawSpeed /= 2;
						}
						else
						{
							drawSpeed = 1;
						}
						if(drawSpeed == 1)
						{
							sfText_setString(vitesse, "1x");
						}
						if(drawSpeed == 0.5)
						{
							sfText_setString(vitesse, "2x");
						}
						if(drawSpeed == 0.25)
						{
							sfText_setString(vitesse, "4x");
						}
						if(drawSpeed == 0.125)
						{
							sfText_setString(vitesse, "8x");
						}
					}
					rectSprite = sfSprite_getGlobalBounds(stop);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						nbPoint = 0;
						drawSprite = 0;
						drawLog = 0;
						sfText_setString(vitesse, "1x");

						ts = (time_t) unixTime;
						date = *localtime(&ts);
						strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &date);
						drawSpeed = 1;

						if(sfTime_asSeconds(sfClock_getElapsedTime(animClock2)) < 0.5)
						{
							sfSprite_setColor(stop, sfColor_fromRGB(41, 128, 185));
						}
					}
					rectSprite = sfSprite_getGlobalBounds(anon);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						element_liste_logs *element = l_logs->suiv;
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
										rectSprite = sfCircleShape_getGlobalBounds(clusterTab[i][j]);
										if(sfFloatRect_contains(&rectSprite, posCluster.x, posCluster.y))
										{
											if(sfFloatRect_contains(&rectSprite, elementpoint->pnt->pix.x, elementpoint->pnt->pix.y))
											{
												supprimer_cluster(element, elementpoint);
												clusterTab = init_tab_cluster(l_logs);
												init_cluster_graph(l_logs, clusterTab);
												l = init_liste_temporelle(l_logs);
												tab = init_tab(l);
												sfVertexArray_clear(vertexArray);
												init_point(l, tab, vertexArray);
												drawClusterinfo = 0;
												nbClic = 0;
												sfVertexArray_clear(quadArray);
												break;
											}
										}
										elementpoint = elementpoint->suiv;
									}
								}
								element = element->suiv;
							}
						}
					}
					rectSprite = sfSprite_getGlobalBounds(dot);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						if(drawAll)
						{
							drawAll = 0;
							sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 128));
						}
						else
						{
							drawAll = 1;
							drawSprite = 0;
							drawLog = 0;
							nbPoint = 0;
							sfText_setString(vitesse, "1x");
							ts = (time_t) unixTime;
							date = *localtime(&ts);
							strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &date);
							drawSpeed = 1;
							sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 255));
						}
					
					}
					rectSprite = sfSprite_getGlobalBounds(cluster2);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						if(drawCluster)
						{
							drawCluster = 0;
							sfSprite_setColor(cluster2, sfColor_fromRGBA(255, 255, 255, 128));
						}
						else
						{
							drawCluster = 1;
							sfSprite_setColor(cluster2, sfColor_fromRGBA(255, 255, 255, 255));
						}

					}
					rectSprite = sfSprite_getGlobalBounds(road);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						if (drawRoad)
						{
							drawRoad = 0;
							sfSprite_setColor(road, sfColor_fromRGBA(255, 255, 255, 128));
						}
						else
						{
							drawRoad = 1;
							sfSprite_setColor(road, sfColor_fromRGBA(255, 255, 255, 255));
						}
					}
					rectSprite = sfSprite_getGlobalBounds(camera);
					if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
					{
						if (cinematicMode)
						{
							cinematicMode = 0;
							sfSprite_setColor(camera, sfColor_fromRGBA(255, 255, 255, 128));
						}
						else
						{
							cinematicMode = 1;
							sfSprite_setColor(camera, sfColor_fromRGBA(255, 255, 255, 255));
						}

					}
				}
				if(event.mouseButton.button == sfMouseRight)
				{
					mousePos.x = event.mouseButton.x;
					mousePos.y = event.mouseButton.y;

					mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mousePos, view);

					if(nbClic == 0 && drawCluster == 1)
					{
						nbClic++;
						element_liste_logs *element = l_logs->suiv;
						element_liste_point *elementpoint;

						for(i=0; i<l->taille; i++)
						{
							if(element != NULL)
							{
								elementpoint = element->pt_cluster->suiv;
								for(j=0; j<element->pt_cluster->taille; j++)
								{
									rectSprite = sfCircleShape_getGlobalBounds(clusterTab[i][j]);
									if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
									{
										posCluster.x = mousePosWorld.x;
										posCluster.y = mousePosWorld.y;
										if(!lock)
										{
											if(sfFloatRect_contains(&rectSprite, elementpoint->pnt->pix.x, elementpoint->pnt->pix.y))
											{
												tmp = elementpoint;
												drawClusterinfo = 1;
												sprintf(buffer,"Longitude : %f Latitude : %f", elementpoint->pnt->ign->pos.lon, elementpoint->pnt->ign->pos.lat);
												sfText_setString(cluster_position, buffer);
												sprintf(buffer, "Adresse : %s %s %s ", elementpoint->pnt->ign->num, elementpoint->pnt->ign->nom_voie, elementpoint->pnt->ign->code_postal);
												sfText_setString(cluster_adresse, buffer);
												sprintf(buffer, "Log : %s ", element->id);
												sfText_setString(cluster_proprietaire, buffer);
												sfText_setColor(cluster_proprietaire, sfColor_fromRGB(element->color.r, element->color.g, element->color.b));
												sfSprite_setPosition(clusterBarre, vector2f( rectSprite.left + rectSprite.width , rectSprite.top));
												offsetGraph = 0;
												int max = max_tab(elementpoint->pnt->tab_heure);
												for(k=0; k<24; k++)
												{
													sfFloatRect rectTest = sfSprite_getGlobalBounds(clusterBarre);
													factor = (130 * elementpoint->pnt->tab_heure[k][1]) / max;
													if(factor == 0)
													{
														factor = 5;
													}
													buildQuad(quadArray, offsetGraph, factor, size, rectTest, zoomFactor);
													offsetGraph = offsetGraph + (size + 2.5);
												}
												lock = 1;
											}
										}
									}
									elementpoint = elementpoint->suiv;
								}
								element = element->suiv;
							}
						}
					}
					else
					{
						drawClusterinfo = 0;
						nbClic = 0;
						sfVertexArray_clear(quadArray);
					}
					lock = 0;
				}
			}	
			if(event.type == sfEvtMouseMoved && sfMouse_isButtonPressed(sfMouseLeft))
			{

				/* Deplacement de la camera avec la souris */
				
				offset.x = mousePos.x - event.mouseMove.x;
				offset.y = mousePos.y - event.mouseMove.y;
				sfView_move(view, offset);

				sfVector2i mouseLoc;
				mouseLoc.x = event.mouseMove.x;
				mouseLoc.y = event.mouseMove.y;

				mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mouseLoc, view);


				/* Gestion des limites de la map */

				if(centerView.x + offset.x < viewSize.x / 2)
				{
					defaultCenter.x = viewSize.x / 2;
					defaultCenter.y = centerView.y;
					sfView_setCenter(view, defaultCenter);
				}
				if(centerView.x + offset.x > 20000 - viewSize.x / 2)
				{
					defaultCenter.x = 20000 - viewSize.x / 2;
					defaultCenter.y = centerView.y;
					sfView_setCenter(view, defaultCenter);
				}
				if(centerView.y + offset.y < viewSize.y / 2)
				{
					defaultCenter.x = centerView.x;
					defaultCenter.y = viewSize.y / 2;
					sfView_setCenter(view, defaultCenter);
				}
				if(centerView.y + offset.y > 16000 - viewSize.y / 2)
				{
					defaultCenter.x = centerView.x;
					defaultCenter.y = 16000 - viewSize.y / 2;
					sfView_setCenter(view, defaultCenter);
				}
			}
			if(event.type == sfEvtMouseMoved)
			{
				sfVector2i mouseLoc;
				mouseLoc.x = event.mouseMove.x;
				mouseLoc.y = event.mouseMove.y;

				mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mouseLoc, view);

				rectSprite = sfSprite_getGlobalBounds(anon);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(anon, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(anon, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(stop);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(stop, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(stop, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(play);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(play, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(play, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(pause);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(pause, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(pause, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(fast_forward);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(fast_forward, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(fast_forward, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(up);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(up, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(up, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(down);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(down, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(down, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(left);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(left, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(left, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(right);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(right, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(right, sfColor_fromRGB(255, 255, 255));
				}
				rectSprite = sfSprite_getGlobalBounds(home);
				if(sfFloatRect_contains(&rectSprite, mousePosWorld.x, mousePosWorld.y))
				{
					sfSprite_setColor(home, sfColor_fromRGB(52, 152, 219));
				}
				else
				{
					sfSprite_setColor(home, sfColor_fromRGB(255, 255, 255));
				}
			}
		}


		/* Nettoyage de la fenêtre de rendu */
		sfRenderWindow_clear(window, sfWhite);

		/* Dessin */

		/* Maj du rectangle de vue */
		rectView = view_getRect(zoomFactor, view);


		/* Dessin de la map */
		for(i=0; i<4; i++)
		{
			for(j=0; j<5; j++)
			{
				rectSprite = sfSprite_getGlobalBounds(spriteTab[i][j]);
				if(sfFloatRect_intersects(&rectSprite, &rectView, NULL) )
				{
					sfRenderWindow_drawSprite(window, spriteTab[i][j], NULL);
				}
			}
		}
		

		/* Animation */

		element_liste_point *element = l->suiv;
		if(drawSprite)
		{
			drawAll = 0;
			drawLog = 1;
			for(i=0; i<nbPoint; i++)
			{
				sfVector2f scale = sfCircleShape_getScale(tab[i]);
				if(scale.x > 1 && scale.y > 1 && sfTime_asSeconds(sfClock_getElapsedTime(animClock)) > drawSpeed)
				{
					sfCircleShape_setScale(tab[i], vector2f(scale.x - 0.3, scale.y - 0.3));
				}
				sfCircleShape_setScale(tab[nbPoint], vector2f(7, 7));

				/* Tracé des points */
				sfRenderWindow_drawCircleShape(window, tab[i], NULL);
				sfText_setString(nom_log,element->pnt->nom_fichier->id);
				sfText_setColor(nom_log, sfColor_fromRGB(element->pnt->nom_fichier->color.r, element->pnt->nom_fichier->color.g, element->pnt->nom_fichier->color.b));
		
				/* Mode "cinematique" */
				if(cinematicMode)
				{
					sfView_setCenter(view, vector2f(element->pnt->pix.x, element->pnt->pix.y));
				}

				/* Actualisation de l'heure */
				ts = (time_t) element->pnt->id;
				date = *localtime(&ts);
				strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &date);
				element = element->suiv;
			}
			if(sfTime_asSeconds(sfClock_getElapsedTime(animClock)) > drawSpeed && nbPoint < l->taille)
			{
				nbPoint++;
				if(echelle > 1)
				{
					echelle = echelle - 0.2;
				}
				sfClock_restart(animClock);
			}
		}

		/* Dessin de tous les points */

		if(drawAll)
		{
			for(i=0; i<l->taille; i++)
			{
				sfRenderWindow_drawCircleShape(window, tab[i], NULL);
			}
		}
		else
		{
			sfSprite_setColor(dot, sfColor_fromRGBA(255, 255, 255, 128));
		}

		/* Dessin de tous les clusters */

		if(drawCluster)
		{
			element_liste_logs *elementlog = l_logs->suiv;
			for(i=0; i<l_logs->taille; i++)
			{
				if(elementlog != NULL)
				{
					for(j=0; j<elementlog->pt_cluster->taille; j++)
					{
						sfRenderWindow_drawCircleShape(window, clusterTab[i][j], NULL);
					}
					elementlog = elementlog->suiv;
				}
			}
		}

		if(drawClusterTemp)
		{
			sfRenderWindow_drawCircleShape(window, clusterTabTemp[i], NULL);
		}

		/* Dessin des routes */

		if(drawRoad)
		{
			sfRenderWindow_drawVertexArray(window, vertexArray, NULL);
		}


		/* Dessin des infos du cluster */

		if(drawClusterinfo)
        {
        	sfRenderWindow_drawSprite(window, clusterBarre, NULL);
        	sfRenderWindow_drawSprite(window, anon, NULL);
        	sfRenderWindow_drawSprite(window, cluster, NULL);
        	sfRenderWindow_drawText(window, cluster_position, NULL);
        	sfRenderWindow_drawText(window, cluster_adresse, NULL);
        	sfRenderWindow_drawText(window, cluster_proprietaire, NULL);
        	sfRenderWindow_drawText(window, affluence1, NULL);
        	sfRenderWindow_drawText(window, affluence2, NULL);
        	sfRenderWindow_drawText(window, affluence3, NULL);
        	sfRenderWindow_drawText(window, affluence4, NULL);
        	sfRenderWindow_drawText(window, affluence5, NULL);
        	for(i=0; i<24; i++)
       		{
        		sfRenderWindow_drawVertexArray(window, quadArray, NULL);
        	}
        }


		/* Dessin de l'interface */

        sfRenderWindow_drawSprite(window, barre, NULL);
        sfRenderWindow_drawSprite(window, play, NULL);
        sfRenderWindow_drawSprite(window, fast_forward, NULL);
        sfRenderWindow_drawSprite(window, pause, NULL);
        sfRenderWindow_drawSprite(window, stop, NULL);
        sfRenderWindow_drawSprite(window, rond, NULL);
        sfRenderWindow_drawSprite(window, home, NULL);
        sfRenderWindow_drawSprite(window, up, NULL);
        sfRenderWindow_drawSprite(window, left, NULL);
        sfRenderWindow_drawSprite(window, right, NULL);
        sfRenderWindow_drawSprite(window, down, NULL);
        sfRenderWindow_drawSprite(window, barre2, NULL);
        sfRenderWindow_drawSprite(window, clockIcon, NULL);
        sfRenderWindow_drawSprite(window, barre3, NULL);
        sfRenderWindow_drawSprite(window, dot, NULL);
        sfRenderWindow_drawSprite(window, cluster2, NULL);
        sfRenderWindow_drawSprite(window, road, NULL);
        sfRenderWindow_drawSprite(window, camera, NULL);

        sfRenderWindow_drawText(window, horloge, NULL);
        sfRenderWindow_drawText(window, vitesse, NULL);

        if(drawLog)
        {
        	sfRenderWindow_drawText(window, nom_log, NULL);
        }




        /* MAJ de la fenêtre de rendu */
		sfRenderWindow_display(window);
	}

	return 0;
}


       
