#include "uv.h"
#include <gtk/gtk.h>

extern Environnement	*uv_gtk_env;
extern GladeXML	*uv_main_file;
extern GtkWidget	*uv_main;
extern GladeXML	*uv_view_file;
extern GtkWidget	*uv_view;
extern Vector center;
extern Vector periph;
extern char* cursor[4];
extern int s_coord_c[4];
extern int s_coord_p[4];
extern int s_vue[6];
extern int current_view;
extern double RadiusMax;
extern double OmegaMax;
extern double zoom_vue;
extern double x_step_vue;
extern double y_step_vue;
extern int lambda_c;
extern int omega_c;
extern int k_c;
extern int alpha_c;
extern int vue_is_displayed[6];
extern int vue_is_displayed_on_vue[6];
extern int r_t_displayed;
extern int integrand_displayed;
extern int decalx, decaly;

GtkWidget	*deglade(char *glade_file, char *id);
void		show_view();
void		show_main();
void		on_edge_view_1_draw_expose_event (const gchar *handler_name,
						  GObject *object,
						  const gchar *signal_name,
						  const gchar *signal_data,
						  GObject *connect_object,
						  gboolean after,
						  gpointer user_data);
