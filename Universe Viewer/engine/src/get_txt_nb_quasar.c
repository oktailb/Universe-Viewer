#include "uv.h"

int get_txt_nb_quasar (Environnement * env, char *filename)
{
	FILE *data_file;
	char c;
	register int count=0;
       
	env = env;
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
	}
	return count;
}


