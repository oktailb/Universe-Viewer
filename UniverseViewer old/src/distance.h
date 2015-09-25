/*______________________________________________________________*/
/*								*/
/* R�unit les fonctions traitant la codistance entre deux	*/
/*  quasars, la codistance d'un quasar � la Terre, un abaque	*/
/*  de codistances r�f�rences, l'integrande des codistances et	*/
/*  l'integration dudit integrande					*/
/*______________________________________________________________*/ 

double codistance(Quasar *,Quasar *);
double earth_codistance(Quasar *);
void   init_abacus(void);
double PdeR(double);
double ONEonPdeR(double);
double AONEonPdeR(double);
double RonPdeR(double);
double DomRonPdeR(double);
double DlaRonPdeR(double);
double integral(double (*f)(),double,double,int);
void grapheP(Point *);
