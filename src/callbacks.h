#include <gtk/gtk.h>



void
on_Bajouteravis_clicked                (GtkWidget       *og,
                                        gpointer         user_data);

void
on_Bmodifieravi_clicked                (GtkWidget       *og,
                                        gpointer         user_data);

void
on_Bsupprimeravis_clicked              (GtkWidget       *og,
                                        gpointer         user_data);

void
on_Bafficheravis_clicked               (GtkWidget       *og,
                                        gpointer         user_data);
void 
on_Bsupp_clicked                  (GtkWidget       *og,
                                        gpointer         user_data);

void
on_RBavisavsis_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBavisreclamation_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBmodifieravisavis_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBmodifieravisreclamation_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Bavisrefresh_clicked                (GtkWidget       *og,
                                        gpointer         user_data);

void
on_CBsupprimeravis_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Bmodifieravisrefreshparking_clicked (GtkWidget       *og,
                                        gpointer         user_data);

void
on_Bmodifieravisrefreshid_clicked      (GtkWidget       *og,
                                        gpointer         user_data);

void
on_Bdeleteavisrefresh_clicked          (GtkWidget       *og,
                                        gpointer         user_data);

void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data);
void clear_combobox(GtkComboBox *combobox) ;
