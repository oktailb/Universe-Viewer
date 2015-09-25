#include "uv.h"

char* DEC_RADtoSTR_DEG (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return DEC_DEGtoSTR_DEG(Valeur);
}
