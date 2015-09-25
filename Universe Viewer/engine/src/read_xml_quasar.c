#include "uv.h"

int read_xml_quasar (Environnement *env, char* NomFichier, Quasar* quasar)
{
  FILE* FD;
  int i=0, k=0, j=0, NBE=0;
  char LIGNE[255], VAL [10], RS [10], MAG [10];
  
  FD = fopen(NomFichier, "r");
  if (!FD) return 0;
  
  fgets(LIGNE, 255, FD);
  while(strstr(LIGNE, "<DATA>")==NULL && !feof(FD)) fgets(LIGNE, 255, FD);
  if (feof(FD))
    {
      printf("XML file corrupted...\n");
      return 0;
    }
  
  NBE = get_xml_nb_quasar (env, NomFichier);
  if (!quasar)
    {
      printf("Memory allocation error for data\n");
      return 0;
    }
  
  while (i<NBE)
    {
      fgets(LIGNE, 255, FD);
      
      j=8;
      while(LIGNE[j]!='<') VAL[k++]=LIGNE[j++];
      VAL[k]='\0';
      
      if(env->radians)
	{
	  quasar[i].ascension=atof(VAL);
	}
      else
	{
	  quasar[i].ascension=HMStoRAD(VAL);
	}
      k=0;
      
      j+=9;
      while(LIGNE[j]!='<') VAL[k++]=LIGNE[j++];
      VAL[k]='\0';
      if(env->radians)
	{
	  quasar[i].declination=atof(VAL);
	}
      else
	{
	  quasar[i].declination=DMStoRAD(VAL);
	}
      k=0;
      
      j+=9;
      while(LIGNE[j]!='<') j++;
      
      j+=9;
      while(LIGNE[j]!='<') j++;
      
      j+=9;
      while(LIGNE[j]!='<') RS[k++]=LIGNE[j++];
      RS[k]='\0';
      if (strlen(RS)!=0) quasar[i].redshift=atof(RS);
      else
	{
	  printf("REDSHIFT  missing to record %d\n", i+1);
	  NBE--;
	  env->data_lenght--;
	}
      k=0;
      
      j+=9;
      while(LIGNE[j]!='<') MAG[k++]=LIGNE[j++];
      MAG[k]='\0';
      if (strlen(MAG)!=0) quasar[i].magnitude=atof(MAG);
      else
	{
	  printf("MAGNITUDE missing to record n%d\n", i+1);
	}
      k=0;
      
      i++;
    }
  fclose(FD);
  return NBE;
}

