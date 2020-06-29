/*!
* \author {Hugo Joby,Vincent Mozziconacci} 
* \verion 5.8
* \file main.c
* \brief Fichier Main.
*/

/*! \mainpage <H1>Projet Geoloc</H1> <IMG SRC="icon_geoloc_web.png"> 
 * 
 * \section intro_sec  Geoloc STI 3A 2017
 *
 * 
 *
 * Bienvenue sur la documentation du projet Geoloc ! 
 * Projet realise par Amine Allouche, Hugo Joby, Farouk Mounim et Vincent Mozziconacci dans le cadre 
 * de la 1ere annee de Securite et Technologies Informatique.
 * \section install_sec Installation et Pre-requis
 *   
 * 
 * Installer les paquets nécessaires à la CSFML (paquet SFML puis paquet CSFML) en utilisant un gestionnaire de paquet linux, commandes : sudo apt install libsfml-dev libcsfml-dev
 * ATTENTION : Le projet geoloc necessite la version 2.3 du paquet libcsfml-dev
 *
 * \section install_sec  Instructions
 * \subsection step1 Etape 1: Importer les logs 
 *
 *
 * Pour Importer ses propres logs, c'est simple, il suffit des les exporter depuis l'application Geoloc disponible sur Smartphone,
 * et de les placer dans le dossier "Logs" situe dans geoloc/logs.
 * 
 * \subsection step2 Etape 2: Lancer Geoloc
 * 
 *
 * Pour lancer geoloc il suffit de lancer l'executable de geoloc. Une fenetre avec un menu s'ouvre ainsi et vous proposent differents choix.
 * Vous pouvez : 
 *               - Lancer la visualisation de la carte et de vos logs
 *               - Consulter l'aide , pour voir les raccourcis et les commandes
 *               - Consulter le "A propos"
 *
 * \subsection step3 Etape 3: Utiliser Geoloc
 *  Une fois dans l'application, vous pouvez librement vous déplacer sur la carte grace à la souris, aux flèches directionnelles ou au bouton "flèches de l'interface", il est possible de zoomer et dézoomer à l'aide la molette de la souris.
 *
 * Le panneau en haut à gauche gère les différents éléments d'affichage, respectivement l'affichage des points, clusters, routes, ainsi qu'un mode cinématique
 * activable ou non fixant la caméra sur les points qui s'affichent 
 *
 * Le panneau en Bas à droite lui, vous offre la possibilité de manipuler le temps, en pouvant dans l'ordre réinitialisé le temps, mettre sur pause
 * lancer l'animation, et choisir la vitesse ( clics multiples )
 * Tous les points de tous les logs placés dans le dossier log sont chargés et affichés dans l'ordre chronologique
 * 
 * Un clic droit sur un cluster permet d'afficher toutes les informations relatives à celui ci :
 *  - Position en lat/lon
 *  - Adresse complète
 *  - Log de provenance
 *  - Un diagramme d'affluence : fréquentation en fonction de tranches horaires
 * 
 * Enfin un bouton d'anonymisation en bas du panneau permettant de supprimer le cluster, les points à l'intérieur et les routes qui y mène
 * La suppression génère un nouveau fichier log anonymisé avec le suffixe _anon dans le dossier log
 * 
 * Note à l'utilisateur : Suite à une anonymisation de log, on retrouvre le log anonymisé dans le dossier log avec le suffixe _anon.
 * Il est possible en cas de surcharge que ces fichiers _anon génèrent des interférences aves les logs classiques.
 * Il faut donc les déplacer hors du dossier "log"
 * 
 *
 * Bugs connus :
 * -Deformation du diagramme lors d'un zoom
 *
 * Documentation réalisée par Hugo JOBY et Vincent MOZZICONACCI.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "fichier.h"
#include "liste_point.h"
#include "cluster.h"
#include "graphic.h"
#include "route.h"
#include "logs.h"

#define size_max 4096
#define taille_fichier 50
#define bufsize 50
#define epsilon 0.000400
#define MinPoint 5
//#define epsilon 0.001000

int main(int argc, char **argv)
{
    system("../index/index");
    srand(time(NULL));
    FILE *f, *f1;
    tete_liste_point *pt;
    tete_liste_point *pt_cluster;
    tete_liste_route *pt_route;
    pt = init_liste();
    char *fichier = malloc(taille_fichier*sizeof(char));
    tete_liste_logs *liste_retour = insertion_logs();
    tete_liste_point *liste_temp = init_liste_temporelle(liste_retour);
    tete_liste_point *liste_temp_cluster = init_liste_temporelle_cluster(liste_retour);
    graphic(liste_temp, liste_retour, liste_temp_cluster);
    
    return 0;
}

