#include "uv.h"

int get_bin_nb_quasar(Environnement *env, char* filename)
{
  FILE *data_file;
  char entete[20];
  
  data_file =fopen(filename,"r");
  if (data_file)
    {
      fscanf(data_file,"%16s\n",entete);
      if ((entete[0]=='Q')&&(entete[2]=='S')&&(entete[4]=='O'))
	{
	  fscanf(data_file,"LENGHT=%d\n",&env->data_size);
	  return env->data_size;
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
  return -1;
}
