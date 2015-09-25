#include "uv.h"

/* create an euclidian vector				*/

Vector Vinit(double x,double y,double z,double t)
{
	Vector u;

	u.x=x;
	u.y=y;
	u.z=z;
	u.t=t;
	return u;
}

