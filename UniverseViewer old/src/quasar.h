/*______________________________________________________________*/
/* 								*/
/* R�nit les fonctions traitant la lecture du fichier des	*/
/*  quasars, le stockage des codistances de chaque quasar �*/
/*  la Terre, la cr�tion de quasars virtuels n�essaires	*/
/*  aux reperes							*/
/*______________________________________________________________*/


int read_bin_quasar (char *filename,Quasar *);
int read_xml_quasar (char *filename,Quasar *);
int read_txt_quasar (char *filename,Quasar *);
int get_bin_nb_quasar (char *filename);
int get_xml_nb_quasar (char *filename);
int get_txt_nb_quasar (char *filename);
void write_bin_quasar (Quasar * quasar,char *filename);
void write_txt_quasar (Quasar * quasar,char *filename);
void write_xml_quasar(Quasar* q, char* filename);
void write_ps_quasar(Quasar* q, char* filename);
void calc_quasar_tau (Quasar *,Point *);
void calc_quasar_pos (Quasar *,Vector *);
void calc_quasar_proj (Vector *,Vector,Vector,int,Point *);
Quasar Qinit(double,double,double,double);

int  (*read_quasar) (char* fname, Quasar*quasar);
int  (*get_nb_quasar) (char* fname);
void (*write_quasar) (Quasar * q,char *filename);

