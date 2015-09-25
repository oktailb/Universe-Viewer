#include "uv.h"

char* DEC_RADtoSTR_DMS (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return DEC_DEGtoSTR_DMS(Valeur);
}

