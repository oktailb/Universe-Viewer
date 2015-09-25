#include "uv.h"

/*------------------------------------------------------------------------------------*/
/* give the value of integral on [a,b] by n step		*/

double integral(Environnement *env, double (*f)(Environnement*, double), double a, double b, int n)
{
#define MAXIMUM 15
  register int j,k,e;
  double largeur,s,ee,kk,t[MAXIMUM];
  
  largeur=b-a;
  s=1.0;e=1;
  t[0]=0.5*( f(env, a) + f(env, b) );
  for(j=1;j<=n;j++)
    {
      s=s*0.5;
      t[j]=0.0;
      for(k=1;k<=e;k++)
	t[j]=t[j]+ f(env, a+largeur*s*(2.0*k-1.0));
      t[j]=s*t[j]+0.5*t[j-1];
      e=e*2;
    }
  ee=1.0;kk=1.0;
  for(j=1;j<=n;j++)
    {
      ee=ee*4.0;
      kk=kk*(ee-1.0);
      for(k=0;k<=n-j;k++)
	t[k]=ee*t[k+1]-t[k];
    }
  return (largeur*t[0]/kk);
}
