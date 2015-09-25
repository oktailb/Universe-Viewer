#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the codistance of a QSO    			  		*/

double earth_codistance(Environnement *env, Quasar *q)
{	
  int j;

  j=(int) (q->redshift/env->abacus_pas);
  return env->abacus[(int) (j)]+integral(env, ONEonPdeR, 1.0/(1.0+q->redshift),1.0/(1.0+(j*env->abacus_pas)), env->codistance_prec);
}


