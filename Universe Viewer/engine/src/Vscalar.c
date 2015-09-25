#include "uv.h"

/* give the scalar product of two vectors		*/

double		Vscalar(Environnement *env, Vector u,Vector v)
{
  double	p;
  double	curv;
  
  if (env->friedman.k > 0)
    curv = 1;
  else
    if (env->friedman.k < 0)
      curv =- 1;
    else
      curv = 0;
  p = u.x*v.x
    + u.y*v.y
    + u.z*v.z
    + u.t*v.t*curv;
  return (p);
}
