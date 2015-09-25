/*______________________________________________________________*/
/*								*/
/* Réunit les fonctions traitant l'initialisation du repere	*/
/*  de projection, la projection de face, la projection de 	*/
/*  cote et l'affichage quasar par quasar de ces projections	*/
/*______________________________________________________________*/


void init_projection_vectors ();
Point projection (Vector,Vector,Vector);
Point *set_quasar_proj(Vector *,int);
Point set_earth_proj(Vector,int);



