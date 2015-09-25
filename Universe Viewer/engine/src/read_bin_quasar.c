#include "uv.h"

int read_bin_quasar (Environnement *env, char *filename, Quasar * quasar)
{
  FILE *data_file;
  register int count;
  char entete[20];
  
  data_file =fopen(filename,"r");
  if (data_file)
    {
      fscanf(data_file,"%16s\n",entete);
      if ((entete[0]=='Q')&&(entete[2]=='S')&&(entete[4]=='O'))
	{
	  fscanf(data_file,"LENGHT=%d\n",&env->data_size);
	  /*quasar = (Quasar *) calloc(data_size,sizeof(Quasar));*/
	  for(count=0;count<env->data_size;count++)
	    fread((double *)(quasar+count),sizeof(double),3,data_file);
	}
      else
	{
	  printf("%s is not a Q.S.O. data file ",filename);
	}
      fclose(data_file);
    }
  else
    {
      printf("\n   Can not open file %s   \n",filename);
    }
  return 0;
}

