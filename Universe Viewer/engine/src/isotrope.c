#include "uv.h"


/*-------------------------------------------------------------------------------------------------*/

/* Create an isotrop an homogen set of qusars					*/


Quasar *isotrope(Environnement *env, int nbre,double Zmax,double Zmin,double ra0,double d0,double beta)
{
  int i;
  double xsi,Vz,rax,dx,Zx,gamma,teta;
  double Vmax,Vmin;
  Quasar *q;
  
  q = xmalloc(nbre * sizeof(*q));
  init_abacusV(env, Zmax);
  Vmax=donne_V(env, Zmax);
  Vmin=donne_V(env, Zmin);
  for(i=0;i<nbre;i++)
    {
      xsi=((double) rand()/RAND_MAX);
      Vz=xsi*(Vmax-Vmin)+Vmin;
      Zx=donne_z(env, Vz);
      xsi=((double) rand()/RAND_MAX);
      gamma=acos( (1.0-cos(beta))*xsi+cos(beta) );
      teta=((double) rand()/RAND_MAX)*2.0*M_PIl;
      rax=ra0+( sin(gamma)*sin(teta) )/cos(d0);
      dx=d0+cos(teta)*sin(gamma);
      q[i].ascension=rax;
      q[i].declination=dx;
      q[i].redshift=Zx;
    }
  return (q);
}
