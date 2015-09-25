#include "uv.h"

void write_bin_quasar (Environnement *env, Quasar * q,char *filename)
{
  FILE *data_file;
  register int count;
  
  data_file =fopen(filename,"w");
  if (data_file)
    {
      fprintf(data_file,"Q.S.O. data file\n");
      fprintf(data_file,"LENGHT=%d\n",env->data_size);
      if (q)
	for(count=0;count< env->data_size;count++)
	  fwrite((double *)(q+count),sizeof(double),3,data_file);
      fclose(data_file);
    }
  else
    {
      printf("Can not open file %s ",filename);
    }
}

