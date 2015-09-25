#include "uv.h"

int read_txt_quasar (Environnement *env, char *filename,Quasar * quasar)
{
  FILE *data_file;
  char c;
  register int count;
  
  START;
  data_file =fopen(filename,"r");
  if (data_file)
    {
      count=0;
      while(!feof(data_file))
	{
	  fscanf(data_file,"%c",&c);
	  if(c == '\n')count++;
	}
      rewind(data_file);
      env->data_size=count;
      for(count=0;count<env->data_size;count++)
	{
  fscanf(data_file,"%lf %lf %lf", &(quasar[count].ascension),&(quasar[count].declination),&(quasar[count].redshift));
	}
      fclose(data_file);
    }
  else
    {
      printf("\n   Can not open file %s    \n",filename);
      return 0;
    }
  return 1;
}

