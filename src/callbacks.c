#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <stdlib.h>
#include <gtk/gtk.h>
#include "avis.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
const char *fileavis = "avis.txt";
const char *fileparking = "parking.txt";
int type=0,all=0,Deleteall=0;
void clear_combobox(GtkComboBox *combobox) {
    GtkTreeModel *model = gtk_combo_box_get_model(combobox);
    GtkListStore *store = GTK_LIST_STORE(model);

    // Supprimer tous les éléments
    gtk_list_store_clear(store);
}

void on_Bajouteravis_clicked(GtkWidget *og, gpointer user_data)
{
    avis a1;
    GtkWidget *id_par;
    GtkWidget *ecrireid;
    GtkWidget *msg;
    GtkWidget *note;
    GtkWidget *avi;
    GtkWidget *reclamation;
    GtkWidget *recl;
    id_par=lookup_widget(og,"CBavisparking");
    ecrireid=lookup_widget(og,"Lidavis");
    msg=lookup_widget(og,"Lavismessage");
    note=lookup_widget(og,"SBavisnote");
    avi=lookup_widget(og,"RBavisavsis");
    reclamation=lookup_widget(og,"RBavisreclamation");
    recl=lookup_widget(og,"Eavis");
    a1.note=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(note));
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(avi))) {
        a1.type = 0; // Avis
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(reclamation))) {
        a1.type = 1; // Réclamation
    }
    strcpy(a1.id_parking,gtk_combo_box_get_active_text(GTK_COMBO_BOX(id_par)));
    strcpy(a1.recl,gtk_entry_get_text(GTK_ENTRY(recl)));
    int cin=14040462;
    int id_avis;
    char ch[50]="";
    fflush(stdin);
    char message[30];
    if (strlen(a1.recl)==0) {
        strcpy(message,"Please enter your comment\n");
    } else {
        strcpy(message,"review added\n");
        id_avis=ajouter_avis(fileavis,cin,a1);
        sprintf(ch, "%d", id_avis);
    }
    gtk_label_set_text(GTK_LABEL(ecrireid),ch);
    gtk_label_set_text(GTK_LABEL(msg),message);
}

void on_Bmodifieravi_clicked(GtkWidget *og, gpointer user_data)
{
    avis a1;
    GtkWidget *id_par;
    GtkWidget *ecrireid;
    GtkWidget *msg;
    GtkWidget *note;
    GtkWidget *avi;
    GtkWidget *reclamation;
    GtkWidget *recl;
    id_par=lookup_widget(og,"cbmodifieravisparking");
    ecrireid=lookup_widget(og,"cbmodifieravisid");
    msg=lookup_widget(og,"Lmodifieravismessage");
    note=lookup_widget(og,"SBmodifieravisnote");
    avi=lookup_widget(og,"RBmodifieravisavis");
    reclamation=lookup_widget(og,"RBmodifieravisreclamation");
    recl=lookup_widget(og,"Emodifieravisreclamation");
    a1.note=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(note));
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(avi))) {
        a1.type = 0; // Avis
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(reclamation))) {
        a1.type = 1; // Réclamation
    }
    char id_chercher[50];
    strcpy(a1.id_parking,gtk_combo_box_get_active_text(GTK_COMBO_BOX(id_par)));
    strcpy(id_chercher,gtk_combo_box_get_active_text(GTK_COMBO_BOX(ecrireid)));
    int id_chercherint = atoi(id_chercher);
    strcpy(a1.recl,gtk_entry_get_text(GTK_ENTRY(recl)));
    fflush(stdin);
    char message[30];
    if (strlen(a1.recl)==0) {
        strcpy(message,"Please enter your comment\n");
    } else {
        strcpy(message,"review modified\n");
        modifier_avis(fileavis,id_chercherint,a1);
        gtk_label_set_text(GTK_LABEL(msg),message);
    }
}

void on_Bsupprimeravis_clicked(GtkWidget *og, gpointer user_data)
{
    GtkWidget* id,*Dall,*msg;
    id=lookup_widget(og,"CBdeleteavis");
    Dall=lookup_widget(og,"CBsupprimeravis");
    msg=lookup_widget(og,"Lsupprimeravismessage");
    char id_chercher[50];
    strcpy(id_chercher,gtk_combo_box_get_active_text(GTK_COMBO_BOX(id)));
    int id_chercherint=atoi(id_chercher);
    char msgg[50];
    GtkWidget *warning = GTK_WIDGET(user_data);
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Dall))) {
        all=1;
        strcpy(msgg,"all reviews have been deleted\n ");
    } else {
        all=0;
        strcpy(msgg,"review have been deleted\n ");
    }
    supprimer_avis(fileavis,id_chercherint, all);
    gtk_label_set_text(GTK_LABEL(msg),msgg);
}

void on_Bafficheravis_clicked(GtkWidget *og, gpointer user_data)
{
GtkWidget *tree;
GtkWidget * nootebook;
nootebook=lookup_widget(og,"notebook13");
tree=lookup_widget(nootebook,"TVafficheravis");
afficher_avis(fileavis,tree);
}

void on_Bsupp_clicked(GtkWidget *og, gpointer user_data)
{
}

void on_RBavisavsis_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
        type=0;
}

void on_RBavisreclamation_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
        type=1;
}

void on_RBmodifieravisavis_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
        type=0;
}

void on_RBmodifieravisreclamation_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
        type=1;
}

void on_Bavisrefresh_clicked(GtkWidget *og, gpointer user_data)
{
    GtkWidget *CB;
    parking Tparking[100];
    int i, j;

    i = lire_parking(fileparking, Tparking);
    CB = lookup_widget(og, "CBavisparking");
clear_combobox(CB);
    if (CB == NULL) {
        g_print("Erreur : le widget CBavisparking est introuvable.\n");
        return;
    }

    gtk_combo_box_remove_text(GTK_COMBO_BOX(CB), 0);

    for (j = 0; j < i; j++) {
        if (Tparking[j].nom_parking != NULL && strlen(Tparking[j].nom_parking) > 0) {
            gtk_combo_box_append_text(GTK_COMBO_BOX(CB), Tparking[j].nom_parking);
        } else {
            g_print("Erreur : nom_parking invalide pour l'élément %d.\n", j);
        }
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(CB), 0);
}

void on_CBsupprimeravis_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
        all=1;
    else
        all=0;
}

void on_Bmodifieravisrefreshparking_clicked(GtkWidget *og, gpointer user_data)
{
    GtkWidget *CB;
    parking Tparking[100];
    int i, j;
    i = lire_parking(fileparking, Tparking);
    CB = lookup_widget(og, "cbmodifieravisparking");
clear_combobox(CB);
    if (CB == NULL) {
        g_print("Erreur : le widget CBavisparking est introuvable.\n");
        return;
    }
    gtk_combo_box_remove_text(GTK_COMBO_BOX(CB), 0);
    for (j = 0; j < i; j++) {
        if (Tparking[j].nom_parking != NULL && strlen(Tparking[j].nom_parking) > 0) {
            gtk_combo_box_append_text(GTK_COMBO_BOX(CB), Tparking[j].nom_parking);
        } else {
            g_print("Erreur : nom_parking invalide pour l'élément %d.\n", j);
        }
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(CB), 0);
}

void
on_Bdeleteavisrefresh_clicked          (GtkWidget       *og,
                                        gpointer         user_data)
{
GtkWidget *CB;
    avis Tparking[100];
    int i, j;
    i = lire_avis(fileavis, Tparking);
    CB = lookup_widget(og, "CBdeleteavis");
	clear_combobox(CB);
    if (CB == NULL) {
        g_print("Erreur : le widget CBavisparking est introuvable.\n");
        return;
    }
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(CB)) >= 0) {
    gtk_combo_box_remove_text(GTK_COMBO_BOX(CB), 0);
}
    for (j = 0; j < i; j++) {
	char id_avis_str[50];  
        sprintf(id_avis_str, "%d", Tparking[j].id_avis);

        if (id_avis_str != NULL && strlen(id_avis_str) > 0) {
            gtk_combo_box_append_text(GTK_COMBO_BOX(CB), id_avis_str);
        } else {
            g_print("Erreur : nom_parking invalide pour l'élément %d.\n", j);
        }
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(CB), 0);


}



void on_Bmodifieravisrefreshid_clicked(GtkWidget *og, gpointer user_data)
{
    GtkWidget *CB;
    avis Tparking[100];
    int i, j;
    i = lire_avis(fileavis, Tparking);
    CB = lookup_widget(og, "cbmodifieravisid");
	clear_combobox(CB);
    if (CB == NULL) {
        g_print("Erreur : le widget CBavisparking est introuvable.\n");
        return;
    }
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(CB)) >= 0) {
        gtk_combo_box_remove_text(GTK_COMBO_BOX(CB), 0);
    }
    for (j = 0; j < i; j++) {
        char id_avis_str[50];  
        sprintf(id_avis_str, "%d", Tparking[j].id_avis);

        if (id_avis_str != NULL && strlen(id_avis_str) > 0) {
            gtk_combo_box_append_text(GTK_COMBO_BOX(CB), id_avis_str);
        } else {
            g_print("Erreur : nom_parking invalide pour l'élément %d.\n", j);
        }
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(CB), 0);}
void on_cancelbutton1_clicked(GtkButton *button, gpointer user_data) {

}

// Fonction pour gérer le bouton "OK"
void on_okbutton1_clicked(GtkButton *button, gpointer user_data) {

}

