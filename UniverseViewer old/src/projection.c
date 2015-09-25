#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
/*
#include <Xm/Xm.h>
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "vector.h"
#include "quasar.h"
#include "projection.h"
#include "distance.h"

#define  PI 3.14159265398

extern Friedman friedman;
extern int data_lenght;
extern Vector null_vector;
extern Vector earth;
extern Vector direction1,direction2,direction3,direction4;
extern double ascension,declination,beta;

/* initialize the euclidian projection vectors			*/

void init_projection_vectors ()
{
	Quasar q;
	Vector P,Q1,Q2;

	if (friedman.k>0.0) direction4 = earth;
	else if(friedman.k<0.0) direction4 = earth;
	else if(friedman.k==0.0) direction4 = null_vector;

	q=Qinit(ascension,declination,0.0,PI/2);
	P=Vpos_curv(&q);
	Q1.x=sin(declination)*cos(ascension)*cos(beta)-sin(ascension)*sin(beta);
	Q1.y=sin(declination)*sin(ascension)*cos(beta)+cos(ascension)*sin(beta);
	Q1.z=-cos(declination)*cos(beta);
	Q1.t=0;
	Q2=Vproduct(P,Q1);
	direction1=P;
	direction2=Q1;
	direction3=Q2;				
		
}

/* give the value of the projection of u on d1 and d2 vectors	*/

Point projection (Vector u, Vector d1,Vector d2)
{
	register Point p;

	p.x = Vscalar(u,d1);
	p.y = Vscalar(u,d2);
	return p;
}

Point *set_quasar_proj(Vector *pos,int i)
{
	Point *proj;
	proj = (Point *) malloc(data_lenght*sizeof(Point));
	switch(i)
	{
	   case 0:
		calc_quasar_proj (pos,direction1,direction4,1,proj);
		break;
	   case 1:
		calc_quasar_proj (pos,direction2,direction4,1,proj);
		break;
	   case 2:
		calc_quasar_proj (pos,direction3,direction4,1,proj);
		break;
	   case 3:
		calc_quasar_proj (pos,direction1,direction3,0,proj);
		break;
	   case 4:
		calc_quasar_proj (pos,direction1,direction2,0,proj);
		break;
	   case 5:
		calc_quasar_proj (pos,direction2,direction3,0,proj);
		break;
	}
	return proj;		
}

Point set_earth_proj(Vector here,int i)
{
	Point proj;

	switch(i)
	{
		case 0:
			if(friedman.k>=0.0)
			{
				proj.x=Vscalar(here,direction1);
				proj.y=Vscalar(here,direction4);
			}
			else
			{
				proj.x=Vscalar(here,direction1);
				proj.y=Vscalar(here,direction4)+2;
			}
		break;
		case 1:
			if(friedman.k>=0.0)
			{
				proj.x=Vscalar(here,direction2);
				proj.y=Vscalar(here,direction4);
			}
			else
			{
				proj.x=Vscalar(here,direction2);
				proj.y=Vscalar(here,direction4)+2;
			}
		break;
		case 2:
			if(friedman.k>=0.0)
			{
				proj.x=Vscalar(here,direction3);
				proj.y=Vscalar(here,direction4);
			}
			else
			{
				proj.x=Vscalar(here,direction3);
				proj.y=Vscalar(here,direction4)+2;
			}
		break;
		case 3:
			proj.x=Vscalar(here,direction1);
			proj.y=Vscalar(here,direction3);
		break;
		case 4:
			proj.x=Vscalar(here,direction1);
			proj.y=Vscalar(here,direction2);
		break;
		case 5:
			proj.x=Vscalar(here,direction2);
			proj.y=Vscalar(here,direction3);
		break;
	}
	return proj;
}
