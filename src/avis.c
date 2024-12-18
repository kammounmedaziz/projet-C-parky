#include <stdio.h>
#include <string.h>
#include <time.h>
#include "avis.h"
#include <stdlib.h>
#include <gtk/gtk.h>
/*ce n'est pas logique que le client ecrit l'id de l'avis 
donc j'ai utliser cette fonction pour gener un id unique pour chaque avis a partir de son cin */
int generer_id(int cin) {
	char unique_id[200];
    char cin_str[16];          
    char timestamp[16];       
    time_t now = time(NULL);   
    sprintf(cin_str, "%d", cin);
    sprintf(timestamp, "%ld", now);
    strcpy(unique_id, cin_str);  
    strcat(unique_id, timestamp); 
    int unique_id1=atoi(unique_id);
return unique_id1;
}
//ajouter avis(retourne le id pour l'afficher sur l'interface)
int ajouter_avis(const char *fileavis, int cin, avis a1){
a1.id_avis=generer_id(cin);


FILE *f=fopen(fileavis,"a");
if (f!=NULL){
fprintf(f,"%d %s %d %d %s \n",a1.id_avis,a1.id_parking,a1.type,a1.note,a1.recl);
fclose(f);
}return a1.id_avis;}
//faire un tableau d'avis a partir du fichier
int lire_avis(const char *fileavis,avis Tavis[]){
int i=0;
FILE* f=fopen(fileavis,"r");
if (f!=NULL){
while (fscanf(f,"%d %s %d %d %[^\n] \n",&Tavis[i].id_avis,Tavis[i].id_parking,&Tavis[i].type,&Tavis[i].note,Tavis[i].recl)!=EOF) i++;
}
return i;
}
//ecricre le fichier a partir de tableau d'avis
void ecrire_avis(const char *fileavis,avis Tavis[],int n){
int i;
FILE* f=fopen(fileavis,"w");
fclose(f);
FILE* f1=fopen(fileavis,"a");
for (i=0;i<n;i++){
fprintf(f1,"%d %s %d %d %s \n",Tavis[i].id_avis,Tavis[i].id_parking,Tavis[i].type,Tavis[i].note,Tavis[i].recl);
}
fclose(f1);
}
//lire le fichier a partir de fichier parking
#define MAX_PARKINGS 100

int lire_parking(const char *fileparking, parking Tparking[]) {
    int i = 0;
    FILE *f = fopen(fileparking, "r");
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier %s\n", fileparking);
        return 0;
    }

    while (i < MAX_PARKINGS && fscanf(f, "%d %s %f %d %s %s %[^\n] \n", 
            &Tparking[i].id_parking, 
            Tparking[i].nom_parking, 
            &Tparking[i].prix_parking, 
            &Tparking[i].capacite_parking, 
            Tparking[i].region, 
            Tparking[i].ville, 
            Tparking[i].rue) != EOF) {
        i++;
    }

    fclose(f);
    return i;
}

//modifier avis
void modifier_avis(const char *fileavis,int id_a_modifier, avis a1){
avis Tavis[100];int i,test=0;
int n=lire_avis(fileavis,Tavis);
for (i=0;i<n;i++){
if (Tavis[i].id_avis==id_a_modifier){
strcpy(Tavis[i].id_parking,a1.id_parking);Tavis[i].type=a1.type;Tavis[i].note=a1.note;strcpy(Tavis[i].recl,a1.recl);
test=1;
break;
}
}

ecrire_avis(fileavis,Tavis,n);
}
//supprimer avis
void supprimer_avis(const char *fileavis,int id_a_supprimer,int all){
if (all==0){
	avis Tavis[100];int i,test=0;
	avis a1;
	int n=lire_avis(fileavis,Tavis);
	for (i=0;i<n;i++){
	if (Tavis[i].id_avis==id_a_supprimer){
	int j;
	for (j=i;j<n-1;j++) {Tavis[j]=Tavis[j+1];}
	n--;test=1;break;}}
	if (test==0) printf("avis n'est pa trouver\n");
	ecrire_avis(fileavis,Tavis,n);}
else{FILE* f=fopen(fileavis,"w");fclose(f);}
}

//affichage d'avis:
enum{ID,Parking,TYPE,NOTE,RECL,COLUMNS};
void afficher_avis(const char *fileavis, GtkWidget *liste){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
avis Tavis[100];
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" id Review",renderer,"text",ID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Parking Name",renderer,"text",Parking,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Type",renderer,"text",TYPE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Rating",renderer,"text",NOTE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Description",renderer,"text",RECL,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

store=gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
int j=lire_avis(fileavis,Tavis);
int i;
for (i=0;i<j;i++){
char ty[8],not[2];
if (Tavis[i].type==1) strcpy(ty,"Claim");
else strcpy(ty,"Review");
sprintf(not , "%d" ,Tavis[i].note);
gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter, ID, Tavis[i].id_avis, Parking, Tavis[i].id_parking, TYPE, ty, NOTE, not, RECL, Tavis[i].recl, -1 );
}
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
g_object_unref (store);
}
}











