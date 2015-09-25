#include "uv.h"

Point *grapheA2(Environnement *env)
{
  Point	*lineA;

  lineA = xmalloc(sizeof(*lineA) * 3);
  lineA[0].x=0.0;
  lineA[0].y=1.0/env->graphAy_max;
  lineA[1].x=env->inte/env->graphAx_max;
  lineA[1].y=1.0/env->graphAy_max;
  lineA[2].x=env->inte/env->graphAx_max;
  lineA[2].y=0.0;
  return (lineA);
}

