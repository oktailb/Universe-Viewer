#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the error made by the researsh made in graph_C3 function	*/

double test_C3(Environnement *env, double this_age_universe)
{
  return (this_age_universe-env->AGE_CST*donne_integral(env, RonPdeR,0.0,1.0,env->quanta,env->graphC_prec));
}

