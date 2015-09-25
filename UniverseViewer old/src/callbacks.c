#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <math.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <stdio.h>
#include "space.h"
#include "distance.h"
#include "quasar.h"
#include "projection.h"
#include "isotrop.h"
#include "vector.h"

Vector center;
Vector periph;

char* cursor[4] = {"|","\\","-","/"};

int s_coord_c[4];
int s_coord_p[4];
int s_vue[6];

int current_view;
double RadiusMax=2.0;
double OmegaMax=5.0;
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

extern int message_displayed;
extern Friedman friedman;
extern Quasar *quasar;
extern Vector *quasar_pos;
extern Point* graphT;
extern Point the_earth[6];
extern Vector earth;
extern Point *grapheC0g,*grapheC1g,*grapheC2g,*grapheC31g,*grapheC32g,*grapheC4g;
extern double ascension,declination,beta;
extern double zoom_rate;
extern double age_universe;
extern double delta_age_universe;
extern double new_age_universe;
extern double h;
extern double zr;
extern double AGE_CST;
extern gdouble* current_color;
gdouble* tmp_current_color;

int decalx=15, decaly=15;

extern double lambda_step;
extern double omega_step;
extern double k_step;
extern double alpha_step;
extern int ascension_step;
extern int declinaison_step;
extern int beta_step;


extern int data_lenght;
extern int data_lenght_max;
extern int data_size;
extern const gchar *buff;
extern int radians;

GtkWidget* about;
GtkWidget* Tau_vs_Redshift;
GtkWidget* Integrand;
GtkWidget* R_t_;
GtkWidget* Lambda_vs_Omega;
GtkWidget* Compute_Distance;
GtkWidget* Move_Steps;
GtkWidget* Isotropic_Distribution;
GtkWidget* Calculus;
GtkWidget* Options;
GtkWidget* edge_1;
GtkWidget* edge_2;
GtkWidget* edge_3;
GtkWidget* front_1;
GtkWidget* front_2;
GtkWidget* front_3;


void
on_nouveau1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_widget_show (fileselection1 = create_fileselection1 ());
}


void
on_ouvrir1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_widget_show (fileselection1 = create_fileselection1 ());
}


void
on_enregistrer1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_widget_show (fileselection2 = create_fileselection2 ());
}


void
on_enregistrer_sous1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_widget_show (fileselection2 = create_fileselection2 ());
}


void
on_quitter1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_exit(0);
}


void
on_couper1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_copier1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_coller1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_supprimer1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	about = create_about();
	gtk_widget_show (about);
}


void
on_edge_view_1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gint width;
	gint height;

	current_view=0;
	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=1;
	vue_is_displayed[1]=0;
	vue_is_displayed[2]=0;
	vue_is_displayed[3]=0;
	vue_is_displayed[4]=0;
	vue_is_displayed[5]=0;

	quasar_proj[0] =set_quasar_proj (quasar_pos,0);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);

}


void
on_edge_view_2_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gint width;
	gint height;
	current_view=1;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=0;
	vue_is_displayed[1]=1;
	vue_is_displayed[2]=0;
	vue_is_displayed[3]=0;
	vue_is_displayed[4]=0;
	vue_is_displayed[5]=0;

	quasar_proj[1] =set_quasar_proj (quasar_pos,1);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);

}


void
on_edge_view_3_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gint width;
	gint height;

	current_view=2;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=0;
	vue_is_displayed[1]=0;
	vue_is_displayed[2]=1;
	vue_is_displayed[3]=0;
	vue_is_displayed[4]=0;
	vue_is_displayed[5]=0;

	quasar_proj[2] =set_quasar_proj (quasar_pos,2);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);

}


void
on_front_view_1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

	gint width;
	gint height;

	current_view=3;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=0;
	vue_is_displayed[1]=0;
	vue_is_displayed[2]=0;
	vue_is_displayed[3]=1;
	vue_is_displayed[4]=0;
	vue_is_displayed[5]=0;

	quasar_proj[3] =set_quasar_proj (quasar_pos,3);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);


}


void
on_front_view_2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

	gint width;
	gint height;

	current_view=4;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=0;
	vue_is_displayed[1]=0;
	vue_is_displayed[2]=0;
	vue_is_displayed[3]=0;
	vue_is_displayed[4]=1;
	vue_is_displayed[5]=0;

	quasar_proj[4] =set_quasar_proj (quasar_pos,4);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);


}


void
on_front_view_3_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

	gint width;
	gint height;

	current_view=5;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	vue_is_displayed[0]=0;
	vue_is_displayed[1]=0;
	vue_is_displayed[2]=0;
	vue_is_displayed[3]=0;
	vue_is_displayed[4]=0;
	vue_is_displayed[5]=1;

	quasar_proj[5] =set_quasar_proj (quasar_pos,5);
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);


}


void
on_lamba_vs_omega1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	char text[256];
	Lambda_vs_Omega = create_Lambda_vs_Omega ();
	sprintf(text, "%lf", donne_cell());
	buff = g_strdup_printf (text);
	gtk_widget_show(Lambda_vs_Omega);
	gtk_entry_set_text((GtkEntry*)entry1,buff);
}

void
on_Lambda_vs_Omega_curve_redraw		(GtkMenuItem     *menuitem,
                                         gpointer         user_data)
{
	GdkColor* color;
	gint width;
	gint height;
	gint i=0, j=0, nb_cell=0;
	double tmp_omega, tmp_lambda, tmp_k;
	GdkGCValues *vals, *color_vals;
	extern double age_universe,new_age_universe;

	alerte("(Re)Drawing Lambda vs Omega curves ...\n");

	vals = (GdkGCValues*) malloc(sizeof(GdkGCValues));
	color_vals = (GdkGCValues*) malloc(sizeof(GdkGCValues));
	color = (GdkColor*) malloc(sizeof(GdkColor));

	gdk_gc_get_values(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],vals);
	new_age_universe=age_universe;

	gtk_widget_get_size_request(Lambda_vs_Omega_curve,&width,&height);

	tmp_omega = friedman.omega;
	tmp_lambda = friedman.lambda;
	tmp_k = friedman.k;

	for(j=0;j<200;j++)
	{
		for(i=0;i<400;i++)
		{
			gtk_progress_bar_set_fraction((GtkProgressBar *) progressbar1,(j*400+i)/(200*400));
			gtk_widget_show(progressbar1);
			friedman.omega=(i-decaly)*OmegaMax/400;
			friedman.lambda=(j-decalx)*OmegaMax/200;
			friedman.k=friedman.lambda+friedman.omega+friedman.alpha-1;

			if(friedman.omega > 0 && friedman.lambda > 0)
			{
				nb_cell = (int)donne_cell();
				switch(nb_cell)
				{
					case 1:
						color->pixel = 0xFFFFFF;
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);
						gdk_draw_point(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],i,200-j);
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);
						break;
					case 2:
						color->pixel = 0x111111;
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);
						gdk_draw_point(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],i,200-j);
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);
						break;
     case 500:
						color->pixel = 0x000000;
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);
						gdk_draw_point(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],i,200-j);
						gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);

						break;
					default:
						break;
				}
			}
		}
	}

	 friedman.omega = tmp_omega;
	 friedman.lambda = tmp_lambda;
	 friedman.k = tmp_k;
/*
 *	Drawing axes for the curve ...
 */

	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx,0,decalx,height);
	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],0,height-decaly,width,height-decaly);

	/*
	 *	Drawing a cursor to brownse the current universe model
	 */
	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+friedman.lambda*(width-decalx)+decalx/2,height-friedman.omega*(height-decaly)-decaly,decalx+friedman.lambda*(width-decalx)-decalx/2,height-friedman.omega*(height-decaly)-decaly);
	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+friedman.lambda*(width-decalx),height-friedman.omega*(height-decaly)-decaly+decaly/2,decalx+friedman.lambda*(width-decalx),height-friedman.omega*(height-decaly)-decaly-decaly/2);

/*------------------------------------------------------------------------------*/
/*		Give the line k=0 in graph Lambda vs Omega			*/
/*------------------------------------------------------------------------------*/

	color->pixel=0x000000F0;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);

	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx,height-decaly,decalx+grapheC0g[0].x*(width-decalx),height-grapheC0g[0].y*(height-decaly)-decaly);

	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);

  gdk_gc_get_values(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],color_vals);
  color->pixel=0x000000F0;
  gdk_gc_set_foreground(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],color);
  gdk_draw_rectangle(graphC0_color->window,graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],1,0,0,150,150);
  gdk_gc_set_foreground(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],&color_vals->foreground);


/*------------------------------------------------------------------------------*/
/*		Give the line k=0 in graph Lambda vs Omega			*/
/*------------------------------------------------------------------------------*/
	color->pixel=0x000000F0;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);

	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx,height-decaly,decalx+grapheC1g[0].x*(width-decalx),height-grapheC1g[0].y*(height-decaly)-decaly);
	gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+grapheC1g[0].x*(width-decalx),height-grapheC1g[0].y*(height-decaly)-decaly,decalx+grapheC1g[1].x*(width-decalx),height-grapheC1g[1].y*(height-decaly)-decaly);

	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);
/*
gdk_gc_get_values(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],color_vals);
  color->pixel=0x000000F0;
  gdk_gc_set_foreground(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],color);
  gdk_draw_rectangle(graphC0_color->window,graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],1,0,0,150,150);
  gdk_gc_set_foreground(graphC0_color->style->fg_gc[GTK_WIDGET_STATE (graphC0_color)],&color_vals->foreground);
*/
/*--------------------------------------------------------------------------------------*/
/*		Give the value of Lambda made by the equation in test_C2 function	*/
/*			return ( 1.5*sqrt(3*l)*(o*sqrt(k)+a*sqrt(3*l))-(k*k) );		*/
/*--------------------------------------------------------------------------------------*/
	color->pixel=0x00000F00;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);

	for(i=1;i<200;i++)
	{
		gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+grapheC2g[i-1].x*(width-decalx),height-grapheC2g[i-1].y*(height-decaly)-decaly,decalx+grapheC2g[i].x*(width-decalx),height-grapheC2g[i].y*(height-decaly)-decaly);
	}
	gtk_widget_show (label45);

	// GrapheC3
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);

  gdk_gc_get_values(graphC2_color->style->fg_gc[GTK_WIDGET_STATE (graphC2_color)],color_vals);
  color->pixel=0x00000F00;
  gdk_gc_set_foreground(graphC2_color->style->fg_gc[GTK_WIDGET_STATE (graphC2_color)],color);
  gdk_draw_rectangle(graphC2_color->window,graphC2_color->style->fg_gc[GTK_WIDGET_STATE (graphC2_color)],1,0,0,150,150);
  gdk_gc_set_foreground(graphC2_color->style->fg_gc[GTK_WIDGET_STATE (graphC2_color)],&color_vals->foreground);

/*--------------------------------------------------------------------------------------*/
/*		Give the values of Omega et Lambda which made the universe age right	*/
/*--------------------------------------------------------------------------------------*/

	//grapheC3(OmegaMax,new_age_universe+delta_age_universe,graphe);
	color->pixel=0x0000F000;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);

	for(i=1;i<600;i++)
	{
		gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+grapheC31g[i-1].x*(width-decalx),height-grapheC31g[i-1].y*(height-decaly)-decaly,decalx+grapheC31g[i].x*(width-decalx),height-grapheC31g[i].y*(height-decaly)-decaly);
	}

	gtk_widget_show (label44);

	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);

  gdk_gc_get_values(graphC3_color->style->fg_gc[GTK_WIDGET_STATE (graphC3_color)],color_vals);
  color->pixel=0x0000F000;
  gdk_gc_set_foreground(graphC3_color->style->fg_gc[GTK_WIDGET_STATE (graphC3_color)],color);
  gdk_draw_rectangle(graphC3_color->window,graphC3_color->style->fg_gc[GTK_WIDGET_STATE (graphC3_color)],1,0,0,150,150);
  gdk_gc_set_foreground(graphC3_color->style->fg_gc[GTK_WIDGET_STATE (graphC3_color)],&color_vals->foreground);

/*--------------------------------------------------------------------------------------*/
/*		Give the values of Omega et Lambda which made the universe age right	*/
/*--------------------------------------------------------------------------------------*/

	//grapheC3(OmegaMax,new_age_universe-delta_age_universe,graphe);
	color->pixel= 0x0000F000;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);

	for(i=1;i<600;i++)
	{
		gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+grapheC32g[i-1].x*(width-decalx),height-grapheC32g[i-1].y*(height-decaly)-decaly,decalx+grapheC32g[i].x*(width-decalx),height-grapheC32g[i].y*(height-decaly)-decaly);
	}

	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);


/*--------------------------------------------------------------------------------------*/
/*		Give the error made by the researsh made in graph_C4 function,		*/
/*	this function is the pure test procedure to put out causal cell curve		*/
/*--------------------------------------------------------------------------------------*/

	//grapheC4(OmegaMax,graphe);
	color->pixel= 0x00F00000;
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],color);
	for(i=1;i<20;i++)
	{
		gdk_draw_line(Lambda_vs_Omega_curve->window,Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],decalx+grapheC4g[i-1].x*(width-decalx),height-grapheC4g[i-1].y*(height-decaly)-decaly,decalx+grapheC4g[i].x*(width-decalx),height-grapheC4g[i].y*(height-decaly)-decaly);

	}
	gdk_gc_set_foreground(Lambda_vs_Omega_curve->style->fg_gc[GTK_WIDGET_STATE (Lambda_vs_Omega_curve)],&vals->foreground);

  gdk_gc_get_values(graphC4_color->style->fg_gc[GTK_WIDGET_STATE (graphC4_color)],color_vals);
  color->pixel=0x00F00000;
  gdk_gc_set_foreground(graphC4_color->style->fg_gc[GTK_WIDGET_STATE (graphC4_color)],color);
  gdk_draw_rectangle(graphC4_color->window,graphC4_color->style->fg_gc[GTK_WIDGET_STATE (graphC4_color)],1,0,0,150,150);
  gdk_gc_set_foreground(graphC4_color->style->fg_gc[GTK_WIDGET_STATE (graphC4_color)],&color_vals->foreground);
  alerte("Done\n");

}

void
on_plot_r_t_1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	R_t_ = create_R_t_();
	r_t_displayed=1;
	gtk_widget_show(R_t_);
}

void
on_plot_r_t_1_redraw                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GdkColor* color;
	GdkGCValues *vals;
	Point* graphe;
	gint width;
	gint height;
	gint i=0;


	vals = (GdkGCValues*) malloc(sizeof(GdkGCValues));
	color = (GdkColor*) malloc(sizeof(GdkColor));

	gdk_gc_get_values(R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],vals);
	gtk_widget_get_size_request(R_t_curve,&width,&height);

	gdk_draw_line(R_t_curve->window,R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],decalx,0,decalx,height);
	gdk_draw_line(R_t_curve->window,R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],0,height-decaly,width,height-decaly);

	color->pixel= 0x00000000;
	gdk_gc_set_foreground(R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],color);

	graphe = (Point*) malloc(sizeof(Point)*200);
	grapheA1(RadiusMax,graphe);
	for(i=1;i<200;i++)
	{
		gdk_draw_line(R_t_curve->window,R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],decalx+graphe[i-1].x*(width-2*decalx),height-graphe[i-1].y*(height-2*decaly)-decaly,decalx+graphe[i].x*(width-2*decalx),height-graphe[i].y*(height-2*decaly)-decaly);
	}

	gdk_gc_set_foreground(R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],&vals->foreground);
	color->pixel= 0x00F00000;
	gdk_gc_set_foreground(R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],color);

	free(graphe);
	graphe = (Point*) malloc(sizeof(Point)*3);
	grapheA2(RadiusMax,graphe);
	for(i=1;i<3;i++)
	{
		gdk_draw_line(R_t_curve->window,R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],decalx+graphe[i-1].x*(width-decalx),height-graphe[i-1].y*(height-decaly)-decaly,decalx+graphe[i].x*(width-decalx),height-graphe[i].y*(height-decaly)-decaly);
	}
	gdk_gc_set_foreground(R_t_curve->style->fg_gc[GTK_WIDGET_STATE (R_t_curve)],&vals->foreground);
	free(graphe);

	gtk_widget_show_now(R_t_curve);

}

void
on_item6_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Integrand = create_Integrand ();
	integrand_displayed=1;
	gtk_widget_show(Integrand);
}

void
on_item6_redraw                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i;
	Point* graphe;
	GdkColor* color;
	GdkGCValues *vals;
	gint width;
	gint height;
	extern int graphP_lenght;
	vals = (GdkGCValues*) malloc(sizeof(GdkGCValues));
	color = (GdkColor*) malloc(sizeof(GdkColor));

	gdk_gc_get_values(drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],vals);
	gtk_widget_get_size_request(drawingarea3,&width,&height);

	gdk_draw_line(drawingarea3->window,drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],decalx,0,decalx,height);
	gdk_draw_line(drawingarea3->window,drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],0,height-decaly,width,height-decaly);

	color->pixel= 0x00F00000;
	gdk_gc_set_foreground(drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],color);

	graphe = (Point*) malloc(sizeof(Point)*graphP_lenght);
	grapheP(graphe);
	for(i=1;i<graphP_lenght;i++)
	{
		gdk_draw_line(drawingarea3->window,drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],decalx+graphe[i-1].x*(width-decalx),height-graphe[i-1].y*(height-decaly)-decaly,decalx+graphe[i].x*(width-decalx),height-graphe[i].y*(height-decaly)-decaly);
	}
	gdk_gc_set_foreground(drawingarea3->style->fg_gc[GTK_WIDGET_STATE (drawingarea3)],&vals->foreground);
	free(graphe);
}

void
on_plot_tau_z_1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Tau_vs_Redshift = create_Tau_vs_Redshift();
	gtk_widget_show(Tau_vs_Redshift);
}


void
on_distance1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Compute_Distance = create_Compute_Distance();
	gtk_widget_show(Compute_Distance);
}


void
on_isotropic1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Isotropic_Distribution = create_Isotropic_Distribution();
	gtk_widget_show(Isotropic_Distribution);
}


void
on_move_steps1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Move_Steps = create_Move_Steps();
	gtk_widget_show(Move_Steps);
}


void
on_calculus1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Calculus = create_Calculus();
	gtk_widget_show(Calculus);
}


void
on_options1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	Options = create_Options();
	gtk_widget_show(Options);
}


void
on_edge_view_4_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[0])
	{
		vue_is_displayed[0] = 1;
		quasar_proj[0] =set_quasar_proj (quasar_pos,0);
		edge_1 = create_edge_1 ();
		gtk_widget_show(edge_1);
	}
}


void
on_edge_view_5_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[1])
	{
		vue_is_displayed[1] = 1;
		quasar_proj[1] =set_quasar_proj (quasar_pos,1);
		edge_2 = create_edge_2 ();
		gtk_widget_show(edge_2);
	}
}


void
on_edge_view_6_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[2])
	{
		vue_is_displayed[2] = 1;
		quasar_proj[2] =set_quasar_proj (quasar_pos,2);
		edge_3 = create_edge_3 ();
		gtk_widget_show(edge_3);
	}
}


void
on_front_view_4_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[3])
	{
		vue_is_displayed[3] = 1;
		quasar_proj[3] =set_quasar_proj (quasar_pos,3);
		front_1 = create_front_1 ();
		gtk_widget_show(front_1);
	}
}


void
on_front_view_5_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[4])
	{
		vue_is_displayed[4] = 1;
		quasar_proj[4] =set_quasar_proj (quasar_pos,4);
		front_2 = create_front_2 ();
		gtk_widget_show(front_2);
	}
}


void
on_front_view_6_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(!vue_is_displayed[5])
	{
		vue_is_displayed[5] = 1;
		quasar_proj[5] =set_quasar_proj (quasar_pos,5);
		front_3 = create_front_3 ();
		gtk_widget_show(front_3);
	}
}

void
on_edge_view_4_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(edge_vue_1,&width,&height);
	width = width/2;
	height = height/2;

	if(s_coord_c[0] == 1 && s_coord_c[3] == 1 && s_coord_p[0] == 1 && s_coord_p[3] == 1)
	{

		gdk_draw_rectangle(edge_vue_1->window,edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)],FALSE,(center.x+1)*256,(center.t+1)*256,(ABS(periph.x-center.x))*256,(ABS(periph.t-center.t))*256);
	}
	else
	{
		if(s_coord_c[0] == 1 && s_coord_p[0])
		{
			gdk_draw_line(edge_vue_1->window,edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)],(center.x+1)*256,0,(center.x+1)*256,512);
			gdk_draw_line(edge_vue_1->window,edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)],(periph.x+1)*256,0,(periph.x+1)*256,512);
		}
		if(s_coord_c[3] == 1 && s_coord_p[3])
		{
			gdk_draw_line(edge_vue_1->window,edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)],0,(center.t+1)*256,512,(center.t+1)*256);
			gdk_draw_line(edge_vue_1->window,edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)],0,(periph.t+1)*256,512,(periph.t+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(edge_vue_1->window, edge_vue_1->style->fg_gc[GTK_WIDGET_STATE (edge_vue_1)], quasar_proj[0][i].x*width+width, height-quasar_proj[0][i].y*height);
	}


}


void
on_edge_view_5_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(edge_vue_2,&width,&height);
	width = width/2;
	height = height/2;

	if(s_coord_c[1] == 1 && s_coord_c[3] == 1 && s_coord_p[1] == 1 && s_coord_p[3] == 1)
	{
		gdk_draw_rectangle(edge_vue_2->window,edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)],FALSE,(center.y+1)*256,(center.t+1)*256,(ABS(periph.y-center.y))*256,(ABS(periph.t-center.t))*256);
	}
	else
	{
		if(s_coord_c[1] == 1 && s_coord_p[1])
		{
			gdk_draw_line(edge_vue_2->window,edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)],(center.y+1)*256,0,(center.y+1)*256,512);
			gdk_draw_line(edge_vue_2->window,edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)],(periph.y+1)*256,0,(periph.y+1)*256,512);
		}
		if(s_coord_c[3] == 1 && s_coord_p[3])
		{
			gdk_draw_line(edge_vue_2->window,edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)],0,(center.t+1)*256,512,(center.t+1)*256);
			gdk_draw_line(edge_vue_2->window,edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)],0,(periph.t+1)*256,512,(periph.t+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(edge_vue_2->window, edge_vue_2->style->fg_gc[GTK_WIDGET_STATE (edge_vue_2)], quasar_proj[1][i].x*width+width, height-quasar_proj[1][i].y*height);
	}

}


void
on_edge_view_6_reactivate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(edge_vue_3,&width,&height);
	width = width/2;
	height = height/2;


	if(s_coord_c[2] == 1 && s_coord_c[3] == 1 && s_coord_p[2] == 1 && s_coord_p[3] == 1)
	{
		gdk_draw_rectangle(edge_vue_3->window,edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)],FALSE,(center.z+1)*256,(center.t+1)*256,(ABS(periph.z-center.z))*256,(ABS(periph.t-center.t))*256);
	}
	else
	{
		if(s_coord_c[2] == 1 && s_coord_p[2])
		{
			gdk_draw_line(edge_vue_3->window,edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)],(center.z+1)*256,0,(center.z+1)*256,512);
			gdk_draw_line(edge_vue_3->window,edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)],(periph.z+1)*256,0,(periph.z+1)*256,512);
		}
		if(s_coord_c[3] == 1 && s_coord_p[3])
		{
			gdk_draw_line(edge_vue_3->window,edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)],0,(center.t+1)*256,512,(center.t+1)*256);
			gdk_draw_line(edge_vue_3->window,edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)],0,(periph.t+1)*256,512,(periph.t+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(edge_vue_3->window, edge_vue_3->style->fg_gc[GTK_WIDGET_STATE (edge_vue_3)], quasar_proj[2][i].x*width+width, height-quasar_proj[2][i].y*height);
	}

}


void
on_front_view_4_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(front_vue_1,&width,&height);
	width = width/2;
	height = height/2;

	if(s_coord_c[0] == 1 && s_coord_c[2] == 1 && s_coord_p[0] == 1 && s_coord_p[2] == 1)
	{
		gdk_draw_rectangle(front_vue_1->window,front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)],FALSE,(center.x+1)*256,(center.z+1)*256,(ABS(periph.x-center.x))*256,(ABS(periph.z-center.z))*256);
	}
	else
	{
		if(s_coord_c[0] == 1 && s_coord_p[0])
		{
			gdk_draw_line(front_vue_1->window,front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)],(center.z+1)*256,0,(center.z+1)*256,512);
			gdk_draw_line(front_vue_1->window,front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)],(periph.z+1)*256,0,(periph.z+1)*256,512);
		}
		if(s_coord_c[2] == 1 && s_coord_p[2])
		{
			gdk_draw_line(front_vue_1->window,front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)],0,(center.x+1)*256,512,(center.x+1)*256);
			gdk_draw_line(front_vue_1->window,front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)],0,(periph.x+1)*256,512,(periph.x+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(front_vue_1->window, front_vue_1->style->fg_gc[GTK_WIDGET_STATE (front_vue_1)], quasar_proj[3][i].x*width+width, height-quasar_proj[3][i].y*height);
	}

}


void
on_front_view_5_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(front_vue_2,&width,&height);
	width = width/2;
	height = height/2;

	if(s_coord_c[0] == 1 && s_coord_c[1] == 1 && s_coord_p[0] == 1 && s_coord_p[1] == 1)
	{
		gdk_draw_rectangle(front_vue_2->window,front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)],FALSE,(center.x+1)*256,(center.y+1)*256,(ABS(periph.x-center.x))*256,(ABS(periph.y-center.y))*256);
	}
	else
	{
		if(s_coord_c[0] == 1 && s_coord_p[0])
		{
			gdk_draw_line(front_vue_2->window,front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)],(center.y+1)*256,0,(center.y+1)*256,512);
			gdk_draw_line(front_vue_2->window,front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)],(periph.y+1)*256,0,(periph.y+1)*256,512);
		}
		if(s_coord_c[1] == 1 && s_coord_p[1])
		{
			gdk_draw_line(front_vue_2->window,front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)],0,(center.x+1)*256,512,(center.x+1)*256);
			gdk_draw_line(front_vue_2->window,front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)],0,(periph.x+1)+256,512,(periph.x+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(front_vue_2->window, front_vue_2->style->fg_gc[GTK_WIDGET_STATE (front_vue_2)], quasar_proj[4][i].x*width+width, height-quasar_proj[4][i].y*height);
	}

}


void
on_front_view_6_reactivate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;

	gtk_widget_get_size_request(front_vue_3,&width,&height);
	width = width/2;
	height = height/2;

	if(s_coord_c[1] == 1 && s_coord_c[2] == 1 && s_coord_p[1] == 1 && s_coord_p[2] == 1)
	{
		gdk_draw_rectangle(front_vue_3->window,front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)],FALSE,(center.y+1)*256,(center.z+1)*256,(ABS(periph.y-center.y))*256,(ABS(periph.z-center.z))*256);
	}
	else
	{
		if(s_coord_c[1] == 1 && s_coord_p[1])
		{
			gdk_draw_line(front_vue_3->window,front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)],(center.z+1)*256,0,(center.z+1)*256,512);
			gdk_draw_line(front_vue_3->window,front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)],(periph.z+1)*256,0,(periph.z+1)*256,512);
		}
		if(s_coord_c[2] == 1 && s_coord_p[2])
		{
			gdk_draw_line(front_vue_3->window,front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)],0,(center.y+1)*256,512,(center.y+1)*256);
			gdk_draw_line(front_vue_3->window,front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)],0,(periph.y+1)*256,512,(periph.y+1)*256);
		}
	}

	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(front_vue_3->window, front_vue_3->style->fg_gc[GTK_WIDGET_STATE (front_vue_3)], quasar_proj[5][i].x*width+width, height-quasar_proj[5][i].y*height);
	}

}

void
on_Close_About_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(about);
}


void
on_Close_Move_Steps_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Move_Steps);
}


void
on_Close_Calculus_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Calculus);
}


void
on_Close_Isotropic_Distribution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Isotropic_Distribution);
}


void
on_Close_Compute_Distance_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Compute_Distance);
}

void
on_Close_Lambda_vs_Omega_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Lambda_vs_Omega);
}


void
on_Close_R_t__clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	r_t_displayed=0;
	gtk_widget_destroy(R_t_);
}


void
on_Close_integrand_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	integrand_displayed=0;
	gtk_widget_destroy(Integrand);
}


void
on_Close_Tau_vs_Redshift_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Tau_vs_Redshift);
}


void
on_Close_Options_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(Options);
}


gboolean
on_vue_button_press_event              (GtkWidget       *widget,
                                        GtkDirectionType  arg1,
                                        gpointer         user_data)
{

/*
double zoom_vue=1.0;
double x_step = 0.0;
double y_step = 0.0;
*/
	int i=0;
	gint width;
	gint height;
	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;
	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(vue->window, vue->style->fg_gc[GTK_WIDGET_STATE (vue)], (x_step_vue+quasar_proj[current_view][i].x)*zoom_vue*width+width, height-(y_step_vue+quasar_proj[current_view][i].y)*zoom_vue*height);
	}

  return FALSE;
}

void
on_Close_edge_1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[0] = 0;

	gtk_widget_destroy(edge_1);
}

void
on_Close_edge_2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[1] = 0;

	gtk_widget_destroy(edge_2);
}

void
on_Close_edge_3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[2] = 0;

	gtk_widget_destroy(edge_3);
}

void
on_Close_front_1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[3] = 0;

	gtk_widget_destroy(front_1);
}

void
on_Close_front_2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[4] = 0;

	gtk_widget_destroy(front_2);
}

void
on_Close_front_3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	vue_is_displayed[5] = 0;

	gtk_widget_destroy(front_3);
}

void
on_zoom_low_activate
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

	int i=0;
	gint width;
	gint height;
	zoom_vue*=zoom_rate;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;
	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(vue->window, vue->style->fg_gc[GTK_WIDGET_STATE (vue)], (x_step_vue+quasar_proj[current_view][i].x)*zoom_vue*width+width, height-(y_step_vue+quasar_proj[current_view][i].y)*zoom_vue*height);
	}

	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	gtk_widget_show_now(vue);

}


void
on_zoom_no_activate
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;
	zoom_vue=1.0;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;
	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(vue->window, vue->style->fg_gc[GTK_WIDGET_STATE (vue)], (x_step_vue+quasar_proj[current_view][i].x)*zoom_vue*width+width, height-(y_step_vue+quasar_proj[current_view][i].y)*zoom_vue*height);
	}
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	gtk_widget_show_now(vue);

}


void
on_zoom_up_activate
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	int i=0;
	gint width;
	gint height;
	zoom_vue/=zoom_rate;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;
	for(i=0;i<data_lenght;i++)
	{
		gdk_draw_point(vue->window, vue->style->fg_gc[GTK_WIDGET_STATE (vue)], (x_step_vue+quasar_proj[current_view][i].x)*zoom_vue*width+width, height-(y_step_vue+quasar_proj[current_view][i].y)*zoom_vue*height);
	}
	gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	gtk_widget_show_now(vue);

}

gboolean
on_Lambda_vs_Omega_curve_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	int x, y, i;
	GdkModifierType state;
	gint width;
	gint height;
	char text[256];

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;


	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state & GDK_BUTTON1_MASK)
	{
		friedman.omega=(x-decalx)*OmegaMax/400;
		friedman.lambda=(200-y-decaly)*OmegaMax/200;

		friedman.k=friedman.lambda+friedman.omega+friedman.alpha-1;

		gtk_spin_button_set_value((GtkSpinButton*)Lambda,friedman.lambda);
		gtk_spin_button_set_value((GtkSpinButton*)Omega,friedman.omega);
		gtk_spin_button_set_value((GtkSpinButton*)k,friedman.k);

		init_abacus ();

		calc_quasar_tau (quasar, graphT);
		calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}

		gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
		if(vue_is_displayed[0]|vue_is_displayed_on_vue[0])	gtk_widget_queue_draw_area(edge_1,0,0,2*width,2*height);
		if(vue_is_displayed[1]|vue_is_displayed_on_vue[1])	gtk_widget_queue_draw_area(edge_2,0,0,2*width,2*height);
		if(vue_is_displayed[2]|vue_is_displayed_on_vue[2])	gtk_widget_queue_draw_area(edge_3,0,0,2*width,2*height);
		if(vue_is_displayed[3]|vue_is_displayed_on_vue[3])	gtk_widget_queue_draw_area(front_1,0,0,2*width,2*height);
		if(vue_is_displayed[4]|vue_is_displayed_on_vue[4])	gtk_widget_queue_draw_area(front_2,0,0,2*width,2*height);
		if(vue_is_displayed[5]|vue_is_displayed_on_vue[5])	gtk_widget_queue_draw_area(front_3,0,0,2*width,2*height);
		if(r_t_displayed)					gtk_widget_queue_draw_area(R_t_curve,0,0,2*width,2*height);
		if(integrand_displayed)					gtk_widget_queue_draw_area(drawingarea3,0,0,2*width,2*height);
		sprintf(text, "%lf", donne_cell());
		buff = g_strdup_printf (text);
		gtk_entry_set_text((GtkEntry*)entry1,buff);

		gtk_widget_show_now(vue);
	}

	return FALSE;
}


void
on_Lambda_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;
	gint width;
	gint height;
	double old;
	double variation;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	old = friedman.lambda;
	friedman.lambda =  gtk_spin_button_get_value(spinbutton);
	variation = friedman.lambda - old;

	friedman.lambda -= (variation*lambda_c);
	friedman.omega  -= (variation*omega_c);
	friedman.k      += (variation*k_c);
	friedman.alpha  -= (variation*alpha_c);

	gtk_spin_button_set_value((GtkSpinButton*)Lambda,friedman.lambda);
	gtk_spin_button_set_value((GtkSpinButton*)Omega,friedman.omega);
	gtk_spin_button_set_value((GtkSpinButton*)k,friedman.k);
	gtk_spin_button_set_value((GtkSpinButton*)Alpha,friedman.alpha);

	if(lambda_c)
	{
		init_abacus ();

		calc_quasar_tau (quasar, graphT);
		calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}

		gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
		gtk_widget_show_now(vue);
	}
}

void
on_Omega_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;
	gint width;
	gint height;
	double old;
	double variation;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	old = friedman.omega;
	friedman.omega =  gtk_spin_button_get_value(spinbutton);
	variation = friedman.omega - old;

	friedman.lambda -= (variation*lambda_c);
	friedman.omega  -= (variation*omega_c);
	friedman.k      += (variation*k_c);
	friedman.alpha  -= (variation*alpha_c);

	gtk_spin_button_set_value((GtkSpinButton*)Lambda,friedman.lambda);
	gtk_spin_button_set_value((GtkSpinButton*)Omega,friedman.omega);
	gtk_spin_button_set_value((GtkSpinButton*)k,friedman.k);
	gtk_spin_button_set_value((GtkSpinButton*)Alpha,friedman.alpha);

	if(omega_c)
	{
		init_abacus ();

		calc_quasar_tau (quasar, graphT);
		calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(r_t_displayed)gtk_widget_queue_draw_area(R_t_curve,0,0,200,400);
		if(integrand_displayed)	gtk_widget_queue_draw_area(drawingarea3,0,0,2*width,2*height);
		gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	}
}

void
on_k_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;
	gint width;
	gint height;
	double old;
	double variation;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	old = friedman.k;
	friedman.k =  gtk_spin_button_get_value(spinbutton);
	variation = -(friedman.k - old);

	friedman.lambda -= (variation*lambda_c);
	friedman.omega  -= (variation*omega_c);
	friedman.k      += (variation*k_c);
	friedman.alpha  -= (variation*alpha_c);

	gtk_spin_button_set_value((GtkSpinButton*)Lambda,friedman.lambda);
	gtk_spin_button_set_value((GtkSpinButton*)Omega,friedman.omega);
	gtk_spin_button_set_value((GtkSpinButton*)k,friedman.k);
	gtk_spin_button_set_value((GtkSpinButton*)Alpha,friedman.alpha);


	if(k_c)
	{
		init_abacus ();

		calc_quasar_tau (quasar, graphT);
		calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(r_t_displayed)gtk_widget_queue_draw_area(R_t_curve,0,0,200,400);
		if(integrand_displayed)	gtk_widget_queue_draw_area(drawingarea3,0,0,2*width,2*height);

		gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	}
}

void
on_Alpha_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;
	gint width;
	gint height;
	double old;
	double variation;

	gtk_widget_get_size_request(vue,&width,&height);
	width = width/2;
	height = height/2;

	old = friedman.alpha;
	friedman.alpha =  gtk_spin_button_get_value(spinbutton);
	variation = friedman.alpha - old;

	friedman.lambda -= (variation*lambda_c);
	friedman.omega  -= (variation*omega_c);
	friedman.k      += (variation*k_c);
	friedman.alpha  -= (variation*alpha_c);

	gtk_spin_button_set_value((GtkSpinButton*)Lambda,friedman.lambda);
	gtk_spin_button_set_value((GtkSpinButton*)Omega,friedman.omega);
	gtk_spin_button_set_value((GtkSpinButton*)k,friedman.k);
	gtk_spin_button_set_value((GtkSpinButton*)Alpha,friedman.alpha);

	if(alpha_c)
	{
		init_abacus ();

		calc_quasar_tau (quasar, graphT);
		calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(r_t_displayed)gtk_widget_queue_draw_area(R_t_curve,0,0,200,400);
		if(integrand_displayed)	gtk_widget_queue_draw_area(drawingarea3,0,0,2*width,2*height);

		gtk_widget_queue_draw_area(vue,0,0,2*width,2*height);
	}
}

void
on_Lambda_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data)
{
	lambda_c = 1;
	omega_c  = 0;
	k_c      = 0;
	alpha_c  = 0;
}

void
on_Omega_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data)
{
	lambda_c = 0;
	omega_c  = 1;
	k_c      = 0;
	alpha_c  = 0;
}

void
on_k_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data)
{
	lambda_c = 0;
	omega_c  = 0;
	k_c      = 1;
	alpha_c  = 0;
}

void
on_Alpha_clicked
                                        (GtkSpinButton *spinbutton,
                                        gpointer         user_data)
{
	lambda_c = 0;
	omega_c  = 0;
	k_c      = 0;
	alpha_c  = 1;
}

void
on_spinbutton5_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;

	ascension = gtk_spin_button_get_value(spinbutton);

		//init_abacus ();

		//calc_quasar_tau (quasar, graphT);
		//calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
		gtk_widget_queue_draw_area(vue,0,0,512,512);
}

void
on_spinbutton6_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;

	declination = gtk_spin_button_get_value(spinbutton);

		//init_abacus ();

		//calc_quasar_tau (quasar, graphT);
		//calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
		gtk_widget_queue_draw_area(vue,0,0,512,512);
}

void
on_spinbutton7_changed
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;

	beta = gtk_spin_button_get_value(spinbutton);

		//init_abacus ();

		//calc_quasar_tau (quasar, graphT);
		//calc_quasar_pos(quasar,quasar_pos);
		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
		gtk_widget_queue_draw_area(vue,0,0,512,512);
}

void
on_change_data_lenght
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	int i;
	data_lenght = gtk_spin_button_get_value(spinbutton);

		init_projection_vectors ();
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
			if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
		}
		if(vue_is_displayed[0]|vue_is_displayed_on_vue[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1]|vue_is_displayed_on_vue[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2]|vue_is_displayed_on_vue[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3]|vue_is_displayed_on_vue[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4]|vue_is_displayed_on_vue[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5]|vue_is_displayed_on_vue[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
		gtk_widget_queue_draw_area(vue,0,0,512,512);
}

void
on_change_zoom_rate
                                        (GtkSpinButton *spinbutton,
                                            gpointer user_data)
{

	zoom_rate = gtk_spin_button_get_value(spinbutton);

		gtk_widget_queue_draw_area(vue,0,0,512,512);
}

void init_graph(void)
{

	grapheC0g = (Point*) malloc(sizeof(Point)*2);
	grapheC0(OmegaMax,grapheC0g);

	grapheC1g = (Point*) malloc(sizeof(Point)*2);
	grapheC1(OmegaMax,grapheC1g);

	grapheC2g = (Point*) malloc(sizeof(Point)*200);
	grapheC2(OmegaMax,grapheC2g);

	grapheC31g = (Point*) malloc(sizeof(Point)*600);
	grapheC3(OmegaMax,new_age_universe+delta_age_universe,grapheC31g);

	grapheC32g = (Point*) malloc(sizeof(Point)*600);
	grapheC3(OmegaMax,new_age_universe-delta_age_universe,grapheC32g);

	grapheC4g = (Point*) malloc(sizeof(Point)*20);
	grapheC4(OmegaMax,grapheC4g);

}

void
on_change_universe_age
                                        (GtkSpinButton *spinbutton,
					gpointer user_data)
{

	age_universe = gtk_spin_button_get_value(spinbutton);
	init_graph();
		gtk_widget_queue_draw_area(Lambda_vs_Omega_curve,0,0,512,512);
}


void
 on_change_delta_universe_age
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{

	delta_age_universe = gtk_spin_button_get_value(spinbutton);
	init_graph();
		gtk_widget_queue_draw_area(Lambda_vs_Omega_curve,0,0,512,512);
}


void
on_scale_factor_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
		h = gtk_spin_button_get_value(spinbutton);
		AGE_CST=(100.0/9.78)*h;
		init_graph();
		gtk_widget_queue_draw_area(Lambda_vs_Omega_curve,0,0,512,512);
}


void
on_Z_decoupling_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
		zr = gtk_spin_button_get_value(spinbutton);
		init_graph();
		gtk_widget_queue_draw_area(Lambda_vs_Omega_curve,0,0,512,512);
}



void
on_Annuler_activate                    (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(colorselector);
}


void
on_Choisir_couleur_activate            (GtkButton       *button,
                                        gpointer         user_data)
{
	memcpy(current_color, tmp_current_color, sizeof(gdouble));
	gtk_widget_queue_draw_area(Lambda_vs_Omega_curve,0,0,512,512);
}


void
on_colorselection1_color_changed       (GtkColorSelection *colorselection,
                                        gpointer         user_data)
{
	gtk_color_selection_get_color   (colorselection, tmp_current_color);
}


gboolean
on_graphC0_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	gtk_widget_show(create_Color_selector ());
  return FALSE;
}


gboolean
on_graphC2_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	gtk_widget_show(create_Color_selector ());
  return FALSE;
}


gboolean
on_graphC3_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	gtk_widget_show(create_Color_selector ());
  return FALSE;
}


gboolean
on_graphC4_color_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	gtk_widget_show(create_Color_selector ());
  return FALSE;
}

int format_selection_done=0;
GtkWidget* format_specifior;
GtkWidget* format_specifior2;

void
on_file_selected             (GtkButton       *button,
                                        gpointer         user_data)
{

	format_specifior = create_format_specifior();
	gtk_widget_show(format_specifior);
}

void
on_file_selection_quit             (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(fileselection1);
}

void
on_file_selected_save             (GtkButton       *button,
                                        gpointer         user_data)
{

	format_specifior2 = create_format_specifior_save();
	gtk_widget_show(format_specifior2);
}

void
on_file_selection_quit_save             (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(fileselection2);
}

void
on_fermer_message_activate             (GtkButton       *button,
                                        gpointer         user_data)
{
	message_displayed--;
	gtk_widget_destroy(message_window[message_displayed]);
}

void
on_text_space_separated_format1_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	read_quasar = read_txt_quasar;
	get_nb_quasar = get_txt_nb_quasar;
}


void
on_xml_xls1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	read_quasar = read_xml_quasar;
	get_nb_quasar = get_xml_nb_quasar;
}


void
on_bin_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	read_quasar = read_bin_quasar;
	get_nb_quasar = get_bin_nb_quasar;
}

void
on_fermer_format_selection_activate             (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(format_specifior);
}

void
on_OK_format_selection_activate             (GtkButton       *button,
                                        gpointer         user_data)
{
	char* fname;
	int i;
	char mess[32];

	fname = (char*) gtk_file_selection_get_filename((GtkFileSelection*)fileselection1);
	gtk_widget_destroy(fileselection1);
	init_abacus ();

	data_lenght = get_nb_quasar (fname);
	
	data_lenght_max = data_lenght;
	quasar_pos 	= (Vector *) malloc(data_lenght*sizeof(Vector));
	quasar		= (Quasar *) malloc(data_lenght*sizeof(Quasar));
	graphT		= (Point*) malloc((data_lenght+1)*sizeof(Point));

	read_quasar (fname,quasar);

	sprintf(mess,"%d objets lus\n", data_lenght);
	alerte(mess);
	data_size=data_lenght;
	calc_quasar_tau (quasar, graphT);
	calc_quasar_pos(quasar,quasar_pos);
	init_projection_vectors ();


	for(i=0;i<NBVIEWS;i++)
	{
		if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])quasar_proj[i] =set_quasar_proj (quasar_pos,i);
		if(vue_is_displayed[i]|vue_is_displayed_on_vue[i])the_earth[i]=set_earth_proj(earth,i);
	}
	if(vue_is_displayed[0]|vue_is_displayed_on_vue[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
	if(vue_is_displayed[1]|vue_is_displayed_on_vue[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
	if(vue_is_displayed[2]|vue_is_displayed_on_vue[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
	if(vue_is_displayed[3]|vue_is_displayed_on_vue[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
	if(vue_is_displayed[4]|vue_is_displayed_on_vue[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
	if(vue_is_displayed[5]|vue_is_displayed_on_vue[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
	gtk_widget_queue_draw_area(vue,0,0,512,512);

	gtk_widget_destroy(format_specifior);
}


void
on_lambda_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	lambda_step = gtk_spin_button_get_value(spinbutton);
	gtk_widget_destroy(Lambda);
  Lambda_adj = gtk_adjustment_new (friedman.lambda, -100, 100, lambda_step, lambda_step, 1);
  Lambda = gtk_spin_button_new (GTK_ADJUSTMENT (Lambda_adj), 1, 7);
  gtk_widget_set_name (Lambda, "Lambda");
  gtk_widget_show (Lambda);
  gtk_fixed_put (GTK_FIXED (coord1), Lambda, 88, 8);
  gtk_widget_set_usize (Lambda, 85, 28);

  g_signal_connect ((gpointer) Lambda, "value_changed",
                    G_CALLBACK (on_Lambda_changed),
                    NULL);

}

void
on_omega_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	omega_step = gtk_spin_button_get_value(spinbutton);
	gtk_widget_destroy(Omega);
  Omega_adj = gtk_adjustment_new (friedman.omega, -100, 100, omega_step, omega_step, 1);
  Omega = gtk_spin_button_new (GTK_ADJUSTMENT (Omega_adj), 1, 7);
  gtk_widget_set_name (Omega, "Omega");
  gtk_widget_show (Omega);
  gtk_fixed_put (GTK_FIXED (coord1), Omega, 88, 40);
  gtk_widget_set_usize (Omega, 85, 28);

  g_signal_connect ((gpointer) Omega, "value_changed",
                    G_CALLBACK (on_Omega_changed),
                    NULL);

}

void
on_k_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	k_step = gtk_spin_button_get_value(spinbutton);

	gtk_widget_destroy(k);
  k_adj = gtk_adjustment_new (friedman.k, -100, 100, k_step, k_step, 1);
  k = gtk_spin_button_new (GTK_ADJUSTMENT (k_adj), 1, 7);
  gtk_widget_set_name (k, "k");
  gtk_widget_show (k);
  gtk_fixed_put (GTK_FIXED (coord1), k, 88, 72);
  gtk_widget_set_usize (k, 85, 28);

  g_signal_connect ((gpointer) k, "value_changed",
                    G_CALLBACK (on_k_changed),
                    NULL);

}

void
on_alpha_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	alpha_step = gtk_spin_button_get_value(spinbutton);
	gtk_widget_destroy(Alpha);
  Alpha_adj = gtk_adjustment_new (friedman.alpha, -100, 100, alpha_step, alpha_step, 1);
  Alpha = gtk_spin_button_new (GTK_ADJUSTMENT (Alpha_adj), 1, 7);
  gtk_widget_set_name (Alpha, "Alpha");
  gtk_widget_show (Alpha);
  gtk_fixed_put (GTK_FIXED (coord1), Alpha, 88, 104);
  gtk_widget_set_usize (Alpha, 85, 28);

  g_signal_connect ((gpointer) Alpha, "value_changed",
                    G_CALLBACK (on_Alpha_changed),
                    NULL);

}

void
on_ascension_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	ascension_step = gtk_spin_button_get_value(spinbutton);

  spinbutton5_adj = gtk_adjustment_new (ascension, -PI, PI, PI/ascension_step, PI/ascension_step, 1);
  spinbutton5 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton5_adj), 1, 5);
  gtk_widget_set_name (spinbutton5, "spinbutton5");
  gtk_widget_show (spinbutton5);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton5, 112, 8);
  gtk_widget_set_usize (spinbutton5, 62, 21);


g_signal_connect ((gpointer) spinbutton5, "value_changed",
                    G_CALLBACK (on_spinbutton5_changed),
                    NULL);

}

void
on_declinaison_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	declinaison_step = gtk_spin_button_get_value(spinbutton);


  spinbutton6_adj = gtk_adjustment_new (declination, -PI, PI, PI/declinaison_step, PI/declinaison_step, 1);
  spinbutton6 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton6_adj), 1, 5);
  gtk_widget_set_name (spinbutton6, "spinbutton6");
  gtk_widget_show (spinbutton6);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton6, 112, 40);
  gtk_widget_set_usize (spinbutton6, 62, 21);


g_signal_connect ((gpointer) spinbutton6, "value_changed",
                    G_CALLBACK (on_spinbutton6_changed),
                    NULL);

}

void
on_beta_step_change
					(GtkSpinButton *spinbutton,
                                            gpointer user_data)
{
	beta_step = gtk_spin_button_get_value(spinbutton);


  spinbutton7_adj = gtk_adjustment_new (beta, -PI, PI, PI/beta_step, PI/beta_step, 1);
  spinbutton7 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton7_adj), 1, 5);
  gtk_widget_set_name (spinbutton7, "spinbutton7");
  gtk_widget_show (spinbutton7);
  gtk_fixed_put (GTK_FIXED (coord2), spinbutton7, 112, 72);
  gtk_widget_set_usize (spinbutton7, 62, 21);


g_signal_connect ((gpointer) spinbutton7, "value_changed",
                    G_CALLBACK (on_spinbutton7_changed),
                    NULL);

}

int quasar_num=-1;
Vector myquasar[2];

void
on_button7_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	quasar_num = 0;alerte("choix du quasar 1 ...");
}

void
on_button8_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	quasar_num = 1;alerte("choix du quasar 2 ...");
}

void
on_button13_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	double result=0;
	char text[256];

	quasar_num = -1;
	//result = codistance(myquasar[0],myquasar[1]);

	sprintf(text, "%lf", result);
	buff = g_strdup_printf (text);
	gtk_entry_set_text((GtkEntry*)entry3,buff);

}

gboolean
on_vue_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	int x, y, there;
	GdkModifierType state;
	gint width;
	gint height;
	Point here;
	alerte("attention ...");
	if(quasar_num != -1)
	{	alerte("choix ...");
		gtk_widget_get_size_request(vue,&width,&height);
		width = width/2;
		height = height/2;


		gdk_window_get_pointer (event->window, &x, &y, &state);

		if (state & GDK_BUTTON1_MASK)
		{
			here.x = (x-width)/(2*width);
			here.y = (y-height)/(2*height);

			there=coor_tableau(quasar_proj[current_view],data_lenght,here);
			if(there>=0)
			{
				myquasar[quasar_num]=quasar_pos[there];
				alerte("Quasar choosed! ");
			}
			else if(there==-1) alerte("There is no point here ! ");
			else if(there==-2) alerte("There is too many points here ! ");
			/*for(i=0;i<NBVIEWS;i++)
				the_myquasar[0][i]=set_earth_proj(myquasar[0],i);*/

		}
	}

	return FALSE;
}

void
on_fermer_format_save_selection_activate             (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(format_specifior2);
}

void
on_OK_format_save_selection_activate             (GtkButton       *button,
                                        gpointer         user_data)
{
	char* fname;

	fname = (char*) gtk_file_selection_get_filename((GtkFileSelection*)fileselection2);
	gtk_widget_destroy(fileselection2);
	write_quasar (quasar,fname);
}

void
on_text_space_separated_format1_save_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	write_quasar = write_txt_quasar;
}


void
on_xml_xls1_save_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	write_quasar = write_xml_quasar;
}


void
on_bin_save_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	write_quasar = write_bin_quasar;
}

void
on_ps_save_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	write_quasar = write_ps_quasar;
}

Vector center;
Vector periph;

gboolean
on_edge_vue_1_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert W pour le centre de la selection

	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[0])
		{
			// remplacer les valeurs
			center.x = (double) (x-256)/256;
			center.t = (double) (y-256)/256;
			s_coord_c[0] = 1;
			s_coord_c[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[0])
			{
				center.x = (double) (x-256)/256;
				s_coord_c[0] = 1;
			}
			if(!s_coord_c[3])
			{
				center.t = (double) (y-256)/256;
				s_coord_c[3] = 1;
			}
			s_vue[0] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_1,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_edge_vue_2_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner Y ert W pour le centre de la selection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[1])
		{
			// remplacer les valeurs
			center.y = (double) (x-256)/256;
			center.t = (double) (y-256)/256;
			s_coord_c[1] = 1;
			s_coord_c[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[1])
			{
				center.y = (double) (x-256)/256;
				s_coord_c[1] = 1;
			}
			if(!s_coord_c[3])
			{
				center.t = (double) (y-256)/256;
				s_coord_c[3] = 1;
			}

			s_vue[1] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_2,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_edge_vue_3_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner Z ert W pour le centre de la selection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[2])
		{
			// remplacer les valeurs
			center.z = (double) (x-256)/256;
			center.t = (double) (y-256)/256;
			s_coord_c[2] = 1;
			s_coord_c[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[2])
			{
				center.z = (double) (x-256)/256;
				s_coord_c[2] = 1;
			}
			if(!s_coord_c[3])
			{
				center.t = (double) (y-256)/256;
				s_coord_c[3] = 1;
			}

			s_vue[2] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_3,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_1_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert Z pour le centre de la selection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[3])
		{
			// remplacer les valeurs
			center.x = (double) (x-256)/256;
			center.z = (double) (y-256)/256;
			s_coord_c[0] = 1;
			s_coord_c[2] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[0])
			{
				center.x = (double) (x-256)/256;
				s_coord_c[0] = 1;
			}
			if(!s_coord_c[2])
			{
				center.z = (double) (y-256)/256;
				s_coord_c[2] = 1;
			}

			s_vue[3] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(front_vue_1,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_2_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert Y pour le centre de la selection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[4])
		{
			// remplacer les valeurs
			center.x = (double) (x-256)/256;
			center.y = (double) (y-256)/256;
			s_coord_c[0] = 1;
			s_coord_c[1] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[0])
			{
				center.x = (double) (x-256)/256;
				s_coord_c[0] = 1;
			}
			if(!s_coord_c[1])
			{
				center.y = (double) (y-256)/256;
				s_coord_c[1] = 1;
			}

			s_vue[4] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(front_vue_2,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_3_button_press_event

                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner Y ert Z pour le centre de la selection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[5])
		{
			// remplacer les valeurs
			center.y = (double) (x-256)/256;
			center.z = (double) (y-256)/256;
			s_coord_c[1] = 1;
			s_coord_c[2] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_c[1])
			{
				center.y = (double) (x-256)/256;
				s_coord_c[1] = 1;
			}
			if(!s_coord_c[2])
			{
				center.z = (double) (y-256)/256;
				s_coord_c[2] = 1;
			}

			s_vue[5] = 1;
		}
		if((s_coord_c[0] == 1) && (s_coord_c[1] ==  1) && (s_coord_c[2] == 1) && (s_coord_c[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(front_vue_3,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
	return FALSE;
}


gboolean
on_edge_vue_1_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert W pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[0])
		{
			// remplacer les valeurs
			periph.x = (double) (x-256)/256;
			periph.t = (double) (y-256)/256;
			s_coord_p[0] = 1;
			s_coord_p[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[0])
			{
				periph.x = (double) (x-256)/256;
				s_coord_p[0] = 1;
			}
			if(!s_coord_p[3])
			{
				periph.t = (double) (y-256)/256;
				s_coord_p[3] = 1;
			}

			s_vue[0] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_1,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_edge_vue_2_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner Y ert W pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[1])
		{
			// remplacer les valeurs
			periph.y = (double) (x-256)/256;
			periph.t = (double) (y-256)/256;
			s_coord_p[1] = 1;
			s_coord_p[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[1])
			{
				periph.y = (double) (x-256)/256;
				s_coord_p[1] = 1;
			}
			if(!s_coord_p[3])
			{
				periph.t = (double) (y-256)/256;
				s_coord_p[3] = 1;
			}

			s_vue[1] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_2,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_edge_vue_3_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner Z ert W pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[2])
		{
			// remplacer les valeurs
			periph.z = (double) (x-256)/256;
			periph.t = (double) (y-256)/256;
			s_coord_p[2] = 1;
			s_coord_p[3] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[2])
			{
				periph.z = (double) (x-256)/256;
				s_coord_p[2] = 1;
			}
			if(!s_coord_p[3])
			{
				periph.t = (double) (y-256)/256;
				s_coord_p[3] = 1;
			}

			s_vue[2] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(edge_vue_3,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_1_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert Z pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[3])
		{
			// remplacer les valeurs
			periph.x = (double) (x-256)/256;
			periph.z = (double) (y-256)/256;
			s_coord_p[0] = 1;
			s_coord_p[2] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[0])
			{
				periph.x = (double) (x-256)/256;
				s_coord_p[0] = 1;
			}
			if(!s_coord_p[2])
			{
				periph.z = (double) (y-256)/256;
				s_coord_p[2] = 1;
			}

			s_vue[3] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(front_vue_1,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_2_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	// permet de sélectionner X ert Y pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[4])
		{
			// remplacer les valeurs
			periph.x = (double) (x-256)/256;
			periph.y = (double) (y-256)/256;
			s_coord_p[0] = 1;
			s_coord_p[1] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[0])
			{
				periph.x = (double) (x-256)/256;
				s_coord_p[0] = 1;
			}
			if(!s_coord_p[1])
			{
				periph.y = (double) (y-256)/256;
				s_coord_p[1] = 1;
			}

			s_vue[4] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}

	//gtk_widget_queue_draw_area(front_vue_2,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

gboolean
on_front_vue_3_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)

{
	// permet de sélectionner Y ert Z pour la périphélie de la sélection
	int x,y;
	GdkModifierType state;

	gdk_window_get_pointer (event->window, &x, &y, &state);

	if (state)// & GDK_BUTTON1_MASK)
	{
		if(s_vue[5])
		{
			// remplacer les valeurs
			periph.y = (double) (x-256)/256;
			periph.z = (double) (y-256)/256;
			s_coord_p[1] = 1;
			s_coord_p[2] = 1;

		}
		else
		{
			// définir les valeurs encore non définies
			if(!s_coord_p[1])
			{
				periph.y = (double) (x-256)/256;
				s_coord_p[1] = 1;
			}
			if(!s_coord_p[2])
			{
				periph.z = (double) (y-256)/256;
				s_coord_p[2] = 1;
			}

			s_vue[5] = 1;
		}
		if((s_coord_p[0] == 1) && (s_coord_p[1] ==  1) && (s_coord_p[2] == 1) && (s_coord_p[3] == 1))
		{
			//zoom !
			alerte("ZOOOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMM!!!\n");
		}
	}
	//gtk_widget_queue_draw_area(front_vue_3,0,0,512,512);
		if(vue_is_displayed[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
		if(vue_is_displayed[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
		if(vue_is_displayed[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
		if(vue_is_displayed[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
		if(vue_is_displayed[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
		if(vue_is_displayed[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);

	return FALSE;
}

void
on_Compute_Isotropic_Distribution_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	int nbre;
	double Zmax;
	double Zmin;
	double ra0;
	double d0;
	double beta;
	int i;
	char mess[32];

	nbre = gtk_spin_button_get_value((GtkSpinButton*)spinbutton35);
	Zmax = gtk_spin_button_get_value((GtkSpinButton*)spinbutton37);
	Zmin = gtk_spin_button_get_value((GtkSpinButton*)spinbutton36);
	ra0 = gtk_spin_button_get_value((GtkSpinButton*)spinbutton38);
	d0 = gtk_spin_button_get_value((GtkSpinButton*)spinbutton39);
	beta = gtk_spin_button_get_value((GtkSpinButton*)spinbutton40);

	init_abacus ();
	data_lenght = nbre;
	data_lenght_max = data_lenght;
	quasar_pos 	= (Vector *) malloc(data_lenght*sizeof(Vector));
	quasar		= (Quasar *) malloc(data_lenght*sizeof(Quasar));
	graphT		= (Point*) malloc((data_lenght+1)*sizeof(Point));

	isotrope(nbre, Zmax, Zmin, ra0, d0, beta, quasar);

	data_size=data_lenght;
	sprintf(mess,"%d objets lus\n", data_lenght);
	alerte(mess);

	calc_quasar_tau (quasar, graphT);
	calc_quasar_pos(quasar,quasar_pos);
	init_projection_vectors ();

	for(i=0;i<NBVIEWS;i++)
	{
		quasar_proj[i] =set_quasar_proj (quasar_pos,i);
		the_earth[i]=set_earth_proj(earth,i);
	}

if(vue_is_displayed[0]|vue_is_displayed_on_vue[0])gtk_widget_queue_draw_area(edge_1,0,0,512,512);
	if(vue_is_displayed[1]|vue_is_displayed_on_vue[1])gtk_widget_queue_draw_area(edge_2,0,0,512,512);
	if(vue_is_displayed[2]|vue_is_displayed_on_vue[2])gtk_widget_queue_draw_area(edge_3,0,0,512,512);
	if(vue_is_displayed[3]|vue_is_displayed_on_vue[3])gtk_widget_queue_draw_area(front_1,0,0,512,512);
	if(vue_is_displayed[4]|vue_is_displayed_on_vue[4])gtk_widget_queue_draw_area(front_2,0,0,512,512);
	if(vue_is_displayed[5]|vue_is_displayed_on_vue[5])gtk_widget_queue_draw_area(front_3,0,0,512,512);
	gtk_widget_queue_draw_area(vue,0,0,512,512);

	// 35, 37, 36, 38, 39, 40
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton) == TRUE)
	{
		radians = 0;
	}
	else
	{
		radians = 1;
	}
}

