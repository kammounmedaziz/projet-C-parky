#ifndef CLIENT_H
#define CLIENT_H
#include <gtk/gtk.h>
typedef struct{
int note,type,id_avis;
char recl[256],id_parking[100];
}avis;
typedef struct{
int id_parking,capacite_parking;
char nom_parking[100],region[50],ville[50],rue[100];
float prix_parking;
}parking;
int lire_avis(const char *fileavis,avis Tavis[]);
void ecrire_avis(const char *fileavis,avis Tavis[],int n);
int ajouter_avis(const char *fileavis, int cin, avis a1);
void modifier_avis(const char *fileavis,int id_a_modifier, avis a1);
void supprimer_avis(const char *fileavis,int id_a_supprimer,int all);
void afficher_avis(const char *fileavis,GtkWidget *liste);
void supp(const char *fileavis,const char *fileparking);
int generer_id(int cin) ;
int lire_parking(const char *fileparking,parking Tparking[]);
#endif
