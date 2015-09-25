#include "uv.h"

void  write_txt_quasar (Environnement *env, Quasar *q,char *filename)
{
  FILE *data_file;
  register int count;
  
  data_file =fopen(filename,"w");
  if (data_file)
    {
      if (q)
	for(count=0;count<env->data_size;count++)
	  fprintf(data_file,"%f %f %f\n",q[count].ascension, q[count].declination,q[count].redshift);
      fclose(data_file);
    }
  else
    {
      printf("Can not open file %s ",filename);
    }
}

