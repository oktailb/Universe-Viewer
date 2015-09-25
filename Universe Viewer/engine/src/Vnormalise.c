#include "uv.h"

/* normalize a vector					*/

Vector Vnormalize(Environnement *env, Vector u)
{
  if ((u.x!=0.0)
      ||(u.y!=0.0)
      ||(u.z!=0.0)
      ||(u.t!=0.0))
    return Vmult(u,1/Vnorme(env, u));
  else
    return env->null_vector;
}

