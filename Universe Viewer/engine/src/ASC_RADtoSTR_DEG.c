#include "uv.h"

char* ASC_RADtoSTR_DEG (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return ASC_DEGtoSTR_DEG(Valeur);
}
