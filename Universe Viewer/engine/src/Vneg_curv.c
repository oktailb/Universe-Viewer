#include "uv.h"

/* give an euclidian vector in cas of k<0 of a QSO			*/

Vector Vneg_curv (Quasar *q)
{
	Vector u;

	u.t = cosh(q->tau);
	u.z = sinh(q->tau);
	u.y = u.z*cos(q->declination);
	u.z *= sin(q->declination);	
	u.x = u.y*cos(q->ascension);
	u.y *= sin(q->ascension);
	return u;
}

