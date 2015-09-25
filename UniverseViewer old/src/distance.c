#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
/*
#include <Xm/Xm.h>
*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "struct.h"
#include "distance.h"
#include "vector.h"
#include "quasar.h"
#include "projection.h"
#include "interface.h"

extern Friedman friedman;
extern double *abacus; 
extern double abacus_pas;
extern double abacus_max;
extern int abacus_prec;
extern int codistance_prec;
extern int graphP_lenght;
int bounced=0;
double graphPy_max,graphPx_max;


/*------------------------------------------------------------------------------------*/
/*
double ABS(double x)
{
	if(x<0) return -x;
	else return x;
}
*/
/*------------------------------------------------------------------------------------*/

/* give the distance on S3 between QSO q1 and QSO q2 			*/

double codistance(Quasar *q1,Quasar *q2)
  {	
	return integral(ONEonPdeR, 1.0/(1.0+q1->redshift), 1.0/(1.0+q2->redshift), abacus_prec);
  }

/*------------------------------------------------------------------------------------*/

/* give the codistance of a QSO    			  		*/

double earth_codistance(Quasar *q)
  {	
	int j;
	if(q!=0)
	{
		j=(int) (q->redshift/abacus_pas);
		return abacus[(int) (j)]+integral(ONEonPdeR, 1.0/(1.0+q->redshift),1.0/(1.0+(j*abacus_pas)), codistance_prec);
	}
	else
	{
		alerte("Memory allocation error for earth_codistance !!!\n");
		return -1;
	}
  }

/*------------------------------------------------------------------------------------*/

/* create an distance's abacus for redshift get from 0 to abacus_max	*/
/* by abacus_prec steps							*/

void init_abacus(void)
  {
	int j;
	int nmax;
	double da,db,inte;

	if (abacus!=NULL) free(abacus);
	nmax=(int) (abacus_max/abacus_pas)+1;
	abacus=(double*) calloc(nmax+1,sizeof(double));
	if(abacus)
	{
		abacus[0]=0.0;
		for(j=1;j<=nmax;j++)
		  {
			da=(double) 1.0/(1.0+(j*abacus_pas));
			db=(double) 1.0/(1.0+((j-1.0)*abacus_pas));
			inte=integral(ONEonPdeR,da,db,abacus_prec);
			abacus[j]=abacus[j-1]+inte;

		  }
	}
	else alerte("Memory allocation error for abacus ");
  }

/*------------------------------------------------------------------------------------*/

/* give the value of P(R)					*/

double PdeR(double R)
  {
	return (((friedman.lambda*R*R-friedman.k)*R
		+friedman.omega)*R+friedman.alpha);

  }

/*------------------------------------------------------------------------------------*/

/* give 1 if P(R)=0 on [xi,xf], 0 else				*/

int null_PdeR(double xi, double xf, double step)
  {
	int reponse;
	double R;

	reponse=0;
	for (R=xi;R<=xf;R+=step)
	  {
		if (PdeR(R)==0) reponse=1;
		break;
	  }
	return reponse;
  }


/*------------------------------------------------------------------------------------*/

/* give the value of 1/sqrt(P(R))  				*/

double ONEonPdeR(double R)
  {
	double pdr;

	pdr=PdeR(R);
	if(pdr>=0) return sqrt(1.0/pdr);
	else
	{
		bounced=1;
		return 0.0;
	}
  }

/*------------------------------------------------------------------------------------*/

/* give the value of 1/|sqrt(P(R))|  				*/

double AONEonPdeR(double R)
  {
	return sqrt(ABS(1.0/PdeR(R)));
  }

/*------------------------------------------------------------------------------------*/

/* give the value of R/sqrt(P(R))  				*/

double RonPdeR(double R)
  {
	return R/sqrt(PdeR(R));
  }

/*------------------------------------------------------------------------------------*/

/* give the value of the derivative of RonPdeR on Omega		*/

double DomRonPdeR(double R)
  {
	return -0.5*R*(R-R*R)/pow(PdeR(R),1.5);
  }

/*------------------------------------------------------------------------------------*/

/* give the value of the derivative of RonPdeR on Lambda		*/

double DlaRonPdeR(double R)
  {
	return -0.5*R*(pow(R,4)-R*R)/pow(PdeR(R),1.5);
  }

/*------------------------------------------------------------------------------------*/

/* give the value of integral on [a,b] by n step		*/

double integral(double (*f)(double), double a, double b, int n)
  {
	#define MAXIMUM 15
        register int j,k,e;
	double largeur,s,ee,kk,t[MAXIMUM];

	largeur=b-a;
	s=1.0;e=1;
	t[0]=0.5*( f(a) + f(b) );
	for(j=1;j<=n;j++)
	  {
		s=s*0.5;
		t[j]=0.0;
		for(k=1;k<=e;k++)
			t[j]=t[j]+ f(a+largeur*s*(2.0*k-1.0));
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

/*------------------------------------------------------------------------------------*/

/*  give a pointer of the values of 1/sqrt(P(R)) (use for graph)		*/

void grapheP(Point *graphP)
  {
	register int i;
	double denomin;
	//Point *graphP;

	graphPx_max=1.0;
	graphPy_max=0.0;
	//graphP=(Point*) calloc(graphP_lenght,sizeof(Point));
	if(graphP)
	{
	  for (i=0;i<graphP_lenght;i++)
	  {
		graphP[i].x=(double) i/(double) (graphP_lenght-1);
		denomin=PdeR(graphP[i].x);
		if (denomin>0)
			graphP[i].y=AONEonPdeR(graphP[i].x);
		else if (denomin==0) graphP[i].y=0;
		else graphP[i].y=-AONEonPdeR(graphP[i].x);
		if (abs(graphP[i].y)>graphPy_max) graphPy_max=abs(graphP[i].y);
	  }
	  if (graphPy_max!=0.0)
		for (i=0;i<graphP_lenght;i++)
		  {
			graphP[i].y=(double) (graphP[i].y/graphPy_max);
		  }
	}
	else alerte("Memory allocation error for integrand plot ");
	//return graphP;
  }

