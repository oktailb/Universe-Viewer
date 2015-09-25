#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include <gtk/gtk.h>
#include <stdlib.h>
#include <pthread.h>

void
on_nouveau1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_ouvrir1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_enregistrer1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_enregistrer_sous1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quitter1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_couper1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copier1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_coller1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_supprimer1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_2_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_3_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_3_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_lamba_vs_omega1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Lambda_vs_Omega_curve_redraw		(GtkMenuItem     *menuitem,
                                         gpointer         user_data);

void
on_plot_r_t_1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_plot_r_t_1_redraw                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_item6_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_plot_tau_z_1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_distance1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_isotropic1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_move_steps1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_calculus1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_options1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_4_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_5_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_6_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_4_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_5_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_6_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_4_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_5_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edge_view_6_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_4_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_5_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_front_view_6_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_OK_clicked                          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_About_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Move_Steps_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Calculus_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Isotropic_Distribution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Compute_Distance_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Isotropic_Distrubution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Lambda_vs_Omega_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_R_t__clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_integrand_clicked             (GtkButton       *button,
                                        gpointer         user_data);
					
					void
on_item6_redraw                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Close_Tau_vs_Redshift_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Options_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_Close_Isotropic_Distribution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_vue_button_press_event              (GtkWidget       *widget,
                                        GtkDirectionType  arg1,
                                        gpointer         user_data);

void
on_Close_edge_1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_Close_edge_2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_Close_edge_3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_Close_front_1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_Close_front_2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_Close_front_3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_statusbar1_event
                                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_zoom_low_activate
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_zoom_no_activate
                                        (GtkButton       *button,
                                        gpointer         user_data);


void
on_zoom_up_activate
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_Lambda_vs_Omega_curve_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_Lambda_changed
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_Omega_changed
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_k_changed
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_Alpha_changed
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_Lambda_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_Omega_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_k_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_Alpha_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data);

void
on_spinbutton5_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_spinbutton6_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_spinbutton7_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_change_data_lenght
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_change_zoom_rate
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data);

void init_graph(void);

void
on_change_universe_age
                                        (GtkSpinButton *spinbutton,
					gpointer user_data);

void
 on_change_delta_universe_age
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_scale_factor_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_Z_decoupling_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_Annuler_activate                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_Choisir_couleur_activate            (GtkButton       *button,
                                        gpointer         user_data);

void
on_colorselection1_color_changed       (GtkColorSelection *colorselection,
                                        gpointer         user_data);

gboolean
on_graphC0_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_graphC2_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_graphC3_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_graphC4_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
init_graph(void);

void
on_file_selected             (GtkButton       *button,
                                        gpointer         user_data);

void
on_file_selection_quit             (GtkButton       *button,
                                        gpointer         user_data);

void
on_fermer_message_activate             (GtkButton       *button,
                                        gpointer         user_data);

void
on_text_space_separated_format1_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_xml_xls1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_bin_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
void
on_fermer_format_selection_activate             (GtkButton       *button,
                                        gpointer         user_data);

void
on_OK_format_selection_activate             (GtkButton       *button,
                                        gpointer         user_data);


void
on_lambda_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_omega_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_k_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_alpha_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_ascension_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_declinaison_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_beta_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data);

void
on_button7_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_button8_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
void
on_button13_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_vue_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_file_selected_save             (GtkButton       *button,
                                        gpointer         user_data);

void
on_file_selection_quit_save             (GtkButton       *button,
                                        gpointer         user_data);

void
on_fermer_format_save_selection_activate             (GtkButton       *button,
                                        gpointer         user_data);

void
on_OK_format_save_selection_activate             (GtkButton       *button,
                                        gpointer         user_data);


void
on_text_space_separated_format1_save_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);


void
on_xml_xls1_save_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);


void
on_bin_save_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_ps_save_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_edge_vue_1_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_edge_vue_2_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_edge_vue_3_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_1_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_2_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_3_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_edge_vue_1_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_edge_vue_2_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_edge_vue_3_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_1_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_2_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
gboolean
on_front_vue_3_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_Compute_Isotropic_Distribution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

#endif
