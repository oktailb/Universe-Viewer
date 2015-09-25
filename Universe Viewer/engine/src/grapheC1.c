#include "uv.h"

Point *grapheC1(Environnement *env, double Omax)
{
  Point	*graphC1;

  graphC1 = xmalloc(sizeof(*graphC1) * 2);
  graphC1[0].x=0.0;
  graphC1[0].y=(1.0-env->friedman.alpha)/Omax;
  graphC1[1].x=1.0/Omax;
  graphC1[1].y=-env->friedman.alpha/Omax;
  return (graphC1);
}
