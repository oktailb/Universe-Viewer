#include "uv.h"

Point	*calc_quasar_proj (Environnement *env, Vector *v, Vector d1, Vector d2, int offset)
{
  Point	*p;
  int	count;

  if (env->friedman.k >= 0.0)
    offset = 0;
  p = xmalloc(env->data_lenght * sizeof(*p));
  for(count = 0; count < env->data_lenght; count++)
    {
      p[count].x = Vscalar(env, v[count], d1);
      p[count].y = Vscalar(env, v[count], d2) + offset * 2;
    }
  return (p);
}
