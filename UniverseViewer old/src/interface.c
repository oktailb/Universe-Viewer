#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  gtk_object_set_data_full (GTK_OBJECT (component), name, \
    gtk_widget_ref (widget), (GtkDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  gtk_object_set_data (GTK_OBJECT (component), name, widget)

extern double age_universe;
extern double delta_age_universe;
extern double new_age_universe;
extern double zr;
extern double h;

double lambda_step = 1e-04;
double omega_step = 1e-04;
double k_step = 1e-04;
double alpha_step = 1e-04;
int ascension_step = 128;
int declinaison_step = 128;
int beta_step = 128;


int message_displayed=0;

GtkWidget*
create_Universe_Viewer_2 (Point *quasar_proj[6])
{
	extern double ascension,declination,beta;
  GtkWidget *Universe_Viewer_2;
  AtkObject *atko;
  GtkWidget *vbox1;
  GtkWidget *Barre_de_menus;
  GtkWidget *Menu_Fichier;
  GtkWidget *image30;
  GtkWidget *menuitem10_menu;
  GtkWidget *ouvrir1;
  GtkWidget *enregistrer1;
  GtkWidget *enregistrer_sous1;
  GtkWidget *separatormenuitem1;
  GtkWidget *quitter1;
  GtkWidget *Menu_Vue;
  GtkWidget *image31;
  GtkWidget *menuitem12_menu;
  GtkWidget *edge_view_4;
  GtkWidget *edge_view_5;
  GtkWidget *edge_view_6;
  GtkWidget *front_view_4;
  GtkWidget *front_view_5;
  GtkWidget *front_view_6;
  GtkWidget *Menu_Graphics;
  GtkWidget *graphics1_menu;
  GtkWidget *lamba_vs_omega1;
  GtkWidget *plot_r_t_1;
  GtkWidget *item6;
  GtkWidget *plot_tau_z_1;
  GtkWidget *Menu_Tools;
  GtkWidget *tools1_menu;
  GtkWidget *distance1;
  GtkWidget *isotropic1;
  GtkWidget *Menu_Preferences;
  GtkWidget *preferences1_menu;
  GtkWidget *move_steps1;
  GtkWidget *calculus1;
  GtkWidget *options1;
  GtkWidget *Menu_Aide;
  GtkWidget *menuitem13_menu;
  GtkWidget *about1;
  GtkWidget *hpaned1;
  GtkWidget *Reglages;
  GtkWidget *frame1;
    GSList *Lambda_s_group = NULL;
  GtkWidget *Constantes_cosmologiques;
  GtkWidget *frame2;
  GtkWidget *a;
  GtkWidget *d;
  GtkWidget *b;
  GtkWidget *label2;
  GtkWidget *frame3;
  GtkWidget *View_manage;
  GtkObject *spinbutton8_adj;
  GtkWidget *spinbutton8;
  GtkWidget *views;
  GtkWidget *menu14;
  GtkWidget *edge_view_1;
  GtkWidget *edge_view_2;
  GtkWidget *edge_view_3;
  GtkWidget *front_view_1;
  GtkWidget *front_view_2;
  GtkWidget *front_view_3;
  GtkWidget *zoom_low;
  GtkWidget *zoom_no;
  GtkWidget *zoom_up;
  GtkWidget *center;
  GtkWidget *middle;
  GtkWidget *earth;
  GtkWidget *local_zoom;
  GtkWidget *Gestion_des_vues;
  GtkWidget *scrolledwindow1;
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();

  Universe_Viewer_2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Universe_Viewer_2, "Universe_Viewer_2");
  gtk_window_set_title (GTK_WINDOW (Universe_Viewer_2), "Universe Viewer 2");
  gtk_window_set_destroy_with_parent (GTK_WINDOW (Universe_Viewer_2), TRUE);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox1, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (Universe_Viewer_2), vbox1);

  Barre_de_menus = gtk_menu_bar_new ();
  gtk_widget_set_name (Barre_de_menus, "Barre_de_menus");
  gtk_widget_show (Barre_de_menus);
  gtk_box_pack_start (GTK_BOX (vbox1), Barre_de_menus, FALSE, FALSE, 0);

  Menu_Fichier = gtk_image_menu_item_new_with_mnemonic ("_Fichier");
  gtk_widget_set_name (Menu_Fichier, "Menu_Fichier");
  gtk_widget_show (Menu_Fichier);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Fichier);

  image30 = gtk_image_new_from_stock ("gtk-floppy", GTK_ICON_SIZE_MENU);
  gtk_widget_set_name (image30, "image30");
  gtk_widget_show (image30);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (Menu_Fichier), image30);

  menuitem10_menu = gtk_menu_new ();
  gtk_widget_set_name (menuitem10_menu, "menuitem10_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Fichier), menuitem10_menu);

  ouvrir1 = gtk_image_menu_item_new_from_stock ("gtk-open", accel_group);
  gtk_widget_set_name (ouvrir1, "ouvrir1");
  gtk_widget_show (ouvrir1);
  gtk_container_add (GTK_CONTAINER (menuitem10_menu), ouvrir1);

  enregistrer1 = gtk_image_menu_item_new_from_stock ("gtk-save", accel_group);
  gtk_widget_set_name (enregistrer1, "enregistrer1");
  gtk_widget_show (enregistrer1);
  gtk_container_add (GTK_CONTAINER (menuitem10_menu), enregistrer1);

  enregistrer_sous1 = gtk_image_menu_item_new_from_stock ("gtk-save-as", accel_group);
  gtk_widget_set_name (enregistrer_sous1, "enregistrer_sous1");
  gtk_widget_show (enregistrer_sous1);
  gtk_container_add (GTK_CONTAINER (menuitem10_menu), enregistrer_sous1);

  separatormenuitem1 = gtk_menu_item_new ();
  gtk_widget_set_name (separatormenuitem1, "separatormenuitem1");
  gtk_widget_show (separatormenuitem1);
  gtk_container_add (GTK_CONTAINER (menuitem10_menu), separatormenuitem1);
  gtk_widget_set_sensitive (separatormenuitem1, FALSE);

  quitter1 = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
  gtk_widget_set_name (quitter1, "quitter1");
  gtk_widget_show (quitter1);
  gtk_container_add (GTK_CONTAINER (menuitem10_menu), quitter1);

  Menu_Vue = gtk_image_menu_item_new_with_mnemonic ("_Vue");
  gtk_widget_set_name (Menu_Vue, "Menu_Vue");
  gtk_widget_show (Menu_Vue);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Vue);

  image31 = gtk_image_new_from_stock ("gtk-dialog-info", GTK_ICON_SIZE_MENU);
  gtk_widget_set_name (image31, "image31");
  gtk_widget_show (image31);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (Menu_Vue), image31);

  menuitem12_menu = gtk_menu_new ();
  gtk_widget_set_name (menuitem12_menu, "menuitem12_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Vue), menuitem12_menu);

  edge_view_4 = gtk_menu_item_new_with_mnemonic ("Edge View 1");
  gtk_widget_set_name (edge_view_4, "edge_view_4");
  gtk_widget_show (edge_view_4);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), edge_view_4);

  edge_view_5 = gtk_menu_item_new_with_mnemonic ("Edge View 2");
  gtk_widget_set_name (edge_view_5, "edge_view_5");
  gtk_widget_show (edge_view_5);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), edge_view_5);

  edge_view_6 = gtk_menu_item_new_with_mnemonic ("Edge View 3");
  gtk_widget_set_name (edge_view_6, "edge_view_6");
  gtk_widget_show (edge_view_6);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), edge_view_6);

  front_view_4 = gtk_menu_item_new_with_mnemonic ("Front View 1");
  gtk_widget_set_name (front_view_4, "front_view_4");
  gtk_widget_show (front_view_4);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), front_view_4);

  front_view_5 = gtk_menu_item_new_with_mnemonic ("Front View 2");
  gtk_widget_set_name (front_view_5, "front_view_5");
  gtk_widget_show (front_view_5);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), front_view_5);

  front_view_6 = gtk_menu_item_new_with_mnemonic ("Front View 3");
  gtk_widget_set_name (front_view_6, "front_view_6");
  gtk_widget_show (front_view_6);
  gtk_container_add (GTK_CONTAINER (menuitem12_menu), front_view_6);

  Menu_Graphics = gtk_menu_item_new_with_mnemonic ("_Graphics");
  gtk_widget_set_name (Menu_Graphics, "Menu_Graphics");
  gtk_widget_show (Menu_Graphics);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Graphics);

  graphics1_menu = gtk_menu_new ();
  gtk_widget_set_name (graphics1_menu, "graphics1_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Graphics), graphics1_menu);

  lamba_vs_omega1 = gtk_menu_item_new_with_mnemonic ("Lamba vs Omega");
  gtk_widget_set_name (lamba_vs_omega1, "lamba_vs_omega1");
  gtk_widget_show (lamba_vs_omega1);
  gtk_container_add (GTK_CONTAINER (graphics1_menu), lamba_vs_omega1);

  plot_r_t_1 = gtk_menu_item_new_with_mnemonic ("Plot a(t)");
  gtk_widget_set_name (plot_r_t_1, "plot_r_t_1");
  gtk_widget_show (plot_r_t_1);
  gtk_container_add (GTK_CONTAINER (graphics1_menu), plot_r_t_1);

  item6 = gtk_menu_item_new_with_mnemonic ("Plot integrand");
  gtk_widget_set_name (item6, "item6");
  gtk_widget_show (item6);
  gtk_container_add (GTK_CONTAINER (graphics1_menu), item6);

  plot_tau_z_1 = gtk_menu_item_new_with_mnemonic ("Plot Comobile Distance(z)");
  gtk_widget_set_name (plot_tau_z_1, "plot_tau_z_1");
  gtk_widget_show (plot_tau_z_1);
  gtk_container_add (GTK_CONTAINER (graphics1_menu), plot_tau_z_1);

  Menu_Tools = gtk_menu_item_new_with_mnemonic ("Tools");
  gtk_widget_set_name (Menu_Tools, "Menu_Tools");
  gtk_widget_show (Menu_Tools);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Tools);

  tools1_menu = gtk_menu_new ();
  gtk_widget_set_name (tools1_menu, "tools1_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Tools), tools1_menu);

  distance1 = gtk_menu_item_new_with_mnemonic ("Distance");
  gtk_widget_set_name (distance1, "distance1");
  gtk_widget_show (distance1);
  gtk_container_add (GTK_CONTAINER (tools1_menu), distance1);

  isotropic1 = gtk_menu_item_new_with_mnemonic ("Isotropic");
  gtk_widget_set_name (isotropic1, "isotropic1");
  gtk_widget_show (isotropic1);
  gtk_container_add (GTK_CONTAINER (tools1_menu), isotropic1);

  Menu_Preferences = gtk_menu_item_new_with_mnemonic ("Preferences");
  gtk_widget_set_name (Menu_Preferences, "Menu_Preferences");
  gtk_widget_show (Menu_Preferences);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Preferences);

  preferences1_menu = gtk_menu_new ();
  gtk_widget_set_name (preferences1_menu, "preferences1_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Preferences), preferences1_menu);

  move_steps1 = gtk_menu_item_new_with_mnemonic ("Move steps");
  gtk_widget_set_name (move_steps1, "move_steps1");
  gtk_widget_show (move_steps1);
  gtk_container_add (GTK_CONTAINER (preferences1_menu), move_steps1);

  calculus1 = gtk_menu_item_new_with_mnemonic ("Calculus");
  gtk_widget_set_name (calculus1, "calculus1");
  gtk_widget_show (calculus1);
  gtk_container_add (GTK_CONTAINER (preferences1_menu), calculus1);

  options1 = gtk_menu_item_new_with_mnemonic ("Options");
  gtk_widget_set_name (options1, "options1");
  gtk_widget_show (options1);
  gtk_container_add (GTK_CONTAINER (preferences1_menu), options1);

  Menu_Aide = gtk_menu_item_new_with_mnemonic ("_Aide");
  gtk_widget_set_name (Menu_Aide, "Menu_Aide");
  gtk_widget_show (Menu_Aide);
  gtk_container_add (GTK_CONTAINER (Barre_de_menus), Menu_Aide);

  menuitem13_menu = gtk_menu_new ();
  gtk_widget_set_name (menuitem13_menu, "menuitem13_menu");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Menu_Aide), menuitem13_menu);

  about1 = gtk_menu_item_new_with_mnemonic ("_About");
  gtk_widget_set_name (about1, "about1");
  gtk_widget_show (about1);
  gtk_container_add (GTK_CONTAINER (menuitem13_menu), about1);

  hpaned1 = gtk_hpaned_new ();
  gtk_widget_set_name (hpaned1, "hpaned1");
  gtk_widget_show (hpaned1);
  gtk_box_pack_start (GTK_BOX (vbox1), hpaned1, TRUE, TRUE, 0);
  gtk_paned_set_position (GTK_PANED (hpaned1), 1);

  Reglages = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (Reglages, "Reglages");
  gtk_widget_show (Reglages);
  gtk_paned_pack1 (GTK_PANED (hpaned1), Reglages, FALSE, FALSE);
  gtk_widget_set_usize (Reglages, 200, 400);
  gtk_container_set_border_width (GTK_CONTAINER (Reglages), 4);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame1, "frame1");
  gtk_widget_show (frame1);
  gtk_box_pack_start (GTK_BOX (Reglages), frame1, FALSE, TRUE, 0);
  gtk_widget_set_usize (frame1, -2, 155);

  coord1 = gtk_fixed_new ();
  gtk_widget_set_name (coord1, "coord1");
  gtk_widget_show (coord1);
  gtk_container_add (GTK_CONTAINER (frame1), coord1);

  Lambda_adj = gtk_adjustment_new (1, -100, 100, lambda_step, lambda_step, 1);
  Lambda = gtk_spin_button_new (GTK_ADJUSTMENT (Lambda_adj), 1, 7);
  gtk_widget_set_name (Lambda, "Lambda");
  gtk_widget_show (Lambda);
  gtk_fixed_put (GTK_FIXED (coord1), Lambda, 88, 8);
  gtk_widget_set_usize (Lambda, 85, 28);

  Omega_adj = gtk_adjustment_new (0.2, -100, 100, omega_step, omega_step, 1);
  Omega = gtk_spin_button_new (GTK_ADJUSTMENT (Omega_adj), 1, 7);
  gtk_widget_set_name (Omega, "Omega");
  gtk_widget_show (Omega);
  gtk_fixed_put (GTK_FIXED (coord1), Omega, 88, 40);
  gtk_widget_set_usize (Omega, 85, 28);

  k_adj = gtk_adjustment_new (0.20005, -100, 100, k_step, k_step, 1);
  k = gtk_spin_button_new (GTK_ADJUSTMENT (k_adj), 1, 7);
  gtk_widget_set_name (k, "k");
  gtk_widget_show (k);
  gtk_fixed_put (GTK_FIXED (coord1), k, 88, 72);
  gtk_widget_set_usize (k, 85, 28);

  Alpha_adj = gtk_adjustment_new (5e-05, -100, 100, alpha_step, alpha_step, 1);
  Alpha = gtk_spin_button_new (GTK_ADJUSTMENT (Alpha_adj), 1, 7);
  gtk_widget_set_name (Alpha, "Alpha");
  gtk_widget_show (Alpha);
  gtk_fixed_put (GTK_FIXED (coord1), Alpha, 88, 104);
  gtk_widget_set_usize (Alpha, 85, 28);

  Lambda_s = gtk_radio_button_new_with_mnemonic (NULL, "Lambda");
  gtk_widget_set_name (Lambda_s, "Lambda_s");
  gtk_widget_show (Lambda_s);
  gtk_fixed_put (GTK_FIXED (coord1), Lambda_s, 8, 8);
  gtk_widget_set_usize (Lambda_s, 83, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (Lambda_s), Lambda_s_group);
  Lambda_s_group = gtk_radio_button_group (GTK_RADIO_BUTTON (Lambda_s));

  Omega_s = gtk_radio_button_new_with_mnemonic (NULL, "Omega");
  gtk_widget_set_name (Omega_s, "Omega_s");
  gtk_widget_show (Omega_s);
  gtk_fixed_put (GTK_FIXED (coord1), Omega_s, 8, 40);
  gtk_widget_set_usize (Omega_s, 83, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (Omega_s), Lambda_s_group);
  Lambda_s_group = gtk_radio_button_group (GTK_RADIO_BUTTON (Omega_s));

  k_s = gtk_radio_button_new_with_mnemonic (NULL, "k");
  gtk_widget_set_name (k_s, "k_s");
  gtk_widget_show (k_s);
  gtk_fixed_put (GTK_FIXED (coord1), k_s, 8, 72);
  gtk_widget_set_usize (k_s, 83, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (k_s), Lambda_s_group);
  Lambda_s_group = gtk_radio_button_group (GTK_RADIO_BUTTON (k_s));

  Alpha_s = gtk_radio_button_new_with_mnemonic (NULL, "Alpha");
  gtk_widget_set_name (Alpha_s, "Alpha_s");
  gtk_widget_show (Alpha_s);
  gtk_fixed_put (GTK_FIXED (coord1), Alpha_s, 8, 104);
  gtk_widget_set_usize (Alpha_s, 83, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (Alpha_s), Lambda_s_group);
  Lambda_s_group = gtk_radio_button_group (GTK_RADIO_BUTTON (Alpha_s));

  Constantes_cosmologiques = gtk_label_new ("Constantes cosmologiques");
  gtk_widget_set_name (Constantes_cosmologiques, "Constantes_cosmologiques");
  gtk_widget_show (Constantes_cosmologiques);
  gtk_frame_set_label_widget (GTK_FRAME (frame1), Constantes_cosmologiques);
  gtk_widget_set_usize (Constantes_cosmologiques, 130, 12);
  gtk_label_set_justify (GTK_LABEL (Constantes_cosmologiques), GTK_JUSTIFY_LEFT);

  frame2 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame2, "frame2");
  gtk_widget_show (frame2);
  gtk_box_pack_start (GTK_BOX (Reglages), frame2, FALSE, TRUE, 0);
  gtk_widget_set_usize (frame2, -2, 130);

  coord2 = gtk_fixed_new ();
  gtk_widget_set_name (coord2, "coord2");
  gtk_widget_show (coord2);
  gtk_container_add (GTK_CONTAINER (frame2), coord2);

  spinbutton5_adj = gtk_adjustment_new (ascension, -PI, PI, PI/ascension_step, PI/ascension_step, 1);
  spinbutton5 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton5_adj), 1, 5);
  gtk_widget_set_name (spinbutton5, "spinbutton5");
  gtk_widget_show (spinbutton5);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton5, 112, 8);
  gtk_widget_set_usize (spinbutton5, 62, 21);

  spinbutton6_adj = gtk_adjustment_new (declination, -PI, PI, PI/declinaison_step, PI/declinaison_step, 1);
  spinbutton6 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton6_adj), 1, 5);
  gtk_widget_set_name (spinbutton6, "spinbutton6");
  gtk_widget_show (spinbutton6);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton6, 112, 40);
  gtk_widget_set_usize (spinbutton6, 62, 21);

  spinbutton7_adj = gtk_adjustment_new (beta, -PI, PI, PI/beta_step, PI/beta_step, 1);
  spinbutton7 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton7_adj), 1, 5);
  gtk_widget_set_name (spinbutton7, "spinbutton7");
  gtk_widget_show (spinbutton7);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton7, 112, 72);
  gtk_widget_set_usize (spinbutton7, 62, 21);

  a = gtk_label_new ("Right Ascenscion");
  gtk_widget_set_name (a, "a");
  gtk_widget_show (a);
  gtk_fixed_put (GTK_FIXED (coord2), a, 16, 8);
  gtk_widget_set_usize (a, 90, 16);
  gtk_label_set_justify (GTK_LABEL (a), GTK_JUSTIFY_LEFT);

  d = gtk_label_new ("Declinaison");
  gtk_widget_set_name (d, "d");
  gtk_widget_show (d);
  gtk_fixed_put (GTK_FIXED (coord2), d, 16, 40);
  gtk_widget_set_usize (d, 58, 16);
  gtk_label_set_justify (GTK_LABEL (d), GTK_JUSTIFY_LEFT);

  b = gtk_label_new ("Beta");
  gtk_widget_set_name (b, "b");
  gtk_widget_show (b);
  gtk_fixed_put (GTK_FIXED (coord2), b, 16, 72);
  gtk_widget_set_usize (b, 58, 16);
  gtk_label_set_justify (GTK_LABEL (b), GTK_JUSTIFY_LEFT);

  label2 = gtk_label_new ("Vue courante");
  gtk_widget_set_name (label2, "label2");
  gtk_widget_show (label2);
  gtk_frame_set_label_widget (GTK_FRAME (frame2), label2);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_LEFT);

  frame3 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame3, "frame3");
  gtk_widget_show (frame3);
  gtk_box_pack_start (GTK_BOX (Reglages), frame3, FALSE, TRUE, 0);
  gtk_widget_set_usize (frame3, -2, 172);

  View_manage = gtk_fixed_new ();
  gtk_widget_set_name (View_manage, "View_manage");
  gtk_widget_show (View_manage);
  gtk_container_add (GTK_CONTAINER (frame3), View_manage);

  spinbutton8_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton8 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton8_adj), 1, 0);
  gtk_widget_set_name (spinbutton8, "spinbutton8");
  gtk_widget_show (spinbutton8);
  gtk_fixed_put (GTK_FIXED (View_manage), spinbutton8, 8, 112);
  gtk_widget_set_usize (spinbutton8, 42, 27);

  views = gtk_option_menu_new ();
  gtk_widget_set_name (views, "views");
  gtk_widget_show (views);
  gtk_fixed_put (GTK_FIXED (View_manage), views, 8, 8);
  gtk_widget_set_usize (views, 165, 27);

  menu14 = gtk_menu_new ();
  gtk_widget_set_name (menu14, "menu14");

  edge_view_1 = gtk_menu_item_new_with_mnemonic ("Edge view 1");
  gtk_widget_set_name (edge_view_1, "edge_view_1");
  gtk_widget_show (edge_view_1);
  gtk_container_add (GTK_CONTAINER (menu14), edge_view_1);

  edge_view_2 = gtk_menu_item_new_with_mnemonic ("Edge view 2");
  gtk_widget_set_name (edge_view_2, "edge_view_2");
  gtk_widget_show (edge_view_2);
  gtk_container_add (GTK_CONTAINER (menu14), edge_view_2);

  edge_view_3 = gtk_menu_item_new_with_mnemonic ("Edge view 3");
  gtk_widget_set_name (edge_view_3, "edge_view_3");
  gtk_widget_show (edge_view_3);
  gtk_container_add (GTK_CONTAINER (menu14), edge_view_3);

  front_view_1 = gtk_menu_item_new_with_mnemonic ("Front view 1");
  gtk_widget_set_name (front_view_1, "front_view_1");
  gtk_widget_show (front_view_1);
  gtk_container_add (GTK_CONTAINER (menu14), front_view_1);

  front_view_2 = gtk_menu_item_new_with_mnemonic ("Front view 2");
  gtk_widget_set_name (front_view_2, "front_view_2");
  gtk_widget_show (front_view_2);
  gtk_container_add (GTK_CONTAINER (menu14), front_view_2);

  front_view_3 = gtk_menu_item_new_with_mnemonic ("Front view 3");
  gtk_widget_set_name (front_view_3, "front_view_3");
  gtk_widget_show (front_view_3);
  gtk_container_add (GTK_CONTAINER (menu14), front_view_3);

  gtk_option_menu_set_menu (GTK_OPTION_MENU (views), menu14);

  zoom_low = gtk_button_new_with_mnemonic ("zoom -");
  gtk_widget_set_name (zoom_low, "zoom_low");
  gtk_widget_show (zoom_low);
  gtk_fixed_put (GTK_FIXED (View_manage), zoom_low, 8, 48);
  gtk_widget_set_usize (zoom_low, 55, 28);

  zoom_no = gtk_button_new_with_mnemonic ("1:1");
  gtk_widget_set_name (zoom_no, "zoom_no");
  gtk_widget_show (zoom_no);
  gtk_fixed_put (GTK_FIXED (View_manage), zoom_no, 72, 48);
  gtk_widget_set_usize (zoom_no, 32, 28);

  zoom_up = gtk_button_new_with_mnemonic ("zoom +");
  gtk_widget_set_name (zoom_up, "zoom_up");
  gtk_widget_show (zoom_up);
  gtk_fixed_put (GTK_FIXED (View_manage), zoom_up, 112, 48);
  gtk_widget_set_usize (zoom_up, 55, 28);

  center = gtk_button_new_with_mnemonic ("Center");
  gtk_widget_set_name (center, "center");
  gtk_widget_show (center);
  gtk_fixed_put (GTK_FIXED (View_manage), center, 112, 80);
  gtk_widget_set_usize (center, 55, 28);

  middle = gtk_button_new_with_mnemonic ("(0,0)");
  gtk_widget_set_name (middle, "middle");
  gtk_widget_show (middle);
  gtk_fixed_put (GTK_FIXED (View_manage), middle, 72, 80);
  gtk_widget_set_usize (middle, 35, 28);

  earth = gtk_button_new_with_mnemonic ("Earth");
  gtk_widget_set_name (earth, "earth");
  gtk_widget_show (earth);
  gtk_fixed_put (GTK_FIXED (View_manage), earth, 8, 80);
  gtk_widget_set_usize (earth, 55, 28);

  local_zoom = gtk_button_new_with_mnemonic ("Localize zoom");
  gtk_widget_set_name (local_zoom, "local_zoom");
  gtk_widget_show (local_zoom);
  gtk_fixed_put (GTK_FIXED (View_manage), local_zoom, 64, 112);
  gtk_widget_set_usize (local_zoom, 103, 28);

  Gestion_des_vues = gtk_label_new ("Gestion des vues");
  gtk_widget_set_name (Gestion_des_vues, "Gestion_des_vues");
  gtk_widget_show (Gestion_des_vues);
  gtk_frame_set_label_widget (GTK_FRAME (frame3), Gestion_des_vues);
  gtk_label_set_justify (GTK_LABEL (Gestion_des_vues), GTK_JUSTIFY_LEFT);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_name (scrolledwindow1, "scrolledwindow1");
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);

  progressbar1 = gtk_progress_bar_new ();
  gtk_widget_set_name (progressbar1, "progressbar1");
  gtk_widget_show (progressbar1);
  gtk_box_pack_start (GTK_BOX (Reglages), progressbar1, FALSE, FALSE, 0);
  gtk_widget_set_usize (progressbar1, -2, 30);
  gtk_progress_set_show_text (GTK_PROGRESS (progressbar1), TRUE);

  vue = gtk_drawing_area_new ();
  gtk_widget_set_name (vue, "vue");
  gtk_widget_show (vue);
  gtk_paned_pack2 (GTK_PANED (hpaned1), vue, FALSE, FALSE);
  gtk_widget_set_usize (vue, 512, 512);
  GTK_WIDGET_SET_FLAGS (vue, GTK_CAN_FOCUS);
  GTK_WIDGET_SET_FLAGS (vue, GTK_CAN_DEFAULT);

  //statusbar1 = gtk_statusbar_new ();
  //gtk_widget_set_name (statusbar1, "statusbar1");
  //gtk_widget_show (statusbar1);
  //gtk_box_pack_start (GTK_BOX (vbox1), statusbar1, FALSE, FALSE, 0);
  text_buffer = gtk_text_buffer_new(NULL);
  textview1 = gtk_text_view_new_with_buffer (text_buffer);
  gtk_widget_set_name (textview1, "textview1");
  gtk_widget_show (textview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), textview1);
  gtk_widget_set_size_request (textview1, -1, 192);

  gtk_signal_connect (GTK_OBJECT (ouvrir1), "activate",
                      GTK_SIGNAL_FUNC (on_ouvrir1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (enregistrer1), "activate",
                      GTK_SIGNAL_FUNC (on_enregistrer1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (enregistrer_sous1), "activate",
                      GTK_SIGNAL_FUNC (on_enregistrer_sous1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (quitter1), "activate",
                      GTK_SIGNAL_FUNC (on_quitter1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_4), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_4_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_5), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_5_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_6), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_6_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_4), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_4_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_5), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_5_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_6), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_6_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (lamba_vs_omega1), "activate",
                      GTK_SIGNAL_FUNC (on_lamba_vs_omega1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (plot_r_t_1), "activate",
                      GTK_SIGNAL_FUNC (on_plot_r_t_1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (item6), "activate",
                      GTK_SIGNAL_FUNC (on_item6_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (plot_tau_z_1), "activate",
                      GTK_SIGNAL_FUNC (on_plot_tau_z_1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (distance1), "activate",
                      GTK_SIGNAL_FUNC (on_distance1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (isotropic1), "activate",
                      GTK_SIGNAL_FUNC (on_isotropic1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (move_steps1), "activate",
                      GTK_SIGNAL_FUNC (on_move_steps1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (calculus1), "activate",
                      GTK_SIGNAL_FUNC (on_calculus1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (options1), "activate",
                      GTK_SIGNAL_FUNC (on_options1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (about1), "activate",
                      GTK_SIGNAL_FUNC (on_about1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_1), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_2), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_2_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edge_view_3), "activate",
                      GTK_SIGNAL_FUNC (on_edge_view_3_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_1), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_2), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_2_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (front_view_3), "activate",
                      GTK_SIGNAL_FUNC (on_front_view_3_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (vue), "expose_event",
                      G_CALLBACK (on_vue_button_press_event),
                      NULL);
  //gtk_signal_connect (GTK_OBJECT (statusbar1), "expose_event",
    //                  G_CALLBACK (on_statusbar1_event),
      //                NULL);

  gtk_signal_connect (GTK_OBJECT (zoom_low), "clicked",
                      GTK_SIGNAL_FUNC (on_zoom_low_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (zoom_no), "clicked",
                      GTK_SIGNAL_FUNC (on_zoom_no_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (zoom_up), "clicked",
                      GTK_SIGNAL_FUNC (on_zoom_up_activate),
                      NULL);

  g_signal_connect ((gpointer) Lambda, "value_changed",
                    G_CALLBACK (on_Lambda_changed),
                    NULL);
  g_signal_connect ((gpointer) Omega, "value_changed",
                    G_CALLBACK (on_Omega_changed),
                    NULL);
  g_signal_connect ((gpointer) k, "value_changed",
                    G_CALLBACK (on_k_changed),
                    NULL);
  g_signal_connect ((gpointer) Alpha, "value_changed",
                    G_CALLBACK (on_Alpha_changed),
                    NULL);

g_signal_connect ((gpointer) spinbutton5, "value_changed",
                    G_CALLBACK (on_spinbutton5_changed),
                    NULL);
g_signal_connect ((gpointer) spinbutton6, "value_changed",
                    G_CALLBACK (on_spinbutton6_changed),
                    NULL);
g_signal_connect ((gpointer) spinbutton7, "value_changed",
                    G_CALLBACK (on_spinbutton7_changed),
                    NULL);


  g_signal_connect ((gpointer) Lambda_s, "clicked",
                    G_CALLBACK (on_Lambda_clicked),
                    NULL);
  g_signal_connect ((gpointer) Omega_s, "clicked",
                    G_CALLBACK (on_Omega_clicked),
                    NULL);
  g_signal_connect ((gpointer) k_s, "clicked",
                    G_CALLBACK (on_k_clicked),
                    NULL);
  g_signal_connect ((gpointer) Alpha_s, "clicked",
                    G_CALLBACK (on_Alpha_clicked),
                    NULL);

  gtk_signal_connect (GTK_OBJECT (vue), "button_press_event",
                      G_CALLBACK (on_vue_event),
                      NULL);

  atko = gtk_widget_get_accessible (Universe_Viewer_2);
  atk_object_set_name (atko, "Universe Viewer 2");

  atko = gtk_widget_get_accessible (center);
  atk_object_set_name (atko, "Center");


  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Universe_Viewer_2, Universe_Viewer_2, "Universe_Viewer_2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Barre_de_menus, "Barre_de_menus");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Fichier, "Menu_Fichier");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, image30, "image30");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, menuitem10_menu, "menuitem10_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, ouvrir1, "ouvrir1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, enregistrer1, "enregistrer1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, enregistrer_sous1, "enregistrer_sous1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, separatormenuitem1, "separatormenuitem1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, quitter1, "quitter1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Vue, "Menu_Vue");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, image31, "image31");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, menuitem12_menu, "menuitem12_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_4, "edge_view_4");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_5, "edge_view_5");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_6, "edge_view_6");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_4, "front_view_4");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_5, "front_view_5");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_6, "front_view_6");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Graphics, "Menu_Graphics");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, graphics1_menu, "graphics1_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, lamba_vs_omega1, "lamba_vs_omega1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, plot_r_t_1, "plot_r_t_1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, item6, "item6");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, plot_tau_z_1, "plot_tau_z_1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Tools, "Menu_Tools");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, tools1_menu, "tools1_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, distance1, "distance1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, isotropic1, "isotropic1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Preferences, "Menu_Preferences");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, preferences1_menu, "preferences1_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, move_steps1, "move_steps1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, calculus1, "calculus1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, options1, "options1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Menu_Aide, "Menu_Aide");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, menuitem13_menu, "menuitem13_menu");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, about1, "about1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, hpaned1, "hpaned1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Reglages, "Reglages");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, frame1, "frame1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, coord1, "coord1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Lambda, "Lambda");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Omega, "Omega");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, k, "k");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Alpha, "Alpha");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Lambda_s, "Lambda_s");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Omega_s, "Omega_s");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, k_s, "k_s");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Alpha_s, "Alpha_s");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Constantes_cosmologiques, "Constantes_cosmologiques");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, frame2, "frame2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, coord2, "coord2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, spinbutton5, "spinbutton5");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, spinbutton6, "spinbutton6");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, spinbutton7, "spinbutton7");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, a, "a");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, d, "d");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, b, "b");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, label2, "label2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, frame3, "frame3");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, View_manage, "View_manage");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, spinbutton8, "spinbutton8");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, views, "views");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, menu14, "menu14");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_1, "edge_view_1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_2, "edge_view_2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, edge_view_3, "edge_view_3");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_1, "front_view_1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_2, "front_view_2");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, front_view_3, "front_view_3");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, zoom_low, "zoom_low");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, zoom_no, "zoom_no");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, zoom_up, "zoom_up");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, center, "center");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, middle, "middle");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, earth, "earth");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, local_zoom, "local_zoom");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, Gestion_des_vues, "Gestion_des_vues");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, progressbar1, "progressbar1");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, vue, "vue");
  GLADE_HOOKUP_OBJECT (Universe_Viewer_2, statusbar1, "statusbar1");

  //gtk_widget_grab_focus (vue);
  //gtk_widget_grab_default (vue);
  gtk_window_add_accel_group (GTK_WINDOW (Universe_Viewer_2), accel_group);

  return Universe_Viewer_2;
}

/*
GtkWidget*
create_Message (char* message)
{
  GtkWidget *Message;
  GtkWidget *vbox11;
  GtkWidget *texte;
  GtkWidget *fermer;

  Message = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Message, "Message");
  gtk_window_set_title (GTK_WINDOW (Message), "Message");

  vbox11 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox11, "vbox11");
  gtk_widget_show (vbox11);
  gtk_container_add (GTK_CONTAINER (Message), vbox11);

  texte = gtk_label_new (message);
  gtk_widget_set_name (texte, "texte");
  gtk_widget_show (texte);
  gtk_box_pack_start (GTK_BOX (vbox11), texte, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (texte), GTK_JUSTIFY_LEFT);

  fermer = gtk_button_new_with_mnemonic ("fermer");
  gtk_widget_set_name (fermer, "fermer");
  gtk_widget_show (fermer);
  gtk_box_pack_start (GTK_BOX (vbox11), fermer, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) fermer, "clicked",
                    G_CALLBACK (on_fermer_message_activate),
                    NULL);


  GLADE_HOOKUP_OBJECT_NO_REF (Message, Message, "Message");
  GLADE_HOOKUP_OBJECT (Message, vbox11, "vbox11");
  GLADE_HOOKUP_OBJECT (Message, texte, "texte");
  GLADE_HOOKUP_OBJECT (Message, fermer, "fermer");

  return Message;
}

*/


GtkWidget*
create_fileselection1 (void)
{
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;

  fileselection1 = gtk_file_selection_new ("Choisir un fichier");
  gtk_widget_set_name (fileselection1, "fileselection1");
  gtk_container_set_border_width (GTK_CONTAINER (fileselection1), 10);

  ok_button1 = GTK_FILE_SELECTION (fileselection1)->ok_button;
  gtk_widget_set_name (ok_button1, "ok_button1");
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  cancel_button1 = GTK_FILE_SELECTION (fileselection1)->cancel_button;
  gtk_widget_set_name (cancel_button1, "cancel_button1");
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (ok_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_file_selected),
                      NULL);

  gtk_signal_connect (GTK_OBJECT (cancel_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_file_selection_quit),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, fileselection1, "fileselection1");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, ok_button1, "ok_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, cancel_button1, "cancel_button1");

  return fileselection1;
}

GtkWidget*
create_fileselection2 (void)
{
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;

  fileselection1 = gtk_file_selection_new ("Enregistrer un fichier");
  gtk_widget_set_name (fileselection1, "fileselection1");
  gtk_container_set_border_width (GTK_CONTAINER (fileselection1), 10);

  ok_button1 = GTK_FILE_SELECTION (fileselection1)->ok_button;
  gtk_widget_set_name (ok_button1, "ok_button1");
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  cancel_button1 = GTK_FILE_SELECTION (fileselection1)->cancel_button;
  gtk_widget_set_name (cancel_button1, "cancel_button1");
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (ok_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_file_selected_save),
                      NULL);

  gtk_signal_connect (GTK_OBJECT (cancel_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_file_selection_quit_save),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, fileselection1, "fileselection1");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, ok_button1, "ok_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection1, cancel_button1, "cancel_button1");

  return fileselection1;
}

GtkWidget*
create_about (void)
{
  GtkWidget *about;
  GtkWidget *vpaned1;
  GtkWidget *staff;
  GtkWidget *Close_About;

  about = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (about, "about");
  gtk_window_set_title (GTK_WINDOW (about), "About ...");

  vpaned1 = gtk_vpaned_new ();
  gtk_widget_set_name (vpaned1, "vpaned1");
  gtk_widget_show (vpaned1);
  gtk_container_add (GTK_CONTAINER (about), vpaned1);
  gtk_container_set_border_width (GTK_CONTAINER (vpaned1), 1);
  gtk_paned_set_position (GTK_PANED (vpaned1), 0);

  staff = gtk_label_new ("                    Programmed by :\n\n\nLionel SPINELLI,   \t\tspinelli@cpt.univ-mrs.fr, \nRemi LAFAYE,       \t\tlafaye@lapphp1.in2p3.fr, \nVincent LECOQ,   \t\tvincent.lecoq@free.fr\nXavier LAUGIER, \t\tlaugier@capucine.univ-mrs.fr\nPascal BONNET, \t\tbonnet@capucine.univ-mrs.fr\nChristophe CROTTA, \tcrotta@capucine.univ-mrs.fr");
  gtk_widget_set_name (staff, "staff");
  gtk_widget_show (staff);
  gtk_paned_pack1 (GTK_PANED (vpaned1), staff, FALSE, FALSE);
  gtk_widget_set_usize (staff, 320, 206);
  gtk_label_set_justify (GTK_LABEL (staff), GTK_JUSTIFY_FILL);

  Close_About = gtk_button_new_with_mnemonic ("OK");
  gtk_widget_set_name (Close_About, "Close_About");
  gtk_widget_show (Close_About);
  gtk_paned_pack2 (GTK_PANED (vpaned1), Close_About, TRUE, TRUE);
  gtk_widget_set_usize (Close_About, 25, 25);

  gtk_signal_connect (GTK_OBJECT (Close_About), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_About_clicked),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (about, about, "about");
  GLADE_HOOKUP_OBJECT (about, vpaned1, "vpaned1");
  GLADE_HOOKUP_OBJECT (about, staff, "staff");
  GLADE_HOOKUP_OBJECT (about, Close_About, "Close_About");

  return about;
}

GtkWidget*
create_Move_Steps (void)
{
  GtkWidget *Move_Steps;
  GtkWidget *vbox2;
  GtkWidget *frame4;
  GtkWidget *fixed9;
  GtkObject *spinbutton9_adj;
  GtkWidget *spinbutton9;
  GtkObject *spinbutton10_adj;
  GtkWidget *spinbutton10;
  GtkObject *spinbutton11_adj;
  GtkWidget *spinbutton11;
  GtkObject *spinbutton12_adj;
  GtkWidget *spinbutton12;
  GtkWidget *label7;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkWidget *label8;
  GtkWidget *label5;
  GtkWidget *frame5;
  GtkWidget *fixed10;
  GtkWidget *label11;
  GtkWidget *label13;
  GtkWidget *label12;
  GtkObject *spinbutton13_adj;
  GtkWidget *spinbutton13;
  GtkObject *spinbutton14_adj;
  GtkWidget *spinbutton14;
  GtkObject *spinbutton15_adj;
  GtkWidget *spinbutton15;
  GtkWidget *label6;
  GtkWidget *Close_Move_Steps;

  Move_Steps = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Move_Steps, "Move_Steps");
  gtk_window_set_title (GTK_WINDOW (Move_Steps), "Move Steps");

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox2, "vbox2");
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (Move_Steps), vbox2);

  frame4 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame4, "frame4");
  gtk_widget_show (frame4);
  gtk_box_pack_start (GTK_BOX (vbox2), frame4, FALSE, FALSE, 0);
  gtk_widget_set_usize (frame4, 180, 123);

  fixed9 = gtk_fixed_new ();
  gtk_widget_set_name (fixed9, "fixed9");
  gtk_widget_show (fixed9);
  gtk_container_add (GTK_CONTAINER (frame4), fixed9);

  spinbutton9_adj = gtk_adjustment_new (lambda_step, 0, 1, 1e-04, 10, 10);
  spinbutton9 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton9_adj), 1, 4);
  gtk_widget_set_name (spinbutton9, "spinbutton9");
  gtk_widget_show (spinbutton9);
  gtk_fixed_put (GTK_FIXED (fixed9), spinbutton9, 104, 8);
  gtk_widget_set_usize (spinbutton9, 71, 20);

  spinbutton10_adj = gtk_adjustment_new (omega_step, 0, 1, 1e-04, 10, 10);
  spinbutton10 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton10_adj), 1, 4);
  gtk_widget_set_name (spinbutton10, "spinbutton10");
  gtk_widget_show (spinbutton10);
  gtk_fixed_put (GTK_FIXED (fixed9), spinbutton10, 104, 32);
  gtk_widget_set_usize (spinbutton10, 71, 20);

  spinbutton11_adj = gtk_adjustment_new (k_step, 0, 1, 1e-04, 10, 10);
  spinbutton11 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton11_adj), 1, 4);
  gtk_widget_set_name (spinbutton11, "spinbutton11");
  gtk_widget_show (spinbutton11);
  gtk_fixed_put (GTK_FIXED (fixed9), spinbutton11, 104, 56);
  gtk_widget_set_usize (spinbutton11, 71, 20);

  spinbutton12_adj = gtk_adjustment_new (alpha_step, 0, 1, 1e-04, 10, 10);
  spinbutton12 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton12_adj), 1, 4);
  gtk_widget_set_name (spinbutton12, "spinbutton12");
  gtk_widget_show (spinbutton12);
  gtk_fixed_put (GTK_FIXED (fixed9), spinbutton12, 104, 80);
  gtk_widget_set_usize (spinbutton12, 71, 20);

  label7 = gtk_label_new ("Lambda Step");
  gtk_widget_set_name (label7, "label7");
  gtk_widget_show (label7);
  gtk_fixed_put (GTK_FIXED (fixed9), label7, 8, 8);
  gtk_widget_set_usize (label7, 70, 16);
  gtk_label_set_justify (GTK_LABEL (label7), GTK_JUSTIFY_LEFT);

  label9 = gtk_label_new ("k Step");
  gtk_widget_set_name (label9, "label9");
  gtk_widget_show (label9);
  gtk_fixed_put (GTK_FIXED (fixed9), label9, 8, 56);
  gtk_widget_set_usize (label9, 38, 16);
  gtk_label_set_justify (GTK_LABEL (label9), GTK_JUSTIFY_LEFT);

  label10 = gtk_label_new ("Alpha Step");
  gtk_widget_set_name (label10, "label10");
  gtk_widget_show (label10);
  gtk_fixed_put (GTK_FIXED (fixed9), label10, 8, 80);
  gtk_widget_set_usize (label10, 54, 20);
  gtk_label_set_justify (GTK_LABEL (label10), GTK_JUSTIFY_LEFT);

  label8 = gtk_label_new ("Omega Step");
  gtk_widget_set_name (label8, "label8");
  gtk_widget_show (label8);
  gtk_fixed_put (GTK_FIXED (fixed9), label8, 8, 32);
  gtk_widget_set_usize (label8, 62, 20);
  gtk_label_set_justify (GTK_LABEL (label8), GTK_JUSTIFY_LEFT);

  label5 = gtk_label_new ("Move Steps Vars");
  gtk_widget_set_name (label5, "label5");
  gtk_widget_show (label5);
  gtk_frame_set_label_widget (GTK_FRAME (frame4), label5);
  gtk_label_set_justify (GTK_LABEL (label5), GTK_JUSTIFY_LEFT);

  frame5 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame5, "frame5");
  gtk_widget_show (frame5);
  gtk_box_pack_start (GTK_BOX (vbox2), frame5, FALSE, FALSE, 0);
  gtk_widget_set_usize (frame5, 180, 97);

  fixed10 = gtk_fixed_new ();
  gtk_widget_set_name (fixed10, "fixed10");
  gtk_widget_show (fixed10);
  gtk_container_add (GTK_CONTAINER (frame5), fixed10);

  label11 = gtk_label_new ("Ascension Step");
  gtk_widget_set_name (label11, "label11");
  gtk_widget_show (label11);
  gtk_fixed_put (GTK_FIXED (fixed10), label11, 8, 8);
  gtk_widget_set_usize (label11, 78, 17);
  gtk_label_set_justify (GTK_LABEL (label11), GTK_JUSTIFY_LEFT);

  label13 = gtk_label_new ("Third Angle Step");
  gtk_widget_set_name (label13, "label13");
  gtk_widget_show (label13);
  gtk_fixed_put (GTK_FIXED (fixed10), label13, 8, 56);
  gtk_widget_set_usize (label13, 70, 17);
  gtk_label_set_justify (GTK_LABEL (label13), GTK_JUSTIFY_LEFT);

  label12 = gtk_label_new ("Declinaison Step");
  gtk_widget_set_name (label12, "label12");
  gtk_widget_show (label12);
  gtk_fixed_put (GTK_FIXED (fixed10), label12, 8, 32);
  gtk_widget_set_usize (label12, 78, 17);
  gtk_label_set_justify (GTK_LABEL (label12), GTK_JUSTIFY_LEFT);

  spinbutton13_adj = gtk_adjustment_new (ascension_step, 1, 65536, 1, 10, 10);
  spinbutton13 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton13_adj), 1, 0);
  gtk_widget_set_name (spinbutton13, "spinbutton13");
  gtk_widget_show (spinbutton13);
  gtk_fixed_put (GTK_FIXED (fixed10), spinbutton13, 104, 8);
  gtk_widget_set_usize (spinbutton13, 71, 20);

  spinbutton14_adj = gtk_adjustment_new (declinaison_step, 1, 65536, 1, 10, 10);
  spinbutton14 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton14_adj), 1, 0);
  gtk_widget_set_name (spinbutton14, "spinbutton14");
  gtk_widget_show (spinbutton14);
  gtk_fixed_put (GTK_FIXED (fixed10), spinbutton14, 104, 32);
  gtk_widget_set_usize (spinbutton14, 71, 20);

  spinbutton15_adj = gtk_adjustment_new (beta_step, 1, 65536, 1, 10, 10);
  spinbutton15 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton15_adj), 1, 0);
  gtk_widget_set_name (spinbutton15, "spinbutton15");
  gtk_widget_show (spinbutton15);
  gtk_fixed_put (GTK_FIXED (fixed10), spinbutton15, 104, 56);
  gtk_widget_set_usize (spinbutton15, 71, 20);

  label6 = gtk_label_new ("Move Steps Coord");
  gtk_widget_set_name (label6, "label6");
  gtk_widget_show (label6);
  gtk_frame_set_label_widget (GTK_FRAME (frame5), label6);
  gtk_label_set_justify (GTK_LABEL (label6), GTK_JUSTIFY_LEFT);

  Close_Move_Steps = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Move_Steps, "Close_Move_Steps");
  gtk_widget_show (Close_Move_Steps);
  gtk_box_pack_start (GTK_BOX (vbox2), Close_Move_Steps, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Move_Steps), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Move_Steps_clicked),
                      NULL);

  gtk_signal_connect (GTK_OBJECT (spinbutton9), "value-changed",
                      G_CALLBACK (on_lambda_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton10), "value-changed",
                      G_CALLBACK (on_omega_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton11), "value-changed",
                      G_CALLBACK (on_k_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton12), "value-changed",
                      G_CALLBACK (on_alpha_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton13), "value-changed",
                      G_CALLBACK (on_ascension_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton14), "value-changed",
                      G_CALLBACK (on_declinaison_step_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton15), "value-changed",
                      G_CALLBACK (on_beta_step_change),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Move_Steps, Move_Steps, "Move_Steps");
  GLADE_HOOKUP_OBJECT (Move_Steps, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (Move_Steps, frame4, "frame4");
  GLADE_HOOKUP_OBJECT (Move_Steps, fixed9, "fixed9");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton9, "spinbutton9");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton10, "spinbutton10");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton11, "spinbutton11");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton12, "spinbutton12");
  GLADE_HOOKUP_OBJECT (Move_Steps, label7, "label7");
  GLADE_HOOKUP_OBJECT (Move_Steps, label9, "label9");
  GLADE_HOOKUP_OBJECT (Move_Steps, label10, "label10");
  GLADE_HOOKUP_OBJECT (Move_Steps, label8, "label8");
  GLADE_HOOKUP_OBJECT (Move_Steps, label5, "label5");
  GLADE_HOOKUP_OBJECT (Move_Steps, frame5, "frame5");
  GLADE_HOOKUP_OBJECT (Move_Steps, fixed10, "fixed10");
  GLADE_HOOKUP_OBJECT (Move_Steps, label11, "label11");
  GLADE_HOOKUP_OBJECT (Move_Steps, label13, "label13");
  GLADE_HOOKUP_OBJECT (Move_Steps, label12, "label12");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton13, "spinbutton13");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton14, "spinbutton14");
  GLADE_HOOKUP_OBJECT (Move_Steps, spinbutton15, "spinbutton15");
  GLADE_HOOKUP_OBJECT (Move_Steps, label6, "label6");
  GLADE_HOOKUP_OBJECT (Move_Steps, Close_Move_Steps, "Close_Move_Steps");

  return Move_Steps;
}

GtkWidget*
create_Calculus (void)
{
  GtkWidget *Calculus;
  GtkWidget *vbox3;
  GtkWidget *frame6;
  GtkWidget *fixed11;
  GtkWidget *label18;
  GtkWidget *label19;
  GtkWidget *label20;
  GtkWidget *label21;
  GtkObject *spinbutton19_adj;
  GtkWidget *spinbutton19;
  GtkObject *spinbutton20_adj;
  GtkWidget *spinbutton20;
  GtkObject *spinbutton21_adj;
  GtkWidget *spinbutton21;
  GtkObject *spinbutton22_adj;
  GtkWidget *spinbutton22;
  GtkWidget *label17;
  GtkWidget *Close_Calculus;

  Calculus = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Calculus, "Calculus");
  gtk_window_set_title (GTK_WINDOW (Calculus), "Calculus");

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox3, "vbox3");
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (Calculus), vbox3);

  frame6 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame6, "frame6");
  gtk_widget_show (frame6);
  gtk_box_pack_start (GTK_BOX (vbox3), frame6, FALSE, FALSE, 0);
  gtk_widget_set_usize (frame6, -2, 121);

  fixed11 = gtk_fixed_new ();
  gtk_widget_set_name (fixed11, "fixed11");
  gtk_widget_show (fixed11);
  gtk_container_add (GTK_CONTAINER (frame6), fixed11);

  label18 = gtk_label_new ("Maximum Redshift");
  gtk_widget_set_name (label18, "label18");
  gtk_widget_show (label18);
  gtk_fixed_put (GTK_FIXED (fixed11), label18, 8, 8);
  gtk_widget_set_usize (label18, 86, 20);
  gtk_label_set_justify (GTK_LABEL (label18), GTK_JUSTIFY_LEFT);

  label19 = gtk_label_new ("Abacus step");
  gtk_widget_set_name (label19, "label19");
  gtk_widget_show (label19);
  gtk_fixed_put (GTK_FIXED (fixed11), label19, 8, 32);
  gtk_widget_set_usize (label19, 62, 16);
  gtk_label_set_justify (GTK_LABEL (label19), GTK_JUSTIFY_LEFT);

  label20 = gtk_label_new ("Abacus Interactions");
  gtk_widget_set_name (label20, "label20");
  gtk_widget_show (label20);
  gtk_fixed_put (GTK_FIXED (fixed11), label20, 8, 56);
  gtk_widget_set_usize (label20, 94, 20);
  gtk_label_set_justify (GTK_LABEL (label20), GTK_JUSTIFY_LEFT);

  label21 = gtk_label_new ("Distance Interactions");
  gtk_widget_set_name (label21, "label21");
  gtk_widget_show (label21);
  gtk_fixed_put (GTK_FIXED (fixed11), label21, 8, 80);
  gtk_widget_set_usize (label21, 102, 20);
  gtk_label_set_justify (GTK_LABEL (label21), GTK_JUSTIFY_LEFT);

  spinbutton19_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton19 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton19_adj), 1, 0);
  gtk_widget_set_name (spinbutton19, "spinbutton19");
  gtk_widget_show (spinbutton19);
  gtk_fixed_put (GTK_FIXED (fixed11), spinbutton19, 120, 8);
  gtk_widget_set_usize (spinbutton19, 46, 20);

  spinbutton20_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton20 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton20_adj), 1, 0);
  gtk_widget_set_name (spinbutton20, "spinbutton20");
  gtk_widget_show (spinbutton20);
  gtk_fixed_put (GTK_FIXED (fixed11), spinbutton20, 120, 32);
  gtk_widget_set_usize (spinbutton20, 46, 20);

  spinbutton21_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton21 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton21_adj), 1, 0);
  gtk_widget_set_name (spinbutton21, "spinbutton21");
  gtk_widget_show (spinbutton21);
  gtk_fixed_put (GTK_FIXED (fixed11), spinbutton21, 120, 56);
  gtk_widget_set_usize (spinbutton21, 46, 20);

  spinbutton22_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton22 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton22_adj), 1, 0);
  gtk_widget_set_name (spinbutton22, "spinbutton22");
  gtk_widget_show (spinbutton22);
  gtk_fixed_put (GTK_FIXED (fixed11), spinbutton22, 120, 80);
  gtk_widget_set_usize (spinbutton22, 46, 20);

  label17 = gtk_label_new ("label17");
  gtk_widget_set_name (label17, "label17");
  gtk_widget_show (label17);
  gtk_frame_set_label_widget (GTK_FRAME (frame6), label17);
  gtk_label_set_justify (GTK_LABEL (label17), GTK_JUSTIFY_LEFT);

  Close_Calculus = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Calculus, "Close_Calculus");
  gtk_widget_show (Close_Calculus);
  gtk_box_pack_start (GTK_BOX (vbox3), Close_Calculus, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Calculus), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Calculus_clicked),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Calculus, Calculus, "Calculus");
  GLADE_HOOKUP_OBJECT (Calculus, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (Calculus, frame6, "frame6");
  GLADE_HOOKUP_OBJECT (Calculus, fixed11, "fixed11");
  GLADE_HOOKUP_OBJECT (Calculus, label18, "label18");
  GLADE_HOOKUP_OBJECT (Calculus, label19, "label19");
  GLADE_HOOKUP_OBJECT (Calculus, label20, "label20");
  GLADE_HOOKUP_OBJECT (Calculus, label21, "label21");
  GLADE_HOOKUP_OBJECT (Calculus, spinbutton19, "spinbutton19");
  GLADE_HOOKUP_OBJECT (Calculus, spinbutton20, "spinbutton20");
  GLADE_HOOKUP_OBJECT (Calculus, spinbutton21, "spinbutton21");
  GLADE_HOOKUP_OBJECT (Calculus, spinbutton22, "spinbutton22");
  GLADE_HOOKUP_OBJECT (Calculus, label17, "label17");
  GLADE_HOOKUP_OBJECT (Calculus, Close_Calculus, "Close_Calculus");

  return Calculus;
}

GtkWidget*
create_Options (void)
{
  GtkWidget *Options;
  GtkWidget *vbox4;
  GtkWidget *OPT;
  GtkWidget *fixed12;
  GtkObject *spinbutton23_adj;
  GtkWidget *spinbutton23;
  GtkObject *spinbutton24_adj;
  GtkWidget *spinbutton24;
  GtkObject *spinbutton25_adj;
  GtkWidget *spinbutton25;
  GtkWidget *label23;
  GtkWidget *label25;
  GtkWidget *checkbutton1;
  GtkWidget *label24;
  GtkWidget *label22;
  GtkWidget *Close_Options;
	
	extern int data_lenght;
	extern int data_lenght_max;
	extern double zoom_rate;

  Options = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Options, "Options");
  gtk_window_set_title (GTK_WINDOW (Options), "Options");

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox4, "vbox4");
  gtk_widget_show (vbox4);
  gtk_container_add (GTK_CONTAINER (Options), vbox4);

  OPT = gtk_frame_new (NULL);
  gtk_widget_set_name (OPT, "OPT");
  gtk_widget_show (OPT);
  gtk_box_pack_start (GTK_BOX (vbox4), OPT, FALSE, FALSE, 0);
  gtk_widget_set_usize (OPT, -2, 130);

  fixed12 = gtk_fixed_new ();
  gtk_widget_set_name (fixed12, "fixed12");
  gtk_widget_show (fixed12);
  gtk_container_add (GTK_CONTAINER (OPT), fixed12);

  spinbutton23_adj = gtk_adjustment_new (data_lenght, 0, data_lenght_max, 1, 100, 100);
  spinbutton23 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton23_adj), 1, 0);
  gtk_widget_set_name (spinbutton23, "spinbutton23");
  gtk_widget_show (spinbutton23);
  gtk_fixed_put (GTK_FIXED (fixed12), spinbutton23, 80, 16);
  gtk_widget_set_usize (spinbutton23, 46, 20);

  spinbutton24_adj = gtk_adjustment_new (zoom_rate, 0, 0.999, 0.001, 100, 100);
  spinbutton24 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton24_adj), 1, 5);
  gtk_widget_set_name (spinbutton24, "spinbutton24");
  gtk_widget_show (spinbutton24);
  gtk_fixed_put (GTK_FIXED (fixed12), spinbutton24, 80, 40);
  gtk_widget_set_usize (spinbutton24, 46, 20);

  spinbutton25_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton25 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton25_adj), 1, 0);
  gtk_widget_set_name (spinbutton25, "spinbutton25");
  gtk_widget_show (spinbutton25);
  gtk_fixed_put (GTK_FIXED (fixed12), spinbutton25, 80, 64);
  gtk_widget_set_usize (spinbutton25, 46, 20);

  label23 = gtk_label_new ("Data lenght");
  gtk_widget_set_name (label23, "label23");
  gtk_widget_show (label23);
  gtk_fixed_put (GTK_FIXED (fixed12), label23, 16, 16);
  gtk_widget_set_usize (label23, 54, 16);
  gtk_label_set_justify (GTK_LABEL (label23), GTK_JUSTIFY_LEFT);

  label25 = gtk_label_new ("Star size");
  gtk_widget_set_name (label25, "label25");
  gtk_widget_show (label25);
  gtk_fixed_put (GTK_FIXED (fixed12), label25, 16, 64);
  gtk_widget_set_usize (label25, 54, 16);
  gtk_label_set_justify (GTK_LABEL (label25), GTK_JUSTIFY_LEFT);

  checkbutton1 = gtk_check_button_new_with_mnemonic ("Angles H:M:S");
  gtk_widget_set_name (checkbutton1, "checkbutton1");
  gtk_widget_show (checkbutton1);
  gtk_fixed_put (GTK_FIXED (fixed12), checkbutton1, 8, 96);
  gtk_widget_set_usize (checkbutton1, 118, 20);

  label24 = gtk_label_new ("Zoom rate");
  gtk_widget_set_name (label24, "label24");
  gtk_widget_show (label24);
  gtk_fixed_put (GTK_FIXED (fixed12), label24, 16, 40);
  gtk_widget_set_usize (label24, 46, 16);
  gtk_label_set_justify (GTK_LABEL (label24), GTK_JUSTIFY_LEFT);

  label22 = gtk_label_new ("Options");
  gtk_widget_set_name (label22, "label22");
  gtk_widget_show (label22);
  gtk_frame_set_label_widget (GTK_FRAME (OPT), label22);
  gtk_label_set_justify (GTK_LABEL (label22), GTK_JUSTIFY_LEFT);

  Close_Options = gtk_button_new_with_mnemonic ("Close Options");
  gtk_widget_set_name (Close_Options, "Close_Options");
  gtk_widget_show (Close_Options);
  gtk_box_pack_start (GTK_BOX (vbox4), Close_Options, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Options), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Options_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton23), "value-changed",
                      GTK_SIGNAL_FUNC (on_change_data_lenght),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton24), "value-changed",
                      GTK_SIGNAL_FUNC (on_change_zoom_rate),
                      NULL);
   g_signal_connect ((gpointer) checkbutton1, "toggled",
                    G_CALLBACK (on_checkbutton1_toggled),
                    NULL);

		     /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Options, Options, "Options");
  GLADE_HOOKUP_OBJECT (Options, vbox4, "vbox4");
  GLADE_HOOKUP_OBJECT (Options, OPT, "OPT");
  GLADE_HOOKUP_OBJECT (Options, fixed12, "fixed12");
  GLADE_HOOKUP_OBJECT (Options, spinbutton23, "spinbutton23");
  GLADE_HOOKUP_OBJECT (Options, spinbutton24, "spinbutton24");
  GLADE_HOOKUP_OBJECT (Options, spinbutton25, "spinbutton25");
  GLADE_HOOKUP_OBJECT (Options, label23, "label23");
  GLADE_HOOKUP_OBJECT (Options, label25, "label25");
  GLADE_HOOKUP_OBJECT (Options, checkbutton1, "checkbutton1");
  GLADE_HOOKUP_OBJECT (Options, label24, "label24");
  GLADE_HOOKUP_OBJECT (Options, label22, "label22");
  GLADE_HOOKUP_OBJECT (Options, Close_Options, "Close_Options");

  return Options;
}





GtkWidget*
create_Compute_Distance (void)
{
  GtkWidget *Compute_Distance;
  GtkWidget *vbox5;
  GtkWidget *frame8;
  GtkWidget *fixed13;
  GtkObject *spinbutton26_adj;
  GtkWidget *spinbutton26;
  GtkObject *spinbutton27_adj;
  GtkWidget *spinbutton27;
  GtkObject *spinbutton28_adj;
  GtkWidget *spinbutton28;
  GtkObject *spinbutton29_adj;
  GtkWidget *spinbutton29;
  GtkWidget *label29;
  GtkWidget *label51;
  GtkWidget *label52;
  GtkWidget *label53;
  GtkWidget *label54;
  GtkWidget *button7;
  GtkWidget *label26;
  GtkWidget *frame9;
  GtkWidget *fixed14;
  GtkObject *spinbutton30_adj;
  GtkWidget *spinbutton30;
  GtkObject *spinbutton31_adj;
  GtkWidget *spinbutton31;
  GtkObject *spinbutton32_adj;
  GtkWidget *spinbutton32;
  GtkObject *spinbutton33_adj;
  GtkWidget *spinbutton33;
  GtkWidget *label30;
  GtkWidget *label55;
  GtkWidget *label56;
  GtkWidget *label57;
  GtkWidget *label58;
  GtkWidget *button8;
  GtkWidget *label27;
  GtkWidget *frame10;
  GtkWidget *fixed15;
  GtkWidget *button13;
  GtkWidget *label28;
  GtkWidget *Close_Isotropic_Distribution;

  Compute_Distance = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Compute_Distance, "Compute_Distance");
  gtk_container_set_border_width (GTK_CONTAINER (Compute_Distance), 3);
  gtk_window_set_title (GTK_WINDOW (Compute_Distance), "Compute Distance");

  vbox5 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox5, "vbox5");
  gtk_widget_show (vbox5);
  gtk_container_add (GTK_CONTAINER (Compute_Distance), vbox5);

  frame8 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame8, "frame8");
  gtk_widget_show (frame8);
  gtk_box_pack_start (GTK_BOX (vbox5), frame8, TRUE, TRUE, 0);
  gtk_widget_set_size_request (frame8, 130, -2);

  fixed13 = gtk_fixed_new ();
  gtk_widget_set_name (fixed13, "fixed13");
  gtk_widget_show (fixed13);
  gtk_container_add (GTK_CONTAINER (frame8), fixed13);

  spinbutton26_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton26 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton26_adj), 1, 0);
  gtk_widget_set_name (spinbutton26, "spinbutton26");
  gtk_widget_show (spinbutton26);
  gtk_fixed_put (GTK_FIXED (fixed13), spinbutton26, 120, 8);
  gtk_widget_set_size_request (spinbutton26, 70, 20);

  spinbutton27_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton27 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton27_adj), 1, 0);
  gtk_widget_set_name (spinbutton27, "spinbutton27");
  gtk_widget_show (spinbutton27);
  gtk_fixed_put (GTK_FIXED (fixed13), spinbutton27, 120, 32);
  gtk_widget_set_size_request (spinbutton27, 70, 20);

  spinbutton28_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton28 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton28_adj), 1, 0);
  gtk_widget_set_name (spinbutton28, "spinbutton28");
  gtk_widget_show (spinbutton28);
  gtk_fixed_put (GTK_FIXED (fixed13), spinbutton28, 120, 56);
  gtk_widget_set_size_request (spinbutton28, 70, 20);

  spinbutton29_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton29 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton29_adj), 1, 0);
  gtk_widget_set_name (spinbutton29, "spinbutton29");
  gtk_widget_show (spinbutton29);
  gtk_fixed_put (GTK_FIXED (fixed13), spinbutton29, 120, 80);
  gtk_widget_set_size_request (spinbutton29, 70, 20);

  label29 = gtk_label_new ("Quasar 1");
  gtk_widget_set_name (label29, "label29");
  gtk_widget_show (label29);
  gtk_fixed_put (GTK_FIXED (fixed13), label29, 16, 24);
  gtk_widget_set_size_request (label29, 56, 16);
  gtk_label_set_justify (GTK_LABEL (label29), GTK_JUSTIFY_LEFT);

  label51 = gtk_label_new ("x");
  gtk_widget_set_name (label51, "label51");
  gtk_widget_show (label51);
  gtk_fixed_put (GTK_FIXED (fixed13), label51, 80, 8);
  gtk_widget_set_size_request (label51, 43, 16);
  gtk_label_set_justify (GTK_LABEL (label51), GTK_JUSTIFY_LEFT);

  label52 = gtk_label_new ("y");
  gtk_widget_set_name (label52, "label52");
  gtk_widget_show (label52);
  gtk_fixed_put (GTK_FIXED (fixed13), label52, 80, 32);
  gtk_widget_set_size_request (label52, 42, 16);
  gtk_label_set_justify (GTK_LABEL (label52), GTK_JUSTIFY_LEFT);

  label53 = gtk_label_new ("z");
  gtk_widget_set_name (label53, "label53");
  gtk_widget_show (label53);
  gtk_fixed_put (GTK_FIXED (fixed13), label53, 80, 56);
  gtk_widget_set_size_request (label53, 43, 16);
  gtk_label_set_justify (GTK_LABEL (label53), GTK_JUSTIFY_LEFT);

  label54 = gtk_label_new ("t");
  gtk_widget_set_name (label54, "label54");
  gtk_widget_show (label54);
  gtk_fixed_put (GTK_FIXED (fixed13), label54, 80, 80);
  gtk_widget_set_size_request (label54, 42, 16);
  gtk_label_set_justify (GTK_LABEL (label54), GTK_JUSTIFY_LEFT);

  button7 = gtk_button_new_with_mnemonic ("Choose");
  gtk_widget_set_name (button7, "button7");
  gtk_widget_show (button7);
  gtk_fixed_put (GTK_FIXED (fixed13), button7, 16, 56);
  gtk_widget_set_size_request (button7, 72, 32);

  label26 = gtk_label_new ("Quasar 1");
  gtk_widget_set_name (label26, "label26");
  gtk_widget_show (label26);
  gtk_frame_set_label_widget (GTK_FRAME (frame8), label26);
  gtk_label_set_justify (GTK_LABEL (label26), GTK_JUSTIFY_LEFT);

  frame9 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame9, "frame9");
  gtk_widget_show (frame9);
  gtk_box_pack_start (GTK_BOX (vbox5), frame9, TRUE, TRUE, 0);
  gtk_widget_set_size_request (frame9, 130, 114);

  fixed14 = gtk_fixed_new ();
  gtk_widget_set_name (fixed14, "fixed14");
  gtk_widget_show (fixed14);
  gtk_container_add (GTK_CONTAINER (frame9), fixed14);

  spinbutton30_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton30 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton30_adj), 1, 0);
  gtk_widget_set_name (spinbutton30, "spinbutton30");
  gtk_widget_show (spinbutton30);
  gtk_fixed_put (GTK_FIXED (fixed14), spinbutton30, 120, 8);
  gtk_widget_set_size_request (spinbutton30, 70, 20);

  spinbutton31_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton31 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton31_adj), 1, 0);
  gtk_widget_set_name (spinbutton31, "spinbutton31");
  gtk_widget_show (spinbutton31);
  gtk_fixed_put (GTK_FIXED (fixed14), spinbutton31, 120, 32);
  gtk_widget_set_size_request (spinbutton31, 70, 20);

  spinbutton32_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton32 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton32_adj), 1, 0);
  gtk_widget_set_name (spinbutton32, "spinbutton32");
  gtk_widget_show (spinbutton32);
  gtk_fixed_put (GTK_FIXED (fixed14), spinbutton32, 120, 56);
  gtk_widget_set_size_request (spinbutton32, 70, 20);

  spinbutton33_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  spinbutton33 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton33_adj), 1, 0);
  gtk_widget_set_name (spinbutton33, "spinbutton33");
  gtk_widget_show (spinbutton33);
  gtk_fixed_put (GTK_FIXED (fixed14), spinbutton33, 120, 80);
  gtk_widget_set_size_request (spinbutton33, 70, 20);

  label30 = gtk_label_new ("Quasar 2");
  gtk_widget_set_name (label30, "label30");
  gtk_widget_show (label30);
  gtk_fixed_put (GTK_FIXED (fixed14), label30, 16, 24);
  gtk_widget_set_size_request (label30, 56, 16);
  gtk_label_set_justify (GTK_LABEL (label30), GTK_JUSTIFY_LEFT);

  label55 = gtk_label_new ("x");
  gtk_widget_set_name (label55, "label55");
  gtk_widget_show (label55);
  gtk_fixed_put (GTK_FIXED (fixed14), label55, 80, 8);
  gtk_widget_set_size_request (label55, 42, 16);
  gtk_label_set_justify (GTK_LABEL (label55), GTK_JUSTIFY_LEFT);

  label56 = gtk_label_new ("y");
  gtk_widget_set_name (label56, "label56");
  gtk_widget_show (label56);
  gtk_fixed_put (GTK_FIXED (fixed14), label56, 80, 32);
  gtk_widget_set_size_request (label56, 42, 16);
  gtk_label_set_justify (GTK_LABEL (label56), GTK_JUSTIFY_LEFT);

  label57 = gtk_label_new ("z");
  gtk_widget_set_name (label57, "label57");
  gtk_widget_show (label57);
  gtk_fixed_put (GTK_FIXED (fixed14), label57, 80, 56);
  gtk_widget_set_size_request (label57, 43, 16);
  gtk_label_set_justify (GTK_LABEL (label57), GTK_JUSTIFY_LEFT);

  label58 = gtk_label_new ("t");
  gtk_widget_set_name (label58, "label58");
  gtk_widget_show (label58);
  gtk_fixed_put (GTK_FIXED (fixed14), label58, 80, 80);
  gtk_widget_set_size_request (label58, 43, 16);
  gtk_label_set_justify (GTK_LABEL (label58), GTK_JUSTIFY_LEFT);

  button8 = gtk_button_new_with_mnemonic ("Choose");
  gtk_widget_set_name (button8, "button8");
  gtk_widget_show (button8);
  gtk_fixed_put (GTK_FIXED (fixed14), button8, 16, 56);
  gtk_widget_set_size_request (button8, 72, 32);

  label27 = gtk_label_new ("Quasar 2");
  gtk_widget_set_name (label27, "label27");
  gtk_widget_show (label27);
  gtk_frame_set_label_widget (GTK_FRAME (frame9), label27);
  gtk_label_set_justify (GTK_LABEL (label27), GTK_JUSTIFY_LEFT);

  frame10 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame10, "frame10");
  gtk_widget_show (frame10);
  gtk_box_pack_start (GTK_BOX (vbox5), frame10, TRUE, TRUE, 0);
  gtk_widget_set_size_request (frame10, 130, 42);

  fixed15 = gtk_fixed_new ();
  gtk_widget_set_name (fixed15, "fixed15");
  gtk_widget_show (fixed15);
  gtk_container_add (GTK_CONTAINER (frame10), fixed15);
  gtk_widget_set_size_request (fixed15, 209, -2);

  entry3 = gtk_entry_new ();
  gtk_widget_set_name (entry3, "entry3");
  gtk_widget_show (entry3);
  gtk_fixed_put (GTK_FIXED (fixed15), entry3, 128, 8);
  gtk_widget_set_size_request (entry3, 56, 32);

  button13 = gtk_button_new_with_mnemonic ("Compute distance");
  gtk_widget_set_name (button13, "button13");
  gtk_widget_show (button13);
  gtk_fixed_put (GTK_FIXED (fixed15), button13, 8, 8);
  gtk_widget_set_size_request (button13, 120, 32);

  label28 = gtk_label_new ("Result");
  gtk_widget_set_name (label28, "label28");
  gtk_widget_show (label28);
  gtk_frame_set_label_widget (GTK_FRAME (frame10), label28);
  gtk_label_set_justify (GTK_LABEL (label28), GTK_JUSTIFY_LEFT);

  Close_Isotropic_Distribution = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Isotropic_Distribution, "Close_Isotropic_Distribution");
  gtk_widget_show (Close_Isotropic_Distribution);
  gtk_box_pack_start (GTK_BOX (vbox5), Close_Isotropic_Distribution, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) button7, "clicked",
                    G_CALLBACK (on_button7_clicked),
                    NULL);
  g_signal_connect ((gpointer) button8, "clicked",
                    G_CALLBACK (on_button8_clicked),
                    NULL);
  g_signal_connect ((gpointer) button13, "clicked",
                    G_CALLBACK (on_button13_clicked),
                    NULL);
  g_signal_connect ((gpointer) Close_Isotropic_Distribution, "clicked",
                    G_CALLBACK (on_Close_Isotropic_Distribution_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Compute_Distance, Compute_Distance, "Compute_Distance");
  GLADE_HOOKUP_OBJECT (Compute_Distance, vbox5, "vbox5");
  GLADE_HOOKUP_OBJECT (Compute_Distance, frame8, "frame8");
  GLADE_HOOKUP_OBJECT (Compute_Distance, fixed13, "fixed13");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton26, "spinbutton26");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton27, "spinbutton27");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton28, "spinbutton28");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton29, "spinbutton29");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label29, "label29");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label51, "label51");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label52, "label52");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label53, "label53");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label54, "label54");
  GLADE_HOOKUP_OBJECT (Compute_Distance, button7, "button7");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label26, "label26");
  GLADE_HOOKUP_OBJECT (Compute_Distance, frame9, "frame9");
  GLADE_HOOKUP_OBJECT (Compute_Distance, fixed14, "fixed14");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton30, "spinbutton30");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton31, "spinbutton31");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton32, "spinbutton32");
  GLADE_HOOKUP_OBJECT (Compute_Distance, spinbutton33, "spinbutton33");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label30, "label30");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label55, "label55");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label56, "label56");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label57, "label57");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label58, "label58");
  GLADE_HOOKUP_OBJECT (Compute_Distance, button8, "button8");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label27, "label27");
  GLADE_HOOKUP_OBJECT (Compute_Distance, frame10, "frame10");
  GLADE_HOOKUP_OBJECT (Compute_Distance, fixed15, "fixed15");
  GLADE_HOOKUP_OBJECT (Compute_Distance, entry3, "entry3");
  GLADE_HOOKUP_OBJECT (Compute_Distance, button13, "button13");
  GLADE_HOOKUP_OBJECT (Compute_Distance, label28, "label28");
  GLADE_HOOKUP_OBJECT (Compute_Distance, Close_Isotropic_Distribution, "Close_Isotropic_Distribution");

  return Compute_Distance;
}




GtkWidget*
create_Isotropic_Distribution (void)
{
  GtkWidget *Isotropic_Distribution;
  GtkWidget *vbox6;
  GtkWidget *frame11;
  GtkWidget *fixed16;
  GtkObject *spinbutton35_adj;

  GtkObject *spinbutton36_adj;

  GtkObject *spinbutton37_adj;

  GtkObject *spinbutton38_adj;

  GtkObject *spinbutton39_adj;

  GtkObject *spinbutton40_adj;

  GtkWidget *label34;
  GtkWidget *label35;
  GtkWidget *label36;
  GtkWidget *label37;
  GtkWidget *label38;
  GtkWidget *label33;
  GtkWidget *button10;
  GtkWidget *label32;
  GtkWidget *Close_Isotropic_Distribution;

  Isotropic_Distribution = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Isotropic_Distribution, "Isotropic_Distribution");
  gtk_container_set_border_width (GTK_CONTAINER (Isotropic_Distribution), 8);
  gtk_window_set_title (GTK_WINDOW (Isotropic_Distribution), "Isotropic Distribution");

  vbox6 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox6, "vbox6");
  gtk_widget_show (vbox6);
  gtk_container_add (GTK_CONTAINER (Isotropic_Distribution), vbox6);

  frame11 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame11, "frame11");
  gtk_widget_show (frame11);
  gtk_box_pack_start (GTK_BOX (vbox6), frame11, TRUE, TRUE, 0);
  gtk_widget_set_usize (frame11, 193, 209);

  fixed16 = gtk_fixed_new ();
  gtk_widget_set_name (fixed16, "fixed16");
  gtk_widget_show (fixed16);
  gtk_container_add (GTK_CONTAINER (frame11), fixed16);
  gtk_widget_set_usize (fixed16, 183, 188);

  spinbutton35_adj = gtk_adjustment_new (0, 0, 0xFFFFFFFF, 1, 10, 10);
  spinbutton35 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton35_adj), 1, 5);
  gtk_widget_set_name (spinbutton35, "spinbutton35");
  gtk_widget_show (spinbutton35);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton35, 112, 8);
  gtk_widget_set_usize (spinbutton35, 70, 20);

  spinbutton36_adj = gtk_adjustment_new (1, -100, 100, 0.00001, 10, 10);
  spinbutton36 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton36_adj), 1, 5);
  gtk_widget_set_name (spinbutton36, "spinbutton36");
  gtk_widget_show (spinbutton36);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton36, 112, 32);
  gtk_widget_set_usize (spinbutton36, 70, 20);

  spinbutton37_adj = gtk_adjustment_new (1, -100, 100, 0.00001, 10, 10);
  spinbutton37 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton37_adj), 1, 5);
  gtk_widget_set_name (spinbutton37, "spinbutton37");
  gtk_widget_show (spinbutton37);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton37, 112, 56);
  gtk_widget_set_usize (spinbutton37, 70, 20);

  spinbutton38_adj = gtk_adjustment_new (1, -100, 100, 0.00001, 10, 10);
  spinbutton38 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton38_adj), 1, 5);
  gtk_widget_set_name (spinbutton38, "spinbutton38");
  gtk_widget_show (spinbutton38);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton38, 112, 80);
  gtk_widget_set_usize (spinbutton38, 70, 20);

  spinbutton39_adj = gtk_adjustment_new (1, -100, 100, 0.00001, 10, 10);
  spinbutton39 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton39_adj), 1, 5);
  gtk_widget_set_name (spinbutton39, "spinbutton39");
  gtk_widget_show (spinbutton39);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton39, 112, 104);
  gtk_widget_set_usize (spinbutton39, 70, 20);

  spinbutton40_adj = gtk_adjustment_new (1, -100, 100, 0.00001, 10, 10);
  spinbutton40 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton40_adj), 1, 5);
  gtk_widget_set_name (spinbutton40, "spinbutton40");
  gtk_widget_show (spinbutton40);
  gtk_fixed_put (GTK_FIXED (fixed16), spinbutton40, 112, 128);
  gtk_widget_set_usize (spinbutton40, 70, 20);

  label34 = gtk_label_new ("Minumum Redshift");
  gtk_widget_set_name (label34, "label34");
  gtk_widget_show (label34);
  gtk_fixed_put (GTK_FIXED (fixed16), label34, 8, 32);
  gtk_widget_set_usize (label34, 86, 16);
  gtk_label_set_justify (GTK_LABEL (label34), GTK_JUSTIFY_LEFT);

  label35 = gtk_label_new ("Maximum Redshift");
  gtk_widget_set_name (label35, "label35");
  gtk_widget_show (label35);
  gtk_fixed_put (GTK_FIXED (fixed16), label35, 8, 56);
  gtk_widget_set_usize (label35, 86, 16);
  gtk_label_set_justify (GTK_LABEL (label35), GTK_JUSTIFY_LEFT);

  label36 = gtk_label_new ("Ascension");
  gtk_widget_set_name (label36, "label36");
  gtk_widget_show (label36);
  gtk_fixed_put (GTK_FIXED (fixed16), label36, 8, 80);
  gtk_widget_set_usize (label36, 50, 16);
  gtk_label_set_justify (GTK_LABEL (label36), GTK_JUSTIFY_LEFT);

  label37 = gtk_label_new ("Declination");
  gtk_widget_set_name (label37, "label37");
  gtk_widget_show (label37);
  gtk_fixed_put (GTK_FIXED (fixed16), label37, 8, 104);
  gtk_widget_set_usize (label37, 54, 16);
  gtk_label_set_justify (GTK_LABEL (label37), GTK_JUSTIFY_LEFT);

  label38 = gtk_label_new ("Beta");
  gtk_widget_set_name (label38, "label38");
  gtk_widget_show (label38);
  gtk_fixed_put (GTK_FIXED (fixed16), label38, 8, 128);
  gtk_widget_set_usize (label38, 32, 16);
  gtk_label_set_justify (GTK_LABEL (label38), GTK_JUSTIFY_LEFT);

  label33 = gtk_label_new ("Isotropic Distrubution");
  gtk_widget_set_name (label33, "label33");
  gtk_widget_show (label33);
  gtk_fixed_put (GTK_FIXED (fixed16), label33, 8, 8);
  gtk_widget_set_usize (label33, 102, 16);
  gtk_label_set_justify (GTK_LABEL (label33), GTK_JUSTIFY_LEFT);

  button10 = gtk_button_new_with_mnemonic ("Compute The Isotropic Distribution");
  gtk_widget_set_name (button10, "button10");
  gtk_widget_show (button10);
  gtk_fixed_put (GTK_FIXED (fixed16), button10, 8, 160);
  gtk_widget_set_usize (button10, 175, 28);

  label32 = gtk_label_new ("Isotropic Distribution");
  gtk_widget_set_name (label32, "label32");
  gtk_widget_show (label32);
  gtk_frame_set_label_widget (GTK_FRAME (frame11), label32);
  gtk_label_set_justify (GTK_LABEL (label32), GTK_JUSTIFY_LEFT);

  Close_Isotropic_Distribution = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Isotropic_Distribution, "Close_Isotropic_Distribution");
  gtk_widget_show (Close_Isotropic_Distribution);
  gtk_box_pack_start (GTK_BOX (vbox6), Close_Isotropic_Distribution, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Isotropic_Distribution), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Isotropic_Distribution_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button10), "clicked",
                      GTK_SIGNAL_FUNC (on_Compute_Isotropic_Distribution_clicked),
                      NULL);
  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Isotropic_Distribution, Isotropic_Distribution, "Isotropic_Distribution");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, vbox6, "vbox6");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, frame11, "frame11");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, fixed16, "fixed16");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton35, "spinbutton35");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton36, "spinbutton36");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton37, "spinbutton37");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton38, "spinbutton38");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton39, "spinbutton39");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, spinbutton40, "spinbutton40");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label34, "label34");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label35, "label35");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label36, "label36");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label37, "label37");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label38, "label38");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label33, "label33");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, button10, "button10");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, label32, "label32");
  GLADE_HOOKUP_OBJECT (Isotropic_Distribution, Close_Isotropic_Distribution, "Close_Isotropic_Distribution");

  return Isotropic_Distribution;
}

GtkWidget*
create_Lambda_vs_Omega (void)
{
  GtkWidget *Lambda_vs_Omega;
  GtkWidget *vbox7;
  GtkWidget *frame12;
  GtkWidget *fixed17;
  GtkObject *spinbutton41_adj;
  GtkWidget *spinbutton41;
  GtkObject *spinbutton42_adj;
  GtkWidget *spinbutton42;
  GtkObject *scale_factor_adj;
  GtkWidget *scale_factor;
  GtkObject *Z_decoupling_adj;
  GtkWidget *Z_decoupling;
  GtkWidget *label42;
  GtkWidget *label47;
  GtkWidget *label46;
  GtkWidget *label39;
  GtkWidget *Close_Lambda_vs_Omega;
  GtkWidget* zr_label;
  GtkWidget* h_label;

  extern double delta_age_universe;

  Lambda_vs_Omega = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Lambda_vs_Omega, "Lambda_vs_Omega");
  gtk_window_set_title (GTK_WINDOW (Lambda_vs_Omega), "Lambda vs Omega");

  vbox7 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox7, "vbox7");
  gtk_widget_show (vbox7);
  gtk_container_add (GTK_CONTAINER (Lambda_vs_Omega), vbox7);

  frame12 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame12, "frame12");
  gtk_widget_show (frame12);
  gtk_box_pack_start (GTK_BOX (vbox7), frame12, TRUE, TRUE, 0);

  fixed17 = gtk_fixed_new ();
  gtk_widget_set_name (fixed17, "fixed17");
  gtk_widget_show (fixed17);
  gtk_container_add (GTK_CONTAINER (frame12), fixed17);
  gtk_widget_set_usize (fixed17, -2, 160);

  spinbutton41_adj = gtk_adjustment_new (age_universe, 0, 100, 1, 10, 10);
  spinbutton41 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton41_adj), 1, 5);
  gtk_widget_set_name (spinbutton41, "spinbutton41");
  gtk_widget_show (spinbutton41);
  gtk_fixed_put (GTK_FIXED (fixed17), spinbutton41, 136, 104);
  gtk_widget_set_usize (spinbutton41, 73, 20);

  spinbutton42_adj = gtk_adjustment_new (delta_age_universe, -100, 100, 1, 10, 10);
  spinbutton42 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton42_adj), 1, 5);
  gtk_widget_set_name (spinbutton42, "spinbutton42");
  gtk_widget_show (spinbutton42);
  gtk_fixed_put (GTK_FIXED (fixed17), spinbutton42, 240, 104);
  gtk_widget_set_usize (spinbutton42, 70, 20);


  scale_factor_adj = gtk_adjustment_new (h, 0.1, 2, 0.01, 10, 10);
  scale_factor = gtk_spin_button_new (GTK_ADJUSTMENT (scale_factor_adj), 1, 2);
  gtk_widget_set_name (scale_factor, "scale_factor");
  gtk_widget_show (scale_factor);
  gtk_fixed_put (GTK_FIXED (fixed17), scale_factor, 300, 32);
  gtk_widget_set_usize (scale_factor, 70, 20);


  Z_decoupling_adj = gtk_adjustment_new (zr, 0, 1500, 10, 10, 10);
  Z_decoupling = gtk_spin_button_new (GTK_ADJUSTMENT (Z_decoupling_adj), 1, 0);
  gtk_widget_set_name (Z_decoupling, "Z_decoupling");
  gtk_widget_show (Z_decoupling);
  gtk_fixed_put (GTK_FIXED (fixed17), Z_decoupling, 300, 8);
  gtk_widget_set_usize (Z_decoupling, 70, 20);

  entry1 = gtk_entry_new ();
  gtk_widget_set_name (entry1, "entry1");
  gtk_widget_show (entry1);
  gtk_fixed_put (GTK_FIXED (fixed17), entry1, 136, 128);
  gtk_widget_set_usize (entry1, 73, 20);

  label40 = gtk_label_new ("Line for k=0");
  gtk_widget_set_name (label40, "label40");
  gtk_widget_show (label40);
  gtk_fixed_put (GTK_FIXED (fixed17), label40, 4, 8);
  gtk_widget_set_usize (label40, 154, 20);
  gtk_label_set_justify (GTK_LABEL (label40), GTK_JUSTIFY_LEFT);

  graphC0_color = gtk_drawing_area_new ();
  gtk_widget_set_name (graphC0_color, "Color for graphC0");
  gtk_widget_show (graphC0_color);
  gtk_fixed_put (GTK_FIXED (fixed17), graphC0_color, 8, 8);
  gtk_widget_set_size_request (graphC0_color, 30, 20);

  label41 = gtk_label_new ("Limit Curve");
  gtk_widget_set_name (label41, "label41");
  gtk_widget_show (label41);
  gtk_fixed_put (GTK_FIXED (fixed17), label41, 4, 32);
  gtk_widget_set_usize (label41, 154, 20);
  gtk_label_set_justify (GTK_LABEL (label41), GTK_JUSTIFY_LEFT);

  graphC2_color = gtk_drawing_area_new ();
  gtk_widget_set_name (graphC2_color, "Color for graphC2");
  gtk_widget_show (graphC2_color);
  gtk_fixed_put (GTK_FIXED (fixed17), graphC2_color, 8, 32);
  gtk_widget_set_size_request (graphC2_color, 30, 20);

  label45 = gtk_label_new ("         Constant Age Curve");
  gtk_widget_set_name (label45, "label45");
  gtk_widget_show (label45);
  gtk_fixed_put (GTK_FIXED (fixed17), label45, 4, 56);
  gtk_widget_set_usize (label45, 174, 16);
  gtk_label_set_justify (GTK_LABEL (label45), GTK_JUSTIFY_LEFT);

  graphC3_color = gtk_drawing_area_new ();
  gtk_widget_set_name (graphC3_color, "Color for graphC3");
  gtk_widget_show (graphC3_color);
  gtk_fixed_put (GTK_FIXED (fixed17), graphC3_color, 8, 56);
  gtk_widget_set_size_request (graphC3_color, 30, 20);

  label44 = gtk_label_new ("          Antipode decoupling");
  gtk_widget_set_name (label44, "label44");
  gtk_widget_show (label44);
  gtk_fixed_put (GTK_FIXED (fixed17), label44, 4, 80);
  gtk_widget_set_usize (label44, 174, 16);
  gtk_label_set_justify (GTK_LABEL (label44), GTK_JUSTIFY_LEFT);

  graphC4_color = gtk_drawing_area_new ();
  gtk_widget_set_name (graphC4_color, "Color for graphC3");
  gtk_widget_show (graphC4_color);
  gtk_fixed_put (GTK_FIXED (fixed17), graphC4_color, 8, 80);
  gtk_widget_set_size_request (graphC4_color, 30, 20);

  zr_label = gtk_label_new ("Z decoupling");
  gtk_widget_set_name (zr_label, "zr_label");
  gtk_widget_show (zr_label);
  gtk_fixed_put (GTK_FIXED (fixed17), zr_label, 170, 8);
  gtk_widget_set_usize (zr_label, 154, 16);
  gtk_label_set_justify (GTK_LABEL (zr_label), GTK_JUSTIFY_LEFT);


  h_label = gtk_label_new ("Scale factor (h)");
  gtk_widget_set_name (h_label, "h_label");
  gtk_widget_show (h_label);
  gtk_fixed_put (GTK_FIXED (fixed17), h_label, 170, 32);
  gtk_widget_set_usize (h_label, 154, 16);
  gtk_label_set_justify (GTK_LABEL (h_label), GTK_JUSTIFY_LEFT);

  label43 = gtk_label_new ("Universe Selected Age");
  gtk_widget_set_name (label43, "label43");
  gtk_widget_show (label43);
  gtk_fixed_put (GTK_FIXED (fixed17), label43, 16, 104);
  gtk_widget_set_usize (label43, 112, 20);
  gtk_label_set_justify (GTK_LABEL (label43), GTK_JUSTIFY_LEFT);

  label42 = gtk_label_new ("Number of Causals Cells");
  gtk_widget_set_name (label42, "label42");
  gtk_widget_show (label42);
  gtk_fixed_put (GTK_FIXED (fixed17), label42, 16, 128);
  gtk_widget_set_usize (label42, 110, 16);
  gtk_label_set_justify (GTK_LABEL (label42), GTK_JUSTIFY_LEFT);

  label47 = gtk_label_new (" +/-");
  gtk_widget_set_name (label47, "label47");
  gtk_widget_show (label47);
  gtk_fixed_put (GTK_FIXED (fixed17), label47, 208, 104);
  gtk_widget_set_usize (label47, 32, 16);
  gtk_label_set_justify (GTK_LABEL (label47), GTK_JUSTIFY_LEFT);

  label46 = gtk_label_new ("Gyear/h");
  gtk_widget_set_name (label46, "label46");
  gtk_widget_show (label46);
  gtk_fixed_put (GTK_FIXED (fixed17), label46, 320, 104);
  gtk_widget_set_usize (label46, 38, 16);
  gtk_label_set_justify (GTK_LABEL (label46), GTK_JUSTIFY_LEFT);

  label39 = gtk_label_new ("Lambda vs Omega");
  gtk_widget_set_name (label39, "label39");
  gtk_widget_show (label39);
  gtk_frame_set_label_widget (GTK_FRAME (frame12), label39);
  gtk_label_set_justify (GTK_LABEL (label39), GTK_JUSTIFY_LEFT);

  Lambda_vs_Omega_curve = gtk_drawing_area_new ();
  gtk_widget_set_name (Lambda_vs_Omega_curve, "Lambda_vs_Omega_curve");
  gtk_widget_show (Lambda_vs_Omega_curve);
  gtk_box_pack_start (GTK_BOX (vbox7), Lambda_vs_Omega_curve, TRUE, TRUE, 0);
  gtk_widget_set_usize (Lambda_vs_Omega_curve, 400, 200);

  Close_Lambda_vs_Omega = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Lambda_vs_Omega, "Close_Lambda_vs_Omega");
  gtk_widget_show (Close_Lambda_vs_Omega);
  gtk_box_pack_start (GTK_BOX (vbox7), Close_Lambda_vs_Omega, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Lambda_vs_Omega), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Lambda_vs_Omega_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Lambda_vs_Omega_curve), "expose_event",
                      G_CALLBACK (on_Lambda_vs_Omega_curve_redraw),
                      NULL);

  gtk_signal_connect (GTK_OBJECT (spinbutton41), "value-changed",
                      G_CALLBACK (on_change_universe_age),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (spinbutton42), "value-changed",
                      G_CALLBACK (on_change_delta_universe_age),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (scale_factor), "value-changed",
                      G_CALLBACK (on_scale_factor_change),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Z_decoupling), "value-changed",
                      G_CALLBACK (on_Z_decoupling_change),
                      NULL);

  gtk_signal_connect (GTK_OBJECT (Lambda_vs_Omega_curve), "button_press_event",
                      G_CALLBACK (on_Lambda_vs_Omega_curve_button_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (graphC0_color), "button_press_event",
                      G_CALLBACK (on_graphC0_color_button_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (graphC2_color), "button_press_event",
                      G_CALLBACK (on_graphC2_color_button_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (graphC3_color), "button_press_event",
                      G_CALLBACK (on_graphC3_color_button_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (graphC4_color), "button_press_event",
                      G_CALLBACK (on_graphC4_color_button_press_event),
                      NULL);

  gtk_widget_set_events (Lambda_vs_Omega_curve, gtk_widget_get_events (Lambda_vs_Omega_curve)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Lambda_vs_Omega, Lambda_vs_Omega, "Lambda_vs_Omega");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, vbox7, "vbox7");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, frame12, "frame12");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, fixed17, "fixed17");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, spinbutton41, "spinbutton41");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, spinbutton42, "spinbutton42");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, entry1, "entry1");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label40, "label40");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label41, "label41");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label45, "label45");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label44, "label44");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label43, "label43");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label42, "label42");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label47, "label47");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label46, "label46");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, label39, "label39");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, Lambda_vs_Omega_curve, "Lambda_vs_Omega_curve");
  GLADE_HOOKUP_OBJECT (Lambda_vs_Omega, Close_Lambda_vs_Omega, "Close_Lambda_vs_Omega");

  return Lambda_vs_Omega;
}

GtkWidget*
create_R_t_ (void)
{
  GtkWidget *R_t_;
  GtkWidget *vbox8;
  GtkWidget *frame13;
  GtkWidget *fixed18;
  GtkWidget *entry2;
  GtkWidget *label50;
  GtkWidget *label49;
  GtkWidget *label48;
  GtkWidget *Close_R_t_;

  R_t_ = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (R_t_, "R_t_");
  gtk_window_set_title (GTK_WINDOW (R_t_), "a(t)");

  vbox8 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox8, "vbox8");
  gtk_widget_show (vbox8);
  gtk_container_add (GTK_CONTAINER (R_t_), vbox8);

  frame13 = gtk_frame_new (NULL);
  gtk_widget_set_name (frame13, "frame13");
  gtk_widget_show (frame13);
  gtk_box_pack_start (GTK_BOX (vbox8), frame13, TRUE, TRUE, 0);
  gtk_widget_set_usize (frame13, -2, 20);

  fixed18 = gtk_fixed_new ();
  gtk_widget_set_name (fixed18, "fixed18");
  gtk_widget_show (fixed18);
  gtk_container_add (GTK_CONTAINER (frame13), fixed18);
  gtk_widget_set_usize (fixed18, -2, 0);

  entry2 = gtk_entry_new ();
  gtk_widget_set_name (entry2, "entry2");
  gtk_widget_show (entry2);
  gtk_fixed_put (GTK_FIXED (fixed18), entry2, 128, 8);
  gtk_widget_set_usize (entry2, 158, 20);

  label50 = gtk_label_new ("Gyear/h");
  gtk_widget_set_name (label50, "label50");
  gtk_widget_show (label50);
  gtk_fixed_put (GTK_FIXED (fixed18), label50, 288, 8);
  gtk_widget_set_usize (label50, 46, 16);
  gtk_label_set_justify (GTK_LABEL (label50), GTK_JUSTIFY_LEFT);

  label49 = gtk_label_new ("Universe Computed Age");
  gtk_widget_set_name (label49, "label49");
  gtk_widget_show (label49);
  gtk_fixed_put (GTK_FIXED (fixed18), label49, 8, 8);
  gtk_widget_set_usize (label49, 118, 16);
  gtk_label_set_justify (GTK_LABEL (label49), GTK_JUSTIFY_LEFT);

  label48 = gtk_label_new ("label48");
  gtk_widget_set_name (label48, "label48");
  gtk_widget_show (label48);
  gtk_frame_set_label_widget (GTK_FRAME (frame13), label48);
  gtk_label_set_justify (GTK_LABEL (label48), GTK_JUSTIFY_LEFT);

  R_t_curve = gtk_drawing_area_new ();
  gtk_widget_set_name (R_t_curve, "R_t_curve");
  gtk_widget_show (R_t_curve);
  gtk_box_pack_start (GTK_BOX (vbox8), R_t_curve, TRUE, TRUE, 0);
  gtk_widget_set_usize (R_t_curve, 400, 200);

  Close_R_t_ = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_R_t_, "Close_R_t_");
  gtk_widget_show (Close_R_t_);
  gtk_box_pack_start (GTK_BOX (vbox8), Close_R_t_, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_R_t_), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_R_t__clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (R_t_curve), "expose_event",
                      G_CALLBACK (on_plot_r_t_1_redraw),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (R_t_, R_t_, "R_t_");
  GLADE_HOOKUP_OBJECT (R_t_, vbox8, "vbox8");
  GLADE_HOOKUP_OBJECT (R_t_, frame13, "frame13");
  GLADE_HOOKUP_OBJECT (R_t_, fixed18, "fixed18");
  GLADE_HOOKUP_OBJECT (R_t_, entry2, "entry2");
  GLADE_HOOKUP_OBJECT (R_t_, label50, "label50");
  GLADE_HOOKUP_OBJECT (R_t_, label49, "label49");
  GLADE_HOOKUP_OBJECT (R_t_, label48, "label48");
  GLADE_HOOKUP_OBJECT (R_t_, R_t_curve, "R_t_curve");
  GLADE_HOOKUP_OBJECT (R_t_, Close_R_t_, "Close_R_t_");

  return R_t_;
}

GtkWidget*
create_Integrand (void)
{
  GtkWidget *Integrand;
  GtkWidget *vbox9;
  GtkWidget *Close_integrand;

  Integrand = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Integrand, "Integrand");
  gtk_window_set_title (GTK_WINDOW (Integrand), "Integrand");

  vbox9 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox9, "vbox9");
  gtk_widget_show (vbox9);
  gtk_container_add (GTK_CONTAINER (Integrand), vbox9);

  drawingarea3 = gtk_drawing_area_new ();
  gtk_widget_set_name (drawingarea3, "drawingarea3");
  gtk_widget_show (drawingarea3);
  gtk_box_pack_start (GTK_BOX (vbox9), drawingarea3, TRUE, TRUE, 0);
  gtk_widget_set_usize (drawingarea3, 400, 200);

  Close_integrand = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_integrand, "Close_integrand");
  gtk_widget_show (Close_integrand);
  gtk_box_pack_start (GTK_BOX (vbox9), Close_integrand, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_integrand), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_integrand_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (drawingarea3), "expose_event",
                      G_CALLBACK (on_item6_redraw),
                      NULL);
		      
  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Integrand, Integrand, "Integrand");
  GLADE_HOOKUP_OBJECT (Integrand, vbox9, "vbox9");
  GLADE_HOOKUP_OBJECT (Integrand, drawingarea3, "drawingarea3");
  GLADE_HOOKUP_OBJECT (Integrand, Close_integrand, "Close_integrand");

  return Integrand;
}

GtkWidget*
create_Tau_vs_Redshift (void)
{
  GtkWidget *Tau_vs_Redshift;
  GtkWidget *vbox10;
  GtkWidget *drawingarea4;
  GtkWidget *Close_Tau_vs_Redshift;

  Tau_vs_Redshift = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Tau_vs_Redshift, "Tau_vs_Redshift");
  gtk_window_set_title (GTK_WINDOW (Tau_vs_Redshift), "Comobile distance vs Redshift");

  vbox10 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox10, "vbox10");
  gtk_widget_show (vbox10);
  gtk_container_add (GTK_CONTAINER (Tau_vs_Redshift), vbox10);

  drawingarea4 = gtk_drawing_area_new ();
  gtk_widget_set_name (drawingarea4, "drawingarea4");
  gtk_widget_show (drawingarea4);
  gtk_box_pack_start (GTK_BOX (vbox10), drawingarea4, FALSE, TRUE, 0);
  gtk_widget_set_usize (drawingarea4, 400, 200);

  Close_Tau_vs_Redshift = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close_Tau_vs_Redshift, "Close_Tau_vs_Redshift");
  gtk_widget_show (Close_Tau_vs_Redshift);
  gtk_box_pack_start (GTK_BOX (vbox10), Close_Tau_vs_Redshift, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (Close_Tau_vs_Redshift), "clicked",
                      GTK_SIGNAL_FUNC (on_Close_Tau_vs_Redshift_clicked),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Tau_vs_Redshift, Tau_vs_Redshift, "Tau_vs_Redshift");
  GLADE_HOOKUP_OBJECT (Tau_vs_Redshift, vbox10, "vbox10");
  GLADE_HOOKUP_OBJECT (Tau_vs_Redshift, drawingarea4, "drawingarea4");
  GLADE_HOOKUP_OBJECT (Tau_vs_Redshift, Close_Tau_vs_Redshift, "Close_Tau_vs_Redshift");

  return Tau_vs_Redshift;
}

GtkWidget*
create_edge_1 (void)
{
  GtkWidget *edge1;
  GtkWidget *vbox13;
  GtkWidget *Close;

  edge1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (edge1, "edge1");
  gtk_window_set_title (GTK_WINDOW (edge1), "Edge vue 1");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (edge1), vbox13);

  edge_vue_1 = gtk_drawing_area_new ();
  gtk_widget_set_name (edge_vue_1, "edge_vue_1");
  gtk_widget_show (edge_vue_1);
  gtk_box_pack_start (GTK_BOX (vbox13), edge_vue_1, TRUE, TRUE, 0);
  gtk_widget_set_size_request (edge_vue_1, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) edge_vue_1, "button_press_event",
                    G_CALLBACK (on_edge_vue_1_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) edge_vue_1, "button_release_event",
                    G_CALLBACK (on_edge_vue_1_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_edge_1_clicked),
                    NULL);

  g_signal_connect ((gpointer) edge_vue_1, "expose_event",
                    G_CALLBACK (on_edge_view_4_reactivate),
                    NULL);

  gtk_widget_set_events (edge_vue_1, gtk_widget_get_events (edge_vue_1)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (edge1, edge1, "edge1");
  GLADE_HOOKUP_OBJECT (edge1, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (edge1, edge_vue_1, "edge_vue_1");
  GLADE_HOOKUP_OBJECT (edge1, Close, "Close");

  return edge1;
}


GtkWidget*
create_edge_2 (void)
{
  GtkWidget *edge2;
  GtkWidget *vbox13;
  GtkWidget *Close;

  edge2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (edge2, "edge1");
  gtk_window_set_title (GTK_WINDOW (edge2), "Edge vue 2");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (edge2), vbox13);

  edge_vue_2 = gtk_drawing_area_new ();
  gtk_widget_set_name (edge_vue_2, "edge_vue_2");
  gtk_widget_show (edge_vue_2);
  gtk_box_pack_start (GTK_BOX (vbox13), edge_vue_2, TRUE, TRUE, 0);
  gtk_widget_set_size_request (edge_vue_2, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) edge_vue_2, "expose_event",
                    G_CALLBACK (on_edge_view_5_reactivate),
                    NULL);
  g_signal_connect ((gpointer) edge_vue_2, "button_press_event",
                    G_CALLBACK (on_edge_vue_2_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) edge_vue_2, "button_release_event",
                    G_CALLBACK (on_edge_vue_2_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_edge_2_clicked),
                    NULL);

  gtk_widget_set_events (edge_vue_2, gtk_widget_get_events (edge_vue_2)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (edge2, edge2, "edge2");
  GLADE_HOOKUP_OBJECT (edge2, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (edge2, edge_vue_2, "edge_vue_2");
  GLADE_HOOKUP_OBJECT (edge2, Close, "Close");

  return edge2;
}

GtkWidget*
create_edge_3 (void)
{
  GtkWidget *edge3;
  GtkWidget *vbox13;
  GtkWidget *Close;

  edge3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (edge3, "edge3");
  gtk_window_set_title (GTK_WINDOW (edge3), "Edge vue 3");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (edge3), vbox13);

  edge_vue_3 = gtk_drawing_area_new ();
  gtk_widget_set_name (edge_vue_3, "edge_vue_3");
  gtk_widget_show (edge_vue_3);
  gtk_box_pack_start (GTK_BOX (vbox13), edge_vue_3, TRUE, TRUE, 0);
  gtk_widget_set_size_request (edge_vue_3, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) edge_vue_3, "expose_event",
                    G_CALLBACK (on_edge_view_6_reactivate),
                    NULL);
  g_signal_connect ((gpointer) edge_vue_3, "button_press_event",
                    G_CALLBACK (on_edge_vue_3_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) edge_vue_3, "button_release_event",
                    G_CALLBACK (on_edge_vue_3_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_edge_3_clicked),
                    NULL);

  gtk_widget_set_events (edge_vue_3, gtk_widget_get_events (edge_vue_3)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (edge3, edge3, "edge3");
  GLADE_HOOKUP_OBJECT (edge3, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (edge3, edge_vue_2, "edge_vue_3");
  GLADE_HOOKUP_OBJECT (edge3, Close, "Close");

  return edge3;
}


GtkWidget*
create_front_1 (void)
{
  GtkWidget *front1;
  GtkWidget *vbox13;
  GtkWidget *Close;

  front1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (front1, "front1");
  gtk_window_set_title (GTK_WINDOW (front1), "front vue 1");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (front1), vbox13);

  front_vue_1 = gtk_drawing_area_new ();
  gtk_widget_set_name (front_vue_1, "front_vue_1");
  gtk_widget_show (front_vue_1);
  gtk_box_pack_start (GTK_BOX (vbox13), front_vue_1, TRUE, TRUE, 0);
  gtk_widget_set_size_request (front_vue_1, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) front_vue_1, "expose_event",
                    G_CALLBACK (on_front_view_4_reactivate),
                    NULL);
  g_signal_connect ((gpointer) front_vue_1, "button_press_event",
                    G_CALLBACK (on_front_vue_1_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) front_vue_1, "button_release_event",
                    G_CALLBACK (on_front_vue_1_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_front_1_clicked),
                    NULL);

  gtk_widget_set_events (front_vue_1, gtk_widget_get_events (front_vue_1)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (front1, front1, "front1");
  GLADE_HOOKUP_OBJECT (front1, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (front1, front_vue_1, "front_vue_1");
  GLADE_HOOKUP_OBJECT (front1, Close, "Close");

  return front1;
}


GtkWidget*
create_front_2 (void)
{
  GtkWidget *front2;
  GtkWidget *vbox13;
  GtkWidget *Close;

  front2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (front2, "front1");
  gtk_window_set_title (GTK_WINDOW (front2), "front vue 2");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (front2), vbox13);

  front_vue_2 = gtk_drawing_area_new ();
  gtk_widget_set_name (front_vue_2, "front_vue_2");
  gtk_widget_show (front_vue_2);
  gtk_box_pack_start (GTK_BOX (vbox13), front_vue_2, TRUE, TRUE, 0);
  gtk_widget_set_size_request (front_vue_2, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) front_vue_2, "expose_event",
                    G_CALLBACK (on_front_view_5_reactivate),
                    NULL);
  g_signal_connect ((gpointer) front_vue_2, "button_press_event",
                    G_CALLBACK (on_front_vue_2_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) front_vue_2, "button_release_event",
                    G_CALLBACK (on_front_vue_2_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_front_2_clicked),
                    NULL);

  gtk_widget_set_events (front_vue_2, gtk_widget_get_events (front_vue_2)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (front2, front2, "front2");
  GLADE_HOOKUP_OBJECT (front2, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (front2, front_vue_2, "front_vue_2");
  GLADE_HOOKUP_OBJECT (front2, Close, "Close");

  return front2;
}

GtkWidget*
create_front_3 (void)
{
  GtkWidget *front3;
  GtkWidget *vbox13;
  GtkWidget *Close;

  front3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (front3, "front3");
  gtk_window_set_title (GTK_WINDOW (front3), "front vue 3");

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox13, "vbox13");
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (front3), vbox13);

  front_vue_3 = gtk_drawing_area_new ();
  gtk_widget_set_name (front_vue_3, "front_vue_3");
  gtk_widget_show (front_vue_3);
  gtk_box_pack_start (GTK_BOX (vbox13), front_vue_3, TRUE, TRUE, 0);
  gtk_widget_set_size_request (front_vue_3, 512, 512);

  Close = gtk_button_new_with_mnemonic ("Close");
  gtk_widget_set_name (Close, "Close");
  gtk_widget_show (Close);
  gtk_box_pack_start (GTK_BOX (vbox13), Close, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) front_vue_3, "expose_event",
                    G_CALLBACK (on_front_view_6_reactivate),
                    NULL);
  g_signal_connect ((gpointer) front_vue_3, "button_press_event",
                    G_CALLBACK (on_front_vue_3_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) front_vue_3, "button_release_event",
                    G_CALLBACK (on_front_vue_3_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) Close, "clicked",
                    G_CALLBACK (on_Close_front_3_clicked),
                    NULL);

  gtk_widget_set_events (front_vue_3, gtk_widget_get_events (front_vue_3)
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_BUTTON_RELEASE_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (front3, front3, "front3");
  GLADE_HOOKUP_OBJECT (front3, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (front3, front_vue_2, "front_vue_3");
  GLADE_HOOKUP_OBJECT (front3, Close, "Close");

  return front3;
}

/*
GtkWidget*
create_Message (char* message)
{
  GtkWidget *Message;
  GtkWidget *texte;

  Message = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Message, "Message");
  gtk_window_set_title (GTK_WINDOW (Message), "Message");

  texte = gtk_label_new (message);
  gtk_widget_set_name (texte, "texte");
  gtk_widget_show (texte);
  gtk_container_add (GTK_CONTAINER (Message), texte);

  fermer = gtk_button_new_with_mnemonic ("fermer");
  gtk_widget_set_name (fermer, "fermer");
  gtk_widget_show (fermer);
  gtk_fixed_put (GTK_FIXED (fixed19), fermer, 280, 240);
  gtk_widget_set_size_request (fermer, 64, 32);

  GLADE_HOOKUP_OBJECT_NO_REF (Message, Message, "Message");
  GLADE_HOOKUP_OBJECT (Message, texte, "texte");

  return Message;
}
*/



GtkWidget*
create_Message (char* message)
{
  GtkWidget* Message;
  GtkWidget *vbox11;
  GtkWidget *texte;
  GtkWidget *fermer;

  Message = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Message, "Message");
  gtk_window_set_title (GTK_WINDOW (Message), "Message");

  vbox11 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox11, "vbox11");
  gtk_widget_show (vbox11);
  gtk_container_add (GTK_CONTAINER (Message), vbox11);

  texte = gtk_label_new (message);
  gtk_widget_set_name (texte, "texte");
  gtk_widget_show (texte);
  gtk_box_pack_start (GTK_BOX (vbox11), texte, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (texte), GTK_JUSTIFY_LEFT);

  fermer = gtk_button_new_with_mnemonic ("fermer");
  gtk_widget_set_name (fermer, "fermer");
  gtk_widget_show (fermer);
  gtk_box_pack_start (GTK_BOX (vbox11), fermer, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) fermer, "clicked",
                    G_CALLBACK (on_fermer_message_activate),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Message, Message, "Message");
  GLADE_HOOKUP_OBJECT (Message, vbox11, "vbox11");
  GLADE_HOOKUP_OBJECT (Message, texte, "texte");
  GLADE_HOOKUP_OBJECT (Message, fermer, "fermer");

  return Message;
}

char* current_msg;

void alerte(char* message)
{
	gtk_text_buffer_insert_at_cursor(text_buffer,message,strlen(message));
	gtk_text_view_place_cursor_onscreen((GtkTextView*) textview1);
/*
	if(message_displayed==0 || (message_displayed>0 && strcmp(message, current_msg)) )
	{
		message_displayed++;
		free(current_msg);
		current_msg = (char*)malloc(strlen(message)+1);
		strcpy(current_msg, message);
		message_window[message_displayed-1] = create_Message(message);
		gtk_widget_show(message_window[message_displayed-1]);
	}
*/
}

GtkWidget*
create_Color_selector (void)
{
  GtkWidget *Color_selector;
  GtkWidget *fixed19;
  GtkWidget *Annuler;
  GtkWidget *Choisir_couleur;
  GtkWidget *colorselection1;

  Color_selector = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (Color_selector, "Color_selector");
  gtk_window_set_title (GTK_WINDOW (Color_selector), "Color Selector");
  gtk_window_set_resizable (GTK_WINDOW (Color_selector), FALSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (Color_selector), TRUE);

  fixed19 = gtk_fixed_new ();
  gtk_widget_set_name (fixed19, "fixed19");
  gtk_widget_show (fixed19);
  gtk_container_add (GTK_CONTAINER (Color_selector), fixed19);

  Annuler = gtk_button_new_with_mnemonic ("Annuler");
  gtk_widget_set_name (Annuler, "Annuler");
  gtk_widget_show (Annuler);
  gtk_fixed_put (GTK_FIXED (fixed19), Annuler, 280, 240);
  gtk_widget_set_size_request (Annuler, 64, 32);

  Choisir_couleur = gtk_button_new_with_mnemonic ("Valider la couleur");
  gtk_widget_set_name (Choisir_couleur, "Choisir_couleur");
  gtk_widget_show (Choisir_couleur);
  gtk_fixed_put (GTK_FIXED (fixed19), Choisir_couleur, 352, 240);
  gtk_widget_set_size_request (Choisir_couleur, 128, 32);

  colorselection1 = gtk_color_selection_new ();
  gtk_widget_set_name (colorselection1, "colorselection1");
  gtk_widget_show (colorselection1);
  gtk_fixed_put (GTK_FIXED (fixed19), colorselection1, 0, 0);
  gtk_widget_set_size_request (colorselection1, 488, 232);
  gtk_color_selection_set_has_opacity_control (GTK_COLOR_SELECTION (colorselection1), TRUE);
  gtk_color_selection_set_has_palette (GTK_COLOR_SELECTION (colorselection1), TRUE);

  g_signal_connect ((gpointer) Annuler, "activate",
                    G_CALLBACK (on_Annuler_activate),
                    NULL);
  g_signal_connect ((gpointer) Choisir_couleur, "activate",
                    G_CALLBACK (on_Choisir_couleur_activate),
                    NULL);
  g_signal_connect ((gpointer) colorselection1, "color_changed",
                    G_CALLBACK (on_colorselection1_color_changed),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (Color_selector, Color_selector, "Color_selector");
  GLADE_HOOKUP_OBJECT (Color_selector, fixed19, "fixed19");
  GLADE_HOOKUP_OBJECT (Color_selector, Annuler, "Annuler");
  GLADE_HOOKUP_OBJECT (Color_selector, Choisir_couleur, "Choisir_couleur");
  GLADE_HOOKUP_OBJECT (Color_selector, colorselection1, "colorselection1");

  return Color_selector;
}


GtkWidget*
create_format_specifior (void)
{
  GtkWidget *format_specifior;
  GtkWidget *vbox12;
  GtkWidget *optionmenu1;
  GtkWidget *menu15;
  GtkWidget *menuitem3;
  GtkWidget *menuitem4;
  GtkWidget *menuitem5;
  GtkWidget *fixed21;
  GtkWidget *OK;
  GtkWidget *cancel;

  format_specifior = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (format_specifior, "format_specifior");
  gtk_window_set_title (GTK_WINDOW (format_specifior), "File format ...");

  vbox12 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox12, "vbox12");
  gtk_widget_show (vbox12);
  gtk_container_add (GTK_CONTAINER (format_specifior), vbox12);

  optionmenu1 = gtk_option_menu_new ();
  gtk_widget_set_name (optionmenu1, "optionmenu1");
  gtk_widget_show (optionmenu1);
  gtk_box_pack_start (GTK_BOX (vbox12), optionmenu1, FALSE, FALSE, 0);

  menu15 = gtk_menu_new ();
  gtk_widget_set_name (menu15, "menu15");

  menuitem3 = gtk_menu_item_new_with_mnemonic ("Text space separated format");
  gtk_widget_set_name (menuitem3, "menuitem3");
  gtk_widget_show (menuitem3);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem3);

  menuitem4 = gtk_menu_item_new_with_mnemonic ("xml xls");
  gtk_widget_set_name (menuitem4, "menuitem4");
  gtk_widget_show (menuitem4);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem4);

  menuitem5 = gtk_menu_item_new_with_mnemonic ("Q.S.O Binary format");
  gtk_widget_set_name (menuitem5, "menuitem5");
  gtk_widget_show (menuitem5);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem5);

  gtk_option_menu_set_menu (GTK_OPTION_MENU (optionmenu1), menu15);

  fixed21 = gtk_fixed_new ();
  gtk_widget_set_name (fixed21, "fixed21");
  gtk_widget_show (fixed21);
  gtk_box_pack_start (GTK_BOX (vbox12), fixed21, TRUE, TRUE, 0);
  gtk_widget_set_size_request (fixed21, -2, 48);

  OK = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_set_name (OK, "OK");
  gtk_widget_show (OK);
  gtk_fixed_put (GTK_FIXED (fixed21), OK, 320, 8);
  gtk_widget_set_size_request (OK, 100, 40);

  cancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (cancel, "cancel");
  gtk_widget_show (cancel);
  gtk_fixed_put (GTK_FIXED (fixed21), cancel, 208, 8);
  gtk_widget_set_size_request (cancel, 100, 40);

  g_signal_connect ((gpointer) menuitem3, "activate",
                    G_CALLBACK (on_text_space_separated_format1_activate),
                    NULL);
  g_signal_connect ((gpointer) menuitem4, "activate",
                    G_CALLBACK (on_xml_xls1_activate),
                    NULL);
  g_signal_connect ((gpointer) menuitem5, "activate",
                    G_CALLBACK (on_bin_activate),
                    NULL);
  g_signal_connect ((gpointer) cancel, "clicked",
                    G_CALLBACK (on_fermer_format_selection_activate),
                    NULL);
  g_signal_connect ((gpointer) OK, "clicked",
                    G_CALLBACK (on_OK_format_selection_activate),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (format_specifior, format_specifior, "format_specifior");
  GLADE_HOOKUP_OBJECT (format_specifior, vbox12, "vbox12");
  GLADE_HOOKUP_OBJECT (format_specifior, optionmenu1, "optionmenu1");
  GLADE_HOOKUP_OBJECT (format_specifior, menu15, "menu15");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem3, "menuitem3");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem4, "menuitem4");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem5, "menuitem5");
  GLADE_HOOKUP_OBJECT (format_specifior, fixed21, "fixed21");
  GLADE_HOOKUP_OBJECT (format_specifior, OK, "OK");
  GLADE_HOOKUP_OBJECT (format_specifior, cancel, "cancel");

  return format_specifior;
}

GtkWidget*
create_format_specifior_save (void)
{
  GtkWidget *format_specifior;
  GtkWidget *vbox12;
  GtkWidget *optionmenu1;
  GtkWidget *menu15;
  GtkWidget *menuitem3;
  GtkWidget *menuitem4;
  GtkWidget *menuitem5;
  GtkWidget *menuitem6;
  GtkWidget *fixed21;
  GtkWidget *OK;
  GtkWidget *cancel;

  format_specifior = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (format_specifior, "format_specifior");
  gtk_window_set_title (GTK_WINDOW (format_specifior), "File format ...");

  vbox12 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox12, "vbox12");
  gtk_widget_show (vbox12);
  gtk_container_add (GTK_CONTAINER (format_specifior), vbox12);

  optionmenu1 = gtk_option_menu_new ();
  gtk_widget_set_name (optionmenu1, "optionmenu1");
  gtk_widget_show (optionmenu1);
  gtk_box_pack_start (GTK_BOX (vbox12), optionmenu1, FALSE, FALSE, 0);

  menu15 = gtk_menu_new ();
  gtk_widget_set_name (menu15, "menu15");

  menuitem3 = gtk_menu_item_new_with_mnemonic ("Text space separated format");
  gtk_widget_set_name (menuitem3, "menuitem3");
  gtk_widget_show (menuitem3);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem3);

  menuitem4 = gtk_menu_item_new_with_mnemonic ("xml xls");
  gtk_widget_set_name (menuitem4, "menuitem4");
  gtk_widget_show (menuitem4);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem4);

  menuitem5 = gtk_menu_item_new_with_mnemonic ("Q.S.O Binary format");
  gtk_widget_set_name (menuitem5, "menuitem5");
  gtk_widget_show (menuitem5);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem5);

  menuitem6 = gtk_menu_item_new_with_mnemonic ("Postscript");
  gtk_widget_set_name (menuitem6, "menuitem6");
  gtk_widget_show (menuitem6);
  gtk_container_add (GTK_CONTAINER (menu15), menuitem6);

  gtk_option_menu_set_menu (GTK_OPTION_MENU (optionmenu1), menu15);

  fixed21 = gtk_fixed_new ();
  gtk_widget_set_name (fixed21, "fixed21");
  gtk_widget_show (fixed21);
  gtk_box_pack_start (GTK_BOX (vbox12), fixed21, TRUE, TRUE, 0);
  gtk_widget_set_size_request (fixed21, -2, 48);

  OK = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_set_name (OK, "OK");
  gtk_widget_show (OK);
  gtk_fixed_put (GTK_FIXED (fixed21), OK, 320, 8);
  gtk_widget_set_size_request (OK, 100, 40);

  cancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (cancel, "cancel");
  gtk_widget_show (cancel);
  gtk_fixed_put (GTK_FIXED (fixed21), cancel, 208, 8);
  gtk_widget_set_size_request (cancel, 100, 40);

  g_signal_connect ((gpointer) menuitem3, "activate",
                    G_CALLBACK (on_text_space_separated_format1_save_activate),
                    NULL);
  g_signal_connect ((gpointer) menuitem4, "activate",
                    G_CALLBACK (on_xml_xls1_save_activate),
                    NULL);
  g_signal_connect ((gpointer) menuitem5, "activate",
                    G_CALLBACK (on_bin_save_activate),
                    NULL);
  g_signal_connect ((gpointer) menuitem6, "activate",
                    G_CALLBACK (on_ps_save_activate),
                    NULL);
  g_signal_connect ((gpointer) cancel, "clicked",
                    G_CALLBACK (on_fermer_format_save_selection_activate),
                    NULL);
  g_signal_connect ((gpointer) OK, "clicked",
                    G_CALLBACK (on_OK_format_save_selection_activate),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (format_specifior, format_specifior, "format_specifior");
  GLADE_HOOKUP_OBJECT (format_specifior, vbox12, "vbox12");
  GLADE_HOOKUP_OBJECT (format_specifior, optionmenu1, "optionmenu1");
  GLADE_HOOKUP_OBJECT (format_specifior, menu15, "menu15");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem3, "menuitem3");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem4, "menuitem4");
  GLADE_HOOKUP_OBJECT (format_specifior, menuitem5, "menuitem5");
  GLADE_HOOKUP_OBJECT (format_specifior, fixed21, "fixed21");
  GLADE_HOOKUP_OBJECT (format_specifior, OK, "OK");
  GLADE_HOOKUP_OBJECT (format_specifior, cancel, "cancel");

  return format_specifior;
}

GtkWidget*
create_load (void)
{
  GtkWidget *load;
  GtkWidget *image32;

  load = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW (load), GTK_WIN_POS_CENTER);
  gtk_widget_set_name (load, "load");
  gtk_window_set_title (GTK_WINDOW (load), "Loading ...");

  image32 = gtk_image_new_from_file("pixmaps/load.jpg");
  gtk_widget_set_name (image32, "image32");
  gtk_widget_show (image32);
  gtk_container_add (GTK_CONTAINER (load), image32);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (load, load, "load");
  GLADE_HOOKUP_OBJECT (load, image32, "image32");

  return load;
}

