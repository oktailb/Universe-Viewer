#include "uv.h"

Point *set_quasar_proj(Environnement *env, Vector *pos,int i)
{
  Point *proj;

  START;
  proj = NULL;
  switch(i)
    {
    case 0:
      proj = calc_quasar_proj (env, pos,env->direction1,env->direction4,1);
      break;
    case 1:
      proj = calc_quasar_proj (env, pos,env->direction2,env->direction4,1);
      break;
    case 2:
      proj = calc_quasar_proj (env, pos,env->direction3,env->direction4,1);
      break;
    case 3:
      proj = calc_quasar_proj (env, pos,env->direction1,env->direction3,0);
      break;
    case 4:
      proj = calc_quasar_proj (env, pos,env->direction1,env->direction2,0);
      break;
    case 5:
      proj = calc_quasar_proj (env, pos,env->direction2,env->direction3,0);
      break;
    }
  return proj;		
}

