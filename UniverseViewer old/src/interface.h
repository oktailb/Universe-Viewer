#include "struct.h"

GtkWidget* vue;
GtkWidget *edge_vue_1;
GtkWidget *edge_vue_2;
GtkWidget *edge_vue_3;
GtkWidget *front_vue_1;
GtkWidget *front_vue_2;
GtkWidget *front_vue_3;
GtkWidget *Lambda_vs_Omega_curve;
GtkWidget *graphC0_color;
GtkWidget *graphC1_color;
GtkWidget *graphC2_color;
GtkWidget *graphC3_color;
GtkWidget *graphC4_color;
GtkWidget *R_t_curve;
GtkWidget *statusbar1;
GtkWidget *drawingarea3;
GtkWidget *colorselector;
GtkWidget *fileselection1;
GtkWidget *fileselection2;
GtkWidget* message_window[16];
GtkWidget *Lambda;
GtkWidget *Omega;
GtkWidget *k;
GtkWidget *Alpha;
GtkWidget *entry1;
GtkWidget *entry3;
GtkWidget* progressbar1;
GtkWidget *label40;
GtkWidget *label41;
GtkWidget *label45;
GtkWidget *label44;
GtkWidget *label43;

  GtkWidget *textview1;
  GtkTextBuffer *text_buffer;
  
  GtkWidget *coord1;
  GtkObject *Lambda_adj;
  GtkObject *Omega_adj;
  GtkObject *k_adj;
  GtkObject *Alpha_adj;
  GtkWidget *Lambda_s;
  GtkWidget *Omega_s;
  GtkWidget *k_s;
  GtkWidget *Alpha_s;

  GtkWidget *coord2;
  GtkObject *spinbutton5_adj;
  GtkWidget *spinbutton5;
  GtkObject *spinbutton6_adj;
  GtkWidget *spinbutton6;
  GtkObject *spinbutton7_adj;
  GtkWidget *spinbutton7;

  GtkWidget *spinbutton35;
  GtkWidget *spinbutton36;
  GtkWidget *spinbutton37;
  GtkWidget *spinbutton38;
  GtkWidget *spinbutton39;
  GtkWidget *spinbutton40;

GtkWidget* create_Universe_Viewer_2 (Point *quasar_proj[6]);
GtkWidget* create_fileselection1 (void);
GtkWidget* create_fileselection2 (void);
GtkWidget* create_about (void);
GtkWidget* create_Move_Steps (void);
GtkWidget* create_Calculus (void);
GtkWidget* create_Options (void);
GtkWidget* create_Compute_Distance (void);
GtkWidget* create_Isotropic_Distribution (void);
GtkWidget* create_Lambda_vs_Omega (void);
GtkWidget* create_R_t_ (void);
GtkWidget* create_Integrand (void);
GtkWidget* create_Tau_vs_Redshift (void);
GtkWidget* create_edge_1 (void);
GtkWidget* create_edge_2 (void);
GtkWidget* create_edge_3 (void);
GtkWidget* create_front_1 (void);
GtkWidget* create_front_2 (void);
GtkWidget* create_front_3 (void);
GtkWidget* create_Message (char* message);
void alerte(char* message);
GtkWidget* create_Color_selector (void);
GtkWidget* create_format_specifior (void);
GtkWidget* create_format_specifior_save (void);
GtkWidget* create_load (void);
