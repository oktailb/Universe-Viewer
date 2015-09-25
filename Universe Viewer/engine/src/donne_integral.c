#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the integral of f between a and b with (b-a)/n step and prec for precision	*/


double donne_integral(Environnement *env, double (*f)(Environnement*, double), double a, double b, int n,int prec)
{
  int i;
  double da,db,pas,inte;
  
  pas=(double) (b-a)/n;
  inte=0.0;
  for(i=1;i<=n;i++)
    {
      da=(double) a+pas*(i-1);
      db=(double) a+pas*i;
      inte+=integral(env, *f,da,db,prec);	
    }
  
  return inte;
}

