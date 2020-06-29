#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

tete_liste_point_ign *init_liste_ign();
int liste_vide_ign(tete_liste_point_ign *pt);
element_liste_point_ign *retourner_element_id_ign(tete_liste_point_ign *pt,int a);
void ajout_liste_ign(tete_liste_point_ign *pt, point_ign *pnt);
void supprimer_element_ign(tete_liste_point_ign *pt);
void afficher_liste_ign(tete_liste_point_ign *pt);
void vider_liste_ign(tete_liste_point_ign *pt);
coor_tableau definir_taille_tableau(tete_liste_point_ign *pt);
void traitement_texte(tete_liste_point_ign *pt, coor_tableau c);


#endif 