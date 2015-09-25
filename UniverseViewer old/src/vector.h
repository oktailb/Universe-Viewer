/*______________________________________________________________*/
/*								*/
/* Réunit les fonctions traitant la création de quadrivecteurs, */
/*  leur produit scalaire, leur norme, leur normalisation, 	*/
/*  leur produit vectoriel, leur addition, leur multiplication	*/
/*  par un scalaire						*/
/*______________________________________________________________*/ 


Vector Vinit (double,double,double,double);
double Vscalar (Vector,Vector); 
double Vnorme (Vector);
Vector Vnormalize (Vector);
Vector Vproduct (Vector,Vector);
Vector Vadd (Vector,Vector);
Vector Vmult (Vector,double);

/*______________________________________________________________*/
/*								*/
/* Réunit les fonctions qui construisent les vecteurs position	*/
/*  dans R4 des quasars, en courbure positive ou négative	*/
/*______________________________________________________________*/


Vector Vpos_curv (Quasar *);
Vector Vnul_curv (Quasar *);
Vector Vneg_curv (Quasar *);
