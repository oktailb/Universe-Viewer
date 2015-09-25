#include "uv.h"

extern int vue_is_displayed[NBVIEWS];

void write_ps_quasar(Environnement *env, Quasar* q, char* filename)
{
  int i,count=0,nb=0;
  FILE* f;
  Point scale;
  Point* grf;
  int Xmax,Ymax,Xmin,Ymin;
  double radius;
  
  q = q;
  
  f=fopen(filename,"w");
  if(f)
    {
      for(i=0;i<NBVIEWS;i++)
	{
	  if(vue_is_displayed[i])
	    {
	      grf = env->quasar_proj[i];
	    }
	}
      scale.x=512/512;   scale.y=512/512;
      Xmin=300-512/2; Ymin=400-512/2;
      Xmax=300+512/2; Ymax=400+512/2;
      radius=0.5/512;
      
      fprintf(f,"%%!PS-Adobe-2.0 EPSF-2.0%%%%Title:%s\n%%%%Creator: %s\n"
	      ,env->data_filename,TITLE);
      fprintf(f,"%%%%BoundingBox: %d %d %d %d\n\n300 400 translate\n"
	      ,Xmin,Ymin-100,Xmax,Ymax);
      fprintf(f,"%f %f scale\n0 setlinewidth\n0 setgray \n/radius %f def \n"
	      ,scale.x,scale.y,radius);
      for(i=0;i<env->data_lenght;i++)
	{
	  if      (((env->quasar_pos[i].x-256)*scale.x>Xmin-300)
		   &&((env->quasar_pos[i].x-256)*scale.x<Xmax-300)
		   &&((env->quasar_pos[i].y-256)*scale.y>Ymin-400)
		   &&((env->quasar_pos[i].y-256)*scale.y<Ymax-400))
	    {
	      if((count%250)==0)
		{
		  fprintf(f,"/quasars%d  \n[\n",nb);
		  nb++;
		}
	      fprintf(f,"\t%f  %f",env->quasar_pos[i].x-256,env->quasar_pos[i].y-256);
	      if((count%8)==7) fprintf(f,"\n");
	      if((count%250)==249) fprintf(f,"\n] def\n\n");
	      count++;
	    }
	}
      if((count%250)!=0) { fprintf(f,"\n] def\n\n"); }
      for(i=0;i<nb;i++)
	{
	  fprintf(f,"0 1 quasars%d length 1 sub 2 idiv  \n{\n\t/count exch def\n\tnewpath\n"
		  ,i);
	  fprintf(f,"\tquasars%d count 2 mul get\n",i);
	  fprintf(f,"\tquasars%d  count 2 mul 1 add get\n\tradius 0 360 arc fill\n} for \n"
		  ,i);
	}
      fprintf(f,"\n%%Draw a frame\n");
      fprintf(f,"\n %f %f moveto %f %f lineto\n",-200.0/scale.x,-200.0/scale.y,-200.0/scale.x,200.0/scale.y);
      fprintf(f,"\n %f %f lineto %f %f lineto\n",200.0/scale.x,200.0/scale.y,200.0/scale.x,-200.0/scale.y);
      fprintf(f,"closepath stroke\n\n%% Cosmological constants value and angles\n");
      fprintf(f,"\n/Symbol findfont %f scalefont setfont\n",35.0/(scale.x+scale.y));
      fprintf(f,"%f %f moveto (W = %f) show\n",-0.9*200.0/scale.x,-1.1*200.0/scale.y,env->friedman.omega);
      fprintf(f,"%f %f moveto (l = %f) show\n",-0.9*200.0/scale.x,-1.2*200.0/scale.y,env->friedman.lambda);
      fprintf(f,"%f %f moveto (a = %f) show\n",-0.9*200.0/scale.x,-1.4*200.0/scale.y,env->friedman.alpha);
      fprintf(f,"0 %f moveto (d = %f) show\n",-1.3*200.0/scale.y,env->declination);
      fprintf(f,"0 %f moveto (b = %f) show\n",-1.4*200.0/scale.y,env->beta);
      fprintf(f,"\n/Times-Roman findfont %f scalefont setfont\n",35.0/(scale.x+scale.y));
      fprintf(f,"%f %f moveto (k = %f) show\n",-0.9*200.0/scale.x,-1.3*200.0/scale.y,env->friedman.k);
      fprintf(f,"%f %f moveto (Reper:%f) show\n",-0.1*200.0/scale.x,-1.1*200.0/scale.y,env->friedman.omega);
      fprintf(f,"0 %f moveto (a = %f) show\n",-1.2*200.0/scale.y,env->ascension);
      fprintf(f,"\n%%Draw the %d quasars\nshowpage\n",count);
      fclose(f);
    }
  else printf(" Can not open  file. ");
}
