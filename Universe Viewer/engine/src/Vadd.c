#include "uv.h"

/* give the add of two vectors				*/

Vector Vadd(Vector u,Vector v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	u.t += v.t;
	return u;
}

