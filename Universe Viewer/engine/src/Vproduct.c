#include "uv.h"

/* give the vectorial product of two vectors		*/

Vector Vproduct(Vector u,Vector v)
{
	Vector w;

	w.x=u.y*v.z-u.z*v.y;
	w.y=u.z*v.x-u.x*v.z;
	w.z=u.x*v.y-u.y*v.x;
	w.t=0;
	return w;	
}

