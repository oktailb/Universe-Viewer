#include "uv.h"

/* give an euclidian vector in cas of k=0 of a QSO */

Vector Vnul_curv (Environnement *env, Quasar *q)
{
  Vector u;
  
  u.t = 0;
  u.z = q->tau/env->distance_max;
  u.y = u.z*cos(q->declination);
  u.z *= sin(q->declination);	
  u.x = u.y*cos(q->ascension);
  u.y *= sin(q->ascension);
  return u;
}


