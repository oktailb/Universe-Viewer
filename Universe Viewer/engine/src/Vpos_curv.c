#include "uv.h"

/* give an euclidian vector in cas of k>0 of a QSO	*/

Vector Vpos_curv (Quasar *q)
{
	Vector u;

	u.t = cos(q->tau);
	u.z = sin(q->tau);
	u.y = u.z*cos(q->declination);
	u.z *= sin(q->declination);	
	u.x = u.y*cos(q->ascension);
	u.y *= sin(q->ascension);

/*	printf("%lf {} %lf {} %lf\n",q->tau,q->ascension,q->declination);
	printf("%lf || %lf || %lf || %lf\n",u.x,u.y,u.z,u.t);
*/
	return u;
}

