#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
/*
#include <Xm/Xm.h>
*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "struct.h"
#include "distance.h"
#include "vector.h"
#include "quasar.h"
#include "projection.h"
#include "space.h"

#define  PI 3.14159265398

extern double *abacus,*abacusV;
extern double abacus_pas,abacus_max0,abacus_max,abacus_prec;
extern double abacusVmax;
extern Friedman friedman;

/*-------------------------------------------------------------------------------------------------*/

/* Give an abacus for the homogen volum					*/

void init_abacusV(double Zmax)
  {
	register int j;
	int nmax,Nmax;
	double inte;

	abacus_max=abacus_max0;
	nmax=(int) (abacus_max/abacus_pas)+1;
	Nmax=(int) (Zmax/abacus_pas)+1;
	if (Nmax>nmax) 
	  {
		abacus_max=Zmax;
		init_abacus();
	  }
	if (Nmax<nmax) 
	  {
		Nmax=nmax;
		init_abacus();
	  }
	if (abacusV!=NULL) free(abacusV);
	abacusV=(double*) calloc(Nmax+1,sizeof(double));
	if(abacusV)
	{
		abacusV[0]=0.0;
		for(j=1;j<=Nmax;j++)
		  {
			inte=sqrt(ABS(friedman.k))*abacus[j];
			if (friedman.k>0.0)
			  abacusV[j]=(2*inte-sin(2*inte))/(4*pow(friedman.k,1.5));
			if (friedman.k==0.0)
			  abacusV[j]=inte*inte*inte/3.0;
			if (friedman.k<0.0)
			 abacusV[j]=(-2*inte+sinh(2*inte))/(4*pow(-friedman.k,1.5));
		  }

	}
	else printf("Memory allocation error for abacusV ");

  }

/*-------------------------------------------------------------------------------------------------*/

/* Give the redshift corresponding to a given volum				*/


double donne_z(double V)
  {
	int j,nmax;
	double Z;

	Z=0;
	nmax=(int) (abacus_max/abacus_pas)+1;
	for(j=1;j<=nmax;j++)
	  {
		if (V>=abacusV[j] && abacusV[j+1]>V)
		  {
			Z=j*abacus_pas+
			  ((V-abacusV[j])*abacus_pas/(abacusV[j+1]-abacusV[j]));
		  }
	  }
	
	return Z;
  }

/*-------------------------------------------------------------------------------------------------*/

/* Give the volum of a given redshift						*/


double donne_V(double Z)
  {
	double inte=0,V=0,nmax;
	int i,rajout=0;

	nmax=(int) (abacus_max/abacus_pas)+1;
	for(i=0;i<=nmax;i++)
	  if (Z>=i*abacus_pas && Z<(i+1)*abacus_pas)
	    {
		inte=sqrt(ABS(friedman.k))*abacus[i];
		rajout=i;
		break;
	    }	 
	  inte+=sqrt(ABS(friedman.k))*integral(ONEonPdeR,1.0/(1.0+Z),1.0/(1.0+(rajout*abacus_pas)),abacus_prec);

	if (friedman.k>0.0)
	  V=(2*inte-sin(2*inte))/(4*pow(friedman.k,1.5));
	if (friedman.k==0.0)
	  V=inte*inte*inte/3.0;
	if (friedman.k<0.0)
	  V=(-2*inte+sinh(2*inte))/(4*pow(-friedman.k,1.5));

	return V;
	
  }

/*-------------------------------------------------------------------------------------------------*/

/* Create an isotrop an homogen set of qusars					*/


void isotrope(int nbre,double Zmax,double Zmin,double ra0,double d0,double beta,Quasar *q)
  {
	int i;
	double xsi,Vz,rax,dx,Zx,gamma,teta;
	double Vmax,Vmin;


	if(q!=NULL) free(q);
	//q=(Quasar *) calloc(nbre, sizeof(struct s_quasar));
	if(q)
	{
	  init_abacusV(Zmax);
  	  Vmax=donne_V(Zmax);
	  Vmin=donne_V(Zmin);
	  for(i=0;i<nbre;i++)
	  {
		xsi=((double) rand()/RAND_MAX);
		Vz=xsi*(Vmax-Vmin)+Vmin;
		Zx=donne_z(Vz);
		xsi=((double) rand()/RAND_MAX);
		gamma=acos( (1.0-cos(beta))*xsi+cos(beta) );
		teta=((double) rand()/RAND_MAX)*2.0*PI;
		rax=ra0+( sin(gamma)*sin(teta) )/cos(d0);
		dx=d0+cos(teta)*sin(gamma);
		q[i].ascension=rax;
		q[i].declination=dx;
		q[i].redshift=Zx;
	  }
	}
	else printf("Can not allocate memory for isotropics quasars ");
  }
