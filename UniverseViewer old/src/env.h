
typedef struct s_environnement
   {
	int		file_to_select;
	int		is_viewed;
	int		is_radians;
	int		is_static;
	int		is_myquasar_shown;
	int		pixel_prec;
	Point		scale_rate;

	Graphic		view[NBGRAPHICS];
	Graph		graphview[NBVIEWS];
	Graph		graphearth[NBVIEWS];
	Graph		graphmyquasar[2][NBVIEWS];
	Graph		graphaxes[4];
	Graph		graphviewT;
	Graph		graphviewP;
	Graph		graphviewA1,
			graphviewA2;
	Graph		graphviewC0,
			graphviewC1,
			graphviewC2,
			graphviewC31,
			graphviewC32,
			graphviewC4;
	Graph		graphzoom;
	Gstring		stringaxes[8];
	Gstring		stringscale[8];
	char		scale[8][64];

	Widget		d_filereq,t_filereq;
	Widget		d_alert,l_alert;
	Widget		t_doc;
	Widget		t_zoom;
	Widget		t_size;
	Widget		t_chage,t_cells,t_age;
	Widget		t_lambda,t_omega,t_k,t_alpha;
	Widget		t_q1x,t_q1y,t_q1z,t_q1t,t_q2x,t_q2y,t_q2z,t_q2t;
	Widget		t_astep,t_dstep,t_bstep;
	Widget		t_ascension,t_declination,t_beta;
	Widget		t_distance;
   } Environnement;

/* Fonction de gestion de l'interface graphique */
void manage_interface (int , char **);

void dialog_init();
void dialog_filereq_init();
void dialog_alert_init();
void dialog_steps_init();
void dialog_calculus_init();
void dialog_options_init();
void dialog_distance_init();
void dialog_isotrop_init();
void dialog_doc_init();
void dialog_about_init();
void dialog_views_init();

void menu_init();
void area_friedman_init();
void area_mainview_init();
void area_angles_init();
void area_zoom_init();

void hide_zero (char *string);
