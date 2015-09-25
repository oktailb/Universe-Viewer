typedef struct	s_colorstr
{
  unsigned char	r;
  unsigned char	g;
  unsigned char	b;
}		colorstr;

typedef struct	s_vector
{
  double	x;
  double	y;
  double	z;
  double	t;
}		Vector;

typedef struct	s_friedman
{
  double	lambda;
  double	omega;
  double	k;
  double	alpha;
}		Friedman;

typedef struct	s_quasar
{
  double	ascension;
  double	declination;
  double	redshift;
  double	tau;
  double	magnitude;
}		Quasar;

typedef struct	s_point
{
  double	x;
  double	y;
  int		size;
}		Point;

typedef struct		s_graph
{
  int			nbpoints;
  Point			*points;
  colorstr		color;
  int			type;
  struct s_graph	*next;
}			Graph;

typedef struct		s_gstring
{
  Point			pos;
  char			*string;
  int			lenght;
  colorstr		color;
  int			xoffset;
  int			yoffset;
  struct s_gstring	*next;
}			Gstring;

typedef struct	s_graphic
{
  int		id;
  int		is_shown;
  Graph*	graph;
  Point		scale;
  Point		center;
  int		xsize;
  int		ysize;
  int		x_y;
  colorstr	foreground;
  colorstr	background;
}		Graphic;

typedef struct	s_environnement
{
  int		bounced;
  char		*data_filename;
  int		data_lenght;
  int		data_lenght_max;
  int		data_size;
  double	zoom_rate;
  double	*current_color;
  Quasar	*quasar;
  Vector	*quasar_pos;
  Point		*graphT;
  Point		*the_earth[6];
  Friedman	friedman;
  Friedman	vieux_friedman;
  Vector	earth;
  Vector	direction1;
  Vector	direction2;
  Vector	direction3;
  Vector	direction4;
  double	ascension;
  double	declination;
  double	beta;
  double	*abacus;
  double	*abacusV;
  double	abacus_pas;
  double	abacus_max0;
  double	abacus_max;
  double	abacusVmax;
  double	distance_max;
  double	nb_causal_cell;
  int		disfunction;
  int		abacus_prec;
  int		codistance_prec;
  int		graphP_lenght;
  double	choose_prec;
  int		graphA_lenght;
  int		graphC2_lenght;
  int		graphC3_lenght;
  int		graphC4_lenght;
  int		graphA_prec;
  int		graphC_prec;
  double	graphC2_eps;
  double	graphC3_eps;
  double	graphC4_eps;
  double	h;
  double	AGE_CST;
  double	age_universe;
  double	new_age_universe;
  double	delta_age_universe;
  double	RadiusMax;
  double	OmegaMax;
  Point		*grapheC0g;
  Point		*grapheC1g;
  Point		*grapheC2g;
  Point		*grapheC31g;
  Point		*grapheC32g;
  Point		*grapheC4g;
  int		*status;
  Point		*quasar_proj[6];
  Vector	null_vector;
  Vector	metric_vector;
  double	zr;
  double	graphAx_max;
  double	graphAy_max;
  double	graphCx_max;
  double	graphCy_max;
  double	inte;
  int		quanta;
  Friedman	old_friedman;
  char		buff[256];
  double	graphTx_max;
  double	graphTy_max;
  int		radians;
  double	graphPy_max;
  double	graphPx_max;
  int		file_to_select;
  int		is_viewed;
  int		is_radians;
  int		is_static;
  int		is_myquasar_shown;
  int		pixel_prec;
  Point		scale_rate;
  Graphic	view[NBGRAPHICS];
  Graph		graphview[NBVIEWS];
  Graph		graphearth[NBVIEWS];
  Graph		graphmyquasar[2][NBVIEWS];
  Graph		graphaxes[4];
  Graph		graphviewT;
  Graph		graphviewP;
  Graph		graphviewA1;
  Graph		graphviewA2;
  Graph		graphviewC0;
  Graph		graphviewC1;
  Graph		graphviewC2;
  Graph		graphviewC31;
  Graph		graphviewC32;
  Graph		graphviewC4;
  Graph		graphzoom;
  char*		stringaxes[8];
  char*		stringscale[8];
  char		scale[8][64];
}		Environnement;

