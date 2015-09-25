#include "uv.h"

/* give the norme of a vector				*/

double Vnorme(Environnement *env, Vector u)
{
  return sqrt(ABS(Vscalar(env, u,u)));
}

