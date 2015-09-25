/* R�nit les type pr��inis traitant les quadrivecteurs,	*/
/*  la structure cosmologique, les quasars et les points	*/

#ifndef __COSMO_STRUCT_H__
#define __COSMO_STRUCT_H__

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define TITLE "Universe Viewer 2"

#define  NBVIEWS 6
#define  NBGRAPHICS 11
#define  NBPLOTS 4
#define  SCALE 2.05

//#define ABS(x)   ((x<0)?(-x):(x))
#define  PI 3.14159265398
#define LAMBDA 1.0
#define OMEGA  0.2
#define K      0.20005
#define ALPHA  0.00005
#define AGE 12.098586


typedef struct
{
	guchar r;
	guchar g;
	guchar b;
}colorstr;

typedef struct s_vector
    {
       double x,
              y,
              z,
              t;
    } Vector;

typedef struct s_friedman
	{
		double lambda,
		       omega,
		       k,
		       alpha;
	} Friedman;

typedef struct s_quasar
	{
		double ascension,
		       declination,
		       redshift,
		       tau,
		       magnitude;
	} Quasar;

typedef struct s_point
	{
		double x,y;
		int size;
	} Point;
/*
typedef struct s_graph
	{
		int	nbpoints;
		Point	*points;
		GdkColor	color;
		int	type;
		struct s_graph *next;
	} Graph;

typedef struct s_gstring
	{
		Point	pos;
		char   *string;
		int	lenght;
		GdkColor	color;
		int	xoffset,yoffset;
		struct s_gstring *next;
	} Gstring;

typedef struct s_graphic
	{
		int	id;
		GtkWidget*  menu;
		GtkWidget*	dialog;
		GtkWidget*	widget;
		GtkWindow*	window;
		GdkGC	gc;
		int	is_shown;
		Graph * graph;
		Gstring * gstring;
		Point	scale;
		Point	center;
		int	xsize,ysize;
		int	x_y;
		GdkColor	foreground,background;
	} Graphic;
*/
Point *quasar_proj[6];

#endif
