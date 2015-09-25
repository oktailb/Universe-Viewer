#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* this function is the pure test procedure to put out causal cell curve	*/


Point *graphC4(Environnement *env)
{
  int i;
  Point	*graph;

  graph = xmalloc(sizeof(graph) * env->graphC4_lenght);
  for(i=0;i < env->graphC4_lenght;i++)
    {
      graph[i].x=0.0;
      graph[i].y=0.0;
    }
  return (graph);
}


