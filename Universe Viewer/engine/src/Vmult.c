#include "uv.h"

/* give the product of a vector by a scalar		*/

Vector Vmult(Vector u,double lambda)
{
	u.x *= lambda;       
	u.y *= lambda;       
	u.z *= lambda;       
	u.t *= lambda;       
        return u;
}

