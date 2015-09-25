#include "uv.h"

Environnement	*init_uv(void)
{
  Environnement*	env;

  env = xmalloc(sizeof(*env));
  env->zoom_rate = 0.95;
  env->friedman.lambda = LAMBDA;
  env->friedman.omega = OMEGA;
  env->friedman.k = K;
  env->friedman.alpha = ALPHA;
  env->earth.x = 0.0;
  env->earth.y = 0.0;
  env->earth.z = 0.0;
  env->earth.t = 1.0;
  env->ascension = 0.0;
  env->declination = 0.0;
  env->beta=0.0;
  env->abacus_pas=0.1;
  env->abacus_max0=4.5;
  env->abacus_max=4.5;
  env->nb_causal_cell=1.0;
  env->abacus_prec=6;
  env->codistance_prec=3;
  env->graphP_lenght=200;
  env->choose_prec=1.0;
  env->graphA_lenght=200;
  env->graphC2_lenght=200;
  env->graphC3_lenght=600;
  env->graphC4_lenght=20;
  env->graphA_prec=6;
  env->graphC_prec=6;
  env->graphC2_eps=0.001;
  env->graphC3_eps=0.005;
  env->graphC4_eps=0.01;
  env->h=0.75;
  env->age_universe=AGE;
  env->new_age_universe=AGE;
  env->delta_age_universe=2.0;
  env->null_vector.x = 0.0;
  env->null_vector.y = 0.0;
  env->null_vector.z = 0.0;
  env->null_vector.t = 0.0;
  env->metric_vector.x = 1.0;
  env->metric_vector.y = 1.0;
  env->metric_vector.z = 1.0;
  env->metric_vector.t = 1.0;
  env->zr=1100.0;
  env->quanta=2;
  env->radians = 1;
  env->RadiusMax=2.0;
  env->OmegaMax=5.0;
  env->grapheC0g = grapheC0(env, env->OmegaMax);
  env->grapheC1g = grapheC1(env, env->OmegaMax);
  env->grapheC2g = grapheC2(env, env->OmegaMax);
  env->grapheC31g = grapheC3(env, env->OmegaMax, env->new_age_universe + env->delta_age_universe);
  env->grapheC32g = grapheC3(env, env->OmegaMax, env->new_age_universe - env->delta_age_universe);
  env->grapheC4g = grapheC4(env, env->OmegaMax);

  return (env);
}
