#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the line k=0 in graph Lambda vs Omega				*/

Point *grapheC0(Environnement *env, double Omax)
{
  Point	*graphC0;

  env->graphCx_max=Omax;
  env->graphCy_max=Omax;
  graphC0 = xmalloc(sizeof(*graphC0));
  graphC0[0].x=env->friedman.omega/Omax;
  graphC0[0].y=env->friedman.lambda/Omax;
  return (graphC0);
}
