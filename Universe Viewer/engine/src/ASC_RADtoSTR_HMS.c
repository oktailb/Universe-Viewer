#include "uv.h"

char* ASC_RADtoSTR_HMS (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return ASC_DEGtoSTR_HMS(Valeur);
}

