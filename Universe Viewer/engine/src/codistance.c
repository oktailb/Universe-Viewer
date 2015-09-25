#include "uv.h"

/* give the distance on S3 between QSO q1 and QSO q2 			*/

double codistance(Environnement* env, Quasar *q1,Quasar *q2)
{	
  return integral(env, ONEonPdeR, 1.0/(1.0+q1->redshift), 1.0/(1.0+q2->redshift), env->abacus_prec);
}
