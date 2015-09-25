#include "uv.h"

Point *set_earth_proj(Environnement *env, Vector here,int i)
{
  Point *proj;
  
  proj = xmalloc(sizeof(*proj));
  switch(i)
    {
    case 0:
      if(env->friedman.k>=0.0)
	{
	  proj->x=Vscalar(env, here,env->direction1);
	  proj->y=Vscalar(env, here,env->direction4);
	}
      else
	{
	  proj->x=Vscalar(env, here,env->direction1);
	  proj->y=Vscalar(env, here,env->direction4)+2;
	}
      break;
    case 1:
      if(env->friedman.k>=0.0)
	{
	  proj->x=Vscalar(env, here,env->direction2);
	  proj->y=Vscalar(env, here,env->direction4);
	}
      else
	{
	  proj->x=Vscalar(env, here,env->direction2);
	  proj->y=Vscalar(env, here,env->direction4)+2;
	}
      break;
    case 2:
      if(env->friedman.k>=0.0)
	{
	  proj->x=Vscalar(env, here,env->direction3);
	  proj->y=Vscalar(env, here,env->direction4);
	}
      else
	{
	  proj->x=Vscalar(env, here,env->direction3);
	  proj->y=Vscalar(env, here,env->direction4)+2;
	}
      break;
    case 3:
      proj->x=Vscalar(env, here,env->direction1);
      proj->y=Vscalar(env, here,env->direction3);
      break;
    case 4:
      proj->x=Vscalar(env, here,env->direction1);
      proj->y=Vscalar(env, here,env->direction2);
      break;
    case 5:
      proj->x=Vscalar(env, here,env->direction2);
      proj->y=Vscalar(env, here,env->direction3);
      break;
    }
  return (proj);
}
