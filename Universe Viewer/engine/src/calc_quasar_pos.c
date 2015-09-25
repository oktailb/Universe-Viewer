#include "uv.h"

/*
 * give the euclidian position of all QSO
 *
 */

Vector*		calc_quasar_pos(Environnement *env, Quasar *q)
{
  Vector	*v;
  int		count;
  
  if(q)
    {
      v = xmalloc(env->data_lenght*sizeof(*v));
      if (v)
	{
	  if (env->friedman.k>0.0)
	    for (count=0;count < env->data_lenght;count++)
	      v[count] = Vpos_curv (q+count);
	  if (env->friedman.k<0.0)
	    for (count=0;count < env->data_lenght;count++)
	      v[count] = Vneg_curv (q+count);
	  if (env->friedman.k==0.0)
	    for (count=0;count < env->data_lenght;count++)
	      v[count] = Vnul_curv (env, q+count);
	}
      return (v);
    }
  return (NULL);
}
