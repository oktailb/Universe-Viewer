#include "uv.h"

/* give the value of the projection of u on d1 and d2 vectors	*/

Point *projection (Environnement *env, Vector u, Vector d1,Vector d2)
{
  Point *p;
  
  START;
  p = xmalloc(sizeof(*p));
  p->x = Vscalar(env, u,d1);
  p->y = Vscalar(env, u,d2);
  return (p);
}
