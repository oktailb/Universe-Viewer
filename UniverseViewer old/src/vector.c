/*							*/
/*		OPERATIONS SUR LES VECTEURS	  	*/
/*______________________________________________________*/
 
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

extern double distance_max;
extern Friedman friedman; 

Vector null_vector={0.0,0.0,0.0,0.0};
Vector metric_vector={1.0,1.0,1.0,1.0};

/* create an euclidian vector				*/

Vector Vinit(double x,double y,double z,double t)
{
	Vector u;

	u.x=x;
	u.y=y;
	u.z=z;
	u.t=t;
	return u;
}

/* give the scalar product of two vectors		*/

double Vscalar(Vector u,Vector v)
{
	double p,curv;

	if (friedman.k>0) curv=1;
	else if (friedman.k<0) curv=-1;
	else curv=0;
	p= u.x*v.x
              +u.y*v.y
              +u.z*v.z
              +u.t*v.t*curv;
	return p;
} 

/* give the norme of a vector				*/

double Vnorme(Vector u)
{
	return sqrt(ABS(Vscalar(u,u)));
}

/* normalize a vector					*/

Vector Vnormalize(Vector u)
{
	if ((u.x!=0.0)
	  ||(u.y!=0.0)
	  ||(u.z!=0.0)
	  ||(u.t!=0.0))
	     return Vmult(u,1/Vnorme(u));
        else return null_vector;
}

/* give the vectorial product of two vectors		*/

Vector Vproduct(Vector u,Vector v)
{
	Vector w;

	w.x=u.y*v.z-u.z*v.y;
	w.y=u.z*v.x-u.x*v.z;
	w.z=u.x*v.y-u.y*v.x;
	w.t=0;
	return w;	
}

/* give the add of two vectors				*/

Vector Vadd(Vector u,Vector v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	u.t += v.t;
	return u;
}

/* give the product of a vector by a scalar		*/

Vector Vmult(Vector u,double lambda)
{
	u.x *= lambda;       
	u.y *= lambda;       
	u.z *= lambda;       
	u.t *= lambda;       
        return u;
}

/* give an euclidian vector in cas of k>0 of a QSO	*/

Vector Vpos_curv (Quasar *q)
{
	Vector u;

	u.t = cos(q->tau);
	u.z = sin(q->tau);
	u.y = u.z*cos(q->declination);
	u.z *= sin(q->declination);	
	u.x = u.y*cos(q->ascension);
	u.y *= sin(q->ascension);

/*	printf("%lf {} %lf {} %lf\n",q->tau,q->ascension,q->declination);
	printf("%lf || %lf || %lf || %lf\n",u.x,u.y,u.z,u.t);
*/
	return u;
}

/* give an euclidian vector in cas of k=0 of a QSO			*/

Vector Vnul_curv (Quasar *q)
{
	Vector u;

	u.t = 0;
	u.z = q->tau/distance_max;
	u.y = u.z*cos(q->declination);
	u.z *= sin(q->declination);	
	u.x = u.y*cos(q->ascension);
	u.y *= sin(q->ascension);

/*	printf("%lf {} %lf {} %lf\n",q->tau,q->ascension,q->declination);
	printf("%lf || %lf || %lf || %lf\n",u.x,u.y,u.z,u.t);
*/
	return u;
}


/* give an euclidian vector in cas of k<0 of a QSO			*/

Vector Vneg_curv (Quasar *q)
{
	Vector u;

	u.t = cosh(q->tau);
	u.z = sinh(q->tau);
	u.y = u.z*cos(q->declination);
	u.z *= sin(q->declination);	
	u.x = u.y*cos(q->ascension);
	u.y *= sin(q->ascension);
	return u;
}

/* main test function */
/*
 main ()
{
	Vector u={1.0,2.0,3.0,4.0};
	Vector v={0.0,1.0,0.0,1.0};
	Vector w;

	printf ("scalar u.v %lf\n",Vscalar(u,v));
	printf ("scalar u.u %lf\n",Vscalar(u,u));
	printf ("scalar v.v %lf\n",Vscalar(v,v));
	printf ("norme u %lf v %lf\n",Vnorme(u),Vnorme(v));
	w=Vnormalize(u);
	printf ("normalize u %lf %lf %lf %lf\n",w.x,w.y,w.z,w.t);
	printf ("norme w %lf %\n",Vnorme(w));
	w=Vnormalize(v);
	printf ("normalize v %lf %lf %lf %lf\n",w.x,w.y,w.z,w.t);
	printf ("norme w %lf %\n",Vnorme(w));
	w=Vproduct(u,v);
	printf ("product uxv %lf %lf %lf %lf\n",w.x,w.y,w.z,w.t);
	w=Vadd(u,v);
	printf ("add u+v %lf %lf %lf %lf\n",w.x,w.y,w.z,w.t);
	w=Vmult(u,3.5);
	printf ("mult l*v %lf %lf %lf %lf\n",w.x,w.y,w.z,w.t);
}
*/


		

