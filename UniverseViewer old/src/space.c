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

extern double abacus_max,abacus_pas;
extern double *abacus;
extern double nb_causal_cell;
extern double choose_prec;
extern int graphA_prec,graphC_prec;
extern int graphA_lenght,graphC1_lenght,graphC2_lenght,graphC3_lenght,graphC4_lenght;
extern double graphC2_eps,graphC3_eps,graphC4_eps;
extern Friedman friedman;
extern double AGE_CST;
extern double age_universe,new_age_universe;
extern int disfunction;

double zr=1100.0;

double graphAx_max,graphAy_max;
double graphCx_max,graphCy_max;
double inte;
int quanta=2;
static char buffer[256];
Friedman old_friedman;

/*------------------------------------------------------------------------------------*/

/* Give the position in pointer p of the QSO see on Point q		*/

int coor_tableau(Point *p, int lenght, Point q)
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
			if ((dx<=choose_prec) && (dy<=choose_prec))
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
		if (reponse==-1) choose_prec*=2;
		else if (reponse==-2) choose_prec/=2;
		else essai=0;
	  }
	return reponse;

  }

/*------------------------------------------------------------------------------------*/

/* Give the arc cosh of cosh(teta)						*/

double ACOSH(double chteta)
  {
	double shteta,teta;

	shteta=sqrt(1+chteta*chteta);
	teta=log(chteta+shteta);
	
	return teta;
  }


/*------------------------------------------------------------------------------------*/

/* Give the distance between QSO see by Vectors v1 and v2		*/

double inter_distance(Vector *v1,Vector *v2)
  {
	double ps=0,reponse=0;

	if (friedman.k>0.0)
	  {
		ps=Vscalar(*v1,*v2);
		reponse=acos(ps);
	  }
	else if (friedman.k<0.0)
	  {
		ps=Vscalar(*v1,*v2);
		reponse=ACOSH(ABS(ps));
	  }
	else if (friedman.k==0.0)
		reponse=Vnorme(Vadd(*v1,Vmult(*v2,-1.0)));
/*	printf("distance: %lf %lf\n",ABS(ps),reponse);
*/	return reponse;

  }

/*------------------------------------------------------------------------------------*/

/* Make the values of R(t)						*/ 

void grapheA1(double Rmax,Point *graphA)
  {
	int i;
	double r,yinte=0;

	graphAx_max=0.0;
	graphAy_max=Rmax;

	if (Rmax< 1) inte=AGE_CST* integral(RonPdeR,0.0,1.0,graphA_prec);
	if (graphA)
	  {
		r=Rmax/(double) (graphA_lenght-1);
		graphA[0].x=0;
		graphA[0].y=0;
		for(i=1;i<graphA_lenght;i++)
		  {
			graphA[i].y=graphA[i-1].y+r;
			graphA[i].x=graphA[i-1].x+AGE_CST*integral(RonPdeR,
					graphA[i-1].y,graphA[i].y,graphA_prec);
			if (graphA[i].y<=1)
			  { 
				inte=graphA[i].x; 
				yinte=graphA[i].y;
			  }
			if (graphA[i].x>graphAx_max) graphAx_max=graphA[i].x;
			if(!i%10) printf("%d ,x: %lf || y: %lf\n",i,graphA[i].x,graphA[i].y);
		  }
		inte+=AGE_CST*integral(RonPdeR,yinte,1.0,graphA_prec);
		age_universe=inte;
/*		printf("age universe: %lf\n",age_universe);
*/		for(i=1;i<graphA_lenght;i++)
		  {
			graphA[i].y=(double) graphA[i].y/(double) graphAy_max;
			graphA[i].x=(double) graphA[i].x/(double) graphAx_max;
		  }

	  }
	else printf("Memory allocation error for Radius vs time plot ");

}

void grapheA2(double Rmax,Point *lineA)
{


	if(lineA)
	{
		lineA[0].x=0.0;
		lineA[0].y=1.0/graphAy_max;
		lineA[1].x=inte/graphAx_max;
		lineA[1].y=1.0/graphAy_max;
		lineA[2].x=inte/graphAx_max;
		lineA[2].y=0.0;
	}
	else printf("Memory allocation error for current time plot ");

  }

/*------------------------------------------------------------------------------------*/

/* Give the line k=0 in graph Lambda vs Omega				*/

void grapheC0(double Omax,Point *graphC0)
  {

	graphCx_max=Omax;
	graphCy_max=Omax;

	if(graphC0)
	{
		graphC0[0].x=friedman.omega/Omax;
		graphC0[0].y=friedman.lambda/Omax;
	}
	else printf("Memory allocation error for current Omega/Lambda plot ");
  }

void grapheC1(double Omax,Point *graphC1)
  {
	if(graphC1)
	{
		graphC1[0].x=0.0;
		graphC1[0].y=(1.0-friedman.alpha)/Omax;
		graphC1[1].x=1.0/Omax;
		graphC1[1].y=-friedman.alpha/Omax;
	}
	else printf("Memory allocation error for k=0 plot ");
  }

/*------------------------------------------------------------------------------------*/

/* Give the error made by the researsh made in graph_C2 function	*/

double test_C2(double a, double k, double l, double o)
  {
	return ( 1.5*sqrt(3*l)*(o*sqrt(k)+a*sqrt(3*l))-(k*k) );
  }

/*------------------------------------------------------------------------------------*/

/* Give the value of derivative on Omega of equation in test_C2 function*/

double derivo(double a, double k, double l, double o)
{
	return 1.5*sqrt(3*l*k)+2.25*o*l/sqrt(3*k*l)-2*k;
}

/*------------------------------------------------------------------------------------*/

/* Give the value of derivative on Lambda of equation in test_C2 function*/


double derivl(double a, double k, double l, double o)
  {
	return 2.25*o*(l+k)/sqrt(3*k*l)+4.5*a-2*k;
  }

/*------------------------------------------------------------------------------------*/

/* Give the value of Lambda made by the equation in test_C2 function 	*/

void grapheC2(double Omax,Point *graphC2)
  {
	int i;
	double r,o0,k0,a0,l0,dom,dl,del;

	disfunction=0;

	a0=friedman.alpha;
	if (graphC2)
	  {
		graphC2[0].x=0;
		graphC2[0].y=1-a0;
		l0=0;
		o0=0.01;
		r=Omax/(double) (graphC2_lenght-1);
		while(l0<=10)
		  {
			o0=0.01;
			l0+=r;
			k0=-1+o0+a0+l0;
			if (k0<=0) continue;
/*			printf("k0=%lf o0=%lf l0=%lf\n",k0,o0,l0);*/
			if (ABS(test_C2(a0,k0,l0,o0))<graphC2_eps)
			  {
				graphC2[1].x=o0;
				graphC2[1].y=l0;
/*			 	printf("x[0]= %lf || y[0]= %lf\n",graphC2[0].x,graphC2[0].y);*/	
				break;
			  }
		  }
		if (l0<=10)
		  {
			for(i=2;i<graphC2_lenght;i++)
			  {
				k0=-1+o0+a0+l0;
				dom=derivo(a0,k0,l0,o0);
				dl=derivl(a0,k0,l0,o0);
				del=(double) (-r*dom)/(double) dl;
				o0+=r;
				l0+=del;
				graphC2[i].x=o0;
				graphC2[i].y=l0;
			  }
			for(i=0;i<graphC2_lenght;i++)
			  {
				graphC2[i].x/=Omax;
				graphC2[i].y/=Omax;
			  }
		  }
		else 
		  {
			disfunction=1;
			printf(" This model is not available ");
		  }
	  }
	else printf("Memory allocation error for limit plot ");

  }

/*------------------------------------------------------------------------------------*/

/* Give the error made by the researsh made in graph_C3 function	*/

double test_C3(double this_age_universe)
  {
	return (this_age_universe-AGE_CST*donne_integral(RonPdeR,0.0,1.0,quanta,graphC_prec));
  }

/*------------------------------------------------------------------------------------*/

/* Give the values of Omega et Lambda which made the universe age right	*/

void grapheC3(double Omax, double this_age_universe,Point *graphC3)
  {
	int i,trouve;
	double r,o0,k0,a0,l0,dom,dl,del,val_test_C3,old_graphC3_eps;

	old_friedman=friedman;
	old_graphC3_eps=graphC3_eps;
	a0=friedman.alpha;
	if (graphC3)
	  {
		l0=0.0;
		o0=0.01-0.05;
		trouve=0;
		r=Omax/(double) (graphC3_lenght-1);
		while(o0<=Omax && trouve==0)
		{
		o0+=0.05;
		l0=0.0;
		graphC3_eps*=1.5;
		while(l0<=Omax)
		  {
			l0+=r;
			k0=-1+o0+a0+l0;
			friedman.omega=o0;
			friedman.lambda=l0;
			friedman.k=k0;
			val_test_C3=test_C3(this_age_universe);
			if (ABS(val_test_C3)<graphC3_eps)
			  {
				graphC3[0].x=o0;
				graphC3[0].y=l0;
				trouve=1;
				break;
			  }
		  }
		}
		if (trouve==1)
		  {
			for(i=1;i<graphC3_lenght;i++)
			  {
				k0=-1+o0+a0+l0;
				friedman.omega=o0;
				friedman.lambda=l0;
				friedman.k=k0;
				dom=donne_integral(DomRonPdeR,0.0,1.0,quanta,graphC_prec);
				dl=donne_integral(DlaRonPdeR,0.0,1.0,quanta,graphC_prec);
				del=(double) -(r*dom)/(double) dl;
				o0+=r;
				l0+=del;
				graphC3[i].x=o0;
				graphC3[i].y=l0;
			  }
			for(i=0;i<graphC3_lenght;i++)
			  {
				graphC3[i].x/=Omax;
				graphC3[i].y/=Omax;
			  }
		  }
		else
		  {
			disfunction=1;
			sprintf(buffer,"Could not compute constant age curve for age=%lf",this_age_universe);
			printf(buffer);
		  } 
	  }
	else printf("Memory allocation error for constant age plot ");
	friedman=old_friedman;
	graphC3_eps=old_graphC3_eps;

  }

/*------------------------------------------------------------------------------------*/

/* Give the error made by the researsh made in graph_C4 function	*/

double test_C4(double cell, double CELL)
  {
	double valeur;

	valeur=cell-CELL;
	return valeur;

  }


/*------------------------------------------------------------------------------------*/

/* Give the number of causal cell of a model 				*/

double donne_cell(void)
  {
	double Zr,tc,tr,tetac=0,cell;


	Zr=1100.0;
	tc=sqrt(ABS(friedman.k))*integral(ONEonPdeR,0.0,1.0/(double) (1.0+Zr),graphC_prec);
	tr=sqrt(ABS(friedman.k))*donne_integral(ONEonPdeR,1.0/(double) (1.0+Zr),1.0,10,graphC_prec);
	if (friedman.k>0.0)
		tetac=2*sin(sin(tc)/sin(tr));
	else if (friedman.k==0.0)
		tetac=2*sin(tc/tr);
	else if (friedman.k<0.0)
		tetac=2*sin(sinh(tc)/sinh(tr));
	cell=sqrt(2)/(1-cos(tetac));

	return cell;


  }

/*------------------------------------------------------------------------------------*/

/* this function is the pure test procedure to put out causal cell curve	*/


void graphC4(double Omax,Point *graphC4)
  {
	int i;

	if (graphC4)
	  {
		for(i=0;i<graphC4_lenght;i++)
		{
			graphC4[i].x=0.0;
			graphC4[i].y=0.0;
		}
	  }
  }


/*------------------------------------------------------------------------------------*/

/* Give the values of Omega et Lambda which a right number of causal cells.	*/

void grapheC4(double Omax,Point *graphC4)
  {
	int i,j,taille,trouve;
	double r,o0,k0,a0,l0;
	double cell,erreur,pas,old_r;

	zr=1100.0;
	old_friedman=friedman;
	a0=friedman.alpha;
	if (graphC4)
	  {
		taille=(int) (Omax/ (graphC4_eps))+1;
		pas=(double) (Omax/graphC4_lenght);
		r=2*graphC4_eps;
		old_r=r;
		o0=0.01-pas;
		for(j=0;j<graphC4_lenght;j++)
		{
		o0+=pas;
		l0=0.0;
		trouve=0;
		r=old_r;
		while(trouve==0 && r>(old_r/8.0))
		{
		l0=0.0;
		r=r/2.0;
		while( l0<=Omax)
		  {
			l0+=r;
			k0=-1+o0+a0+l0;
			friedman.omega=o0;
			friedman.lambda=l0;
			friedman.k=k0;
			if (k0>0.0)
			  {
				cell=donne_cell();
				erreur=ABS(test_C4(cell, nb_causal_cell));
				if (erreur<=graphC4_eps)
				  {
				graphC4[j].x=o0;
				graphC4[j].y=l0;
				trouve=1;
				break;
				  }
				else if (j>0)
				  {
				graphC4[j].x=graphC4[j-1].x;
				graphC4[j].y=graphC4[j-1].y;
				  }
				else
				  {
				graphC4[j].x=o0;
				graphC4[j].y=l0;
				  }


			  }
		  }
		 }
		}

		for(i=0;i<graphC4_lenght;i++)
		  {
			graphC4[i].x/=Omax;
			graphC4[i].y/=Omax;
		  }

	  }
	else printf("Memory allocation error for causal plot ");
	friedman=old_friedman;
  }

/*------------------------------------------------------------------------------------*/

/* Give the integral of f between a and b with (b-a)/n step and prec for precision	*/


double donne_integral(double (*f)(double), double a, double b, int n,int prec)
  {
	int i;
	double da,db,pas,inte;

	pas=(double) (b-a)/n;
	inte=0.0;
	for(i=1;i<=n;i++)
	  {
		da=(double) a+pas*(i-1);
		db=(double) a+pas*i;
		inte+=integral(*f,da,db,prec);	
	  }

	return inte;
  }

/*------------------------------------------------------------------------------------*/

/* this function is the second test procedure for causal cell curve		*/


void grC4(double Omax,Point *graphC4)
  {
	int i;
	double zr,r,o0,k0,a0,l0;
	double cell,erreur,old_erreur,pas;

	zr=1100.0;
	printf("C4: c'est parti ");
	old_friedman=friedman;
	a0=friedman.alpha;
	if (graphC4)
	  {
		r=Omax/(double) (graphC4_lenght);
		o0=0.01-r;
		for(i=0;i<graphC4_lenght;i++)
		{
		o0+=r;
		pas=0.05;
		old_erreur=0.0;
		erreur=10.0;
		printf("o0=%lf\n",o0);
		l0=0.0;
		while(l0<=Omax && ABS(erreur)>graphC4_eps)
		  {
			l0+=pas;
			k0=-1+o0+a0+l0;
			friedman.omega=o0;
			friedman.lambda=l0;
			friedman.k=k0;
			if (k0>0.0)
			  {
				cell=donne_cell();
				erreur=test_C4(cell,nb_causal_cell);

				printf("cell=%lf  || erreur= %lf   ||  old=  %lf\n",
						cell,erreur,old_erreur);
				printf("pas=%lf  || l0= %lf \n",pas,l0);

				if (erreur*old_erreur<0)
				  {
				  l0=l0-pas;
				  pas=pas/10.0;
				  break;
				  }
				old_erreur=erreur;
				
			  }
		  }
		if (ABS(erreur)<=graphC4_eps)
			{
				graphC4[i].x=o0;
				graphC4[i].y=l0;
				printf("OK, j'ai trouve le %d  %lf point.\n",i,erreur);
			 	printf("x[i]= %lf || y[i]= %lf\n",graphC4[i].x,graphC4[i].y);

			}
		else if (i>0)
			{
				graphC4[i].x=graphC4[i-1].x;
				graphC4[i].y=graphC4[i-1].y;
				printf("PLANTE");
			}
		else 
			{
				graphC4[i].x=0.0;
				graphC4[i].y=0.0;
				printf("PLANTE");
			}

		}
		for(i=0;i<graphC4_lenght;i++)
		  {
			graphC4[i].x/=Omax;
			graphC4[i].y/=Omax;
		  }


	  }
}
