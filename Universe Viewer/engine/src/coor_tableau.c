#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the position in pointer p of the QSO see on Point q		*/

int coor_tableau(Environnement *env, Point *p, int lenght, Point q)
{
  int i,reponse;
  int essai=5;
  double dx,dy;
  
  while(essai)
    {
      reponse=-1;
      for(i=0;i<lenght;i++)
	{
	  dx=q.x-p[i].x; if(dx<0) dx=-dx;
	  dy=q.y-p[i].y; if(dy<0) dy=-dy;
	  if ((dx<=env->choose_prec) && (dy<=env->choose_prec))
	    {
	      if (reponse>-1)
		{
		  reponse=-2;
		  break;
		}
	      else reponse=i;
	    }
	}
      --essai;
      if (reponse==-1)
	env->choose_prec*=2;
      else 
	if (reponse==-2)
	  env->choose_prec/=2;
      else essai=0;
    }
  return reponse;
}
