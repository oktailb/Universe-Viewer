#include "uv.h"
#include <gtk/gtk.h>
#include <glade/glade.h>

Environnement	*uv_gtk_env;

Vector center;
Vector periph;
char* cursor[4] = {"|","\\","-","/"};
int s_coord_c[4];
int s_coord_p[4];
int s_vue[6];
int current_view;
double zoom_vue=1.0;
double x_step_vue = 0.0;
double y_step_vue = 0.0;
int lambda_c = 1;
int omega_c  = 0;
int k_c      = 0;
int alpha_c  = 0;
int vue_is_displayed[6]={0,0,0,0,0,0};
int vue_is_displayed_on_vue[6]={1,0,0,0,0,0};
int r_t_displayed=0;
int integrand_displayed=0;
int decalx=15, decaly=15;
