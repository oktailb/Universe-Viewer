#include "uv.h"

/* initialize the euclidian projection vectors			*/

void init_projection_vectors (Environnement *env)
{
  Quasar *q;
  Vector P,Q1,Q2;
  
  if (env->friedman.k>0.0)
    env->direction4 = env->earth;
  else
    if(env->friedman.k<0.0)
      env->direction4 = env->earth;
    else
      if(env->friedman.k==0.0)
	env->direction4 = env->null_vector;
  q = Qinit(env->ascension,env->declination,0.0,M_PIl/2);
  P=Vpos_curv(q);
  Q1.x=sin(env->declination)*cos(env->ascension)*cos(env->beta)-sin(env->ascension)*sin(env->beta);
  Q1.y=sin(env->declination)*sin(env->ascension)*cos(env->beta)+cos(env->ascension)*sin(env->beta);
  Q1.z=-cos(env->declination)*cos(env->beta);
  Q1.t=0;
  Q2=Vproduct(P,Q1);
  env->direction1=P;
  env->direction2=Q1;
  env->direction3=Q2;
}

