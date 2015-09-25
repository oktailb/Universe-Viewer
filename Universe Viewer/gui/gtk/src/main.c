#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "interface.h"
#include "support.h"

/*	DECLARATION DES VARIABLES GLOBALES						*/

#include "struct.h"
#include "vector.h"
#include "callbacks.h"
#include "calldraw.h"
#include "distance.h"
#include "quasar.h"
#include "projection.h"
#include "isotrop.h"
#include "space.h"

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <signal.h>

char *data_filename;
int   data_lenght,data_lenght_max;
int   data_size;

double zoom_rate = 0.95;
gdouble* current_color;

Quasar *quasar;
Vector *quasar_pos;
Point* graphT;
Point the_earth[6];

Friedman friedman={LAMBDA,OMEGA,K,ALPHA}, vieux_friedman;
Vector earth={0.0,0.0,0.0,1.0};
Vector direction1,direction2,direction3,direction4;
double ascension=0.0;
double declination=0.0;
double beta=0.0;


double *abacus, *abacusV;
double abacus_pas=0.1;
double abacus_max0=4.5;
double abacus_max=4.5;
double abacusVmax;
double distance_max;
double nb_causal_cell=1.0;
int disfunction;
int abacus_prec=6;
int codistance_prec=3;
int graphP_lenght=200;
double choose_prec=1.0;
int graphA_lenght=200,graphC2_lenght=200,graphC3_lenght=600,graphC4_lenght=20;
int graphA_prec=6,graphC_prec=6;
double graphC2_eps=0.001,graphC3_eps=0.005,graphC4_eps=0.01;
double h=0.75;
double AGE_CST,age_universe=AGE,new_age_universe=AGE;
double delta_age_universe=2.0;
const gchar *buff;

extern double RadiusMax;
extern double OmegaMax;

Point *grapheC0g,*grapheC1g,*grapheC2g,*grapheC31g,*grapheC32g,*grapheC4g;

int *status;

pid_t cree_fils(void (*func)(void), int w)
{
	pid_t pid;

	pid = fork();
	switch(pid)
	{
		case -1:
			printf("Erreur dans la creation du processus !\n");
			exit(-1);
		case 0:
			func();
			exit(0);
			break;
		default:
			if(w)wait(status);
			return pid;
			break;
	}
}

void loading(void)
{
	GtkWidget *load_screen;
	//gtk_set_locale ();
	gtk_init (NULL,NULL);
	//buff = g_strdup_printf ("Waiting ...");

	//add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	load_screen = create_load();
	gtk_widget_show(load_screen);

	gtk_main();
}

int
main (int argc, char *argv[])
{
	GtkWidget *Universe_Viewer_2;

	int i, pid;
	char mess[32];
	pid=cree_fils(loading,0);
  gtk_set_locale ();
  gtk_init (&argc, &argv);
	//buff = g_strdup_printf ("Waiting ...");
	gdk_rgb_init();
  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

	AGE_CST=(100.0/9.78)*h;
	read_quasar = read_txt_quasar;
	get_nb_quasar = get_txt_nb_quasar;

	data_filename=(char *) calloc(256,sizeof(char));
	if(argc==2) strcpy(data_filename,argv[1]);
	else strcpy(data_filename,"data/Burbridge.txt");
	init_abacus ();
	data_lenght = get_txt_nb_quasar (data_filename);
	data_lenght_max = data_lenght;
	quasar_pos 	= (Vector *) malloc(data_lenght*sizeof(Vector));
	quasar		= (Quasar *) malloc(data_lenght*sizeof(Quasar));
	graphT		= (Point*) malloc((data_lenght+1)*sizeof(Point));



	read_txt_quasar (data_filename,quasar);

	data_lenght=data_size;
		sprintf(mess,"%d objets lus\n", data_lenght);
	calc_quasar_tau (quasar, graphT);
	calc_quasar_pos(quasar,quasar_pos);
	init_projection_vectors ();
	init_graph();

	for(i=0;i<NBVIEWS;i++)
	{
		quasar_proj[i] =set_quasar_proj (quasar_pos,i);
		the_earth[i]=set_earth_proj(earth,i);
	}

	Universe_Viewer_2 = create_Universe_Viewer_2 (quasar_proj);
	kill(pid,SIGINT);
	gtk_widget_show (Universe_Viewer_2);
	alerte(mess);
	gtk_main();

	// penser à faire le ménage !!!

		free(grapheC0g);
		free(grapheC1g);
		free(grapheC2g);
		free(grapheC31g);
		free(grapheC32g);
		free(grapheC4g);

		//gtk_widget_destroy(Universe_Viewer_2);

	return 0;
}

