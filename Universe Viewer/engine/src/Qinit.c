#include "uv.h"

Quasar *Qinit(double ascension ,double declination ,double redshift ,double tau)
{
  Quasar *q;

  q = xmalloc(sizeof(*q));
  q->ascension = ascension;
  q->declination = declination;
  q->redshift = redshift;
  q->tau = tau;
  return (q);
}
