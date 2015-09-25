#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include <unistd.h>

#include "uv.h"
#include "uv-gtk.h"



void	show_main()
{
  gtk_widget_show(deglade("uv_main.glade", "uv_main"));
}

void	open_file(char *file)
{
  int	i;

  uv_gtk_env->data_lenght = get_txt_nb_quasar(uv_gtk_env, file);
  uv_gtk_env->quasar = xmalloc(sizeof(*(uv_gtk_env->quasar)) * uv_gtk_env->data_lenght);
  read_txt_quasar(uv_gtk_env, file, uv_gtk_env->quasar);
  uv_gtk_env->graphT = calc_quasar_tau(uv_gtk_env, uv_gtk_env->quasar);
  uv_gtk_env->quasar_pos = calc_quasar_pos(uv_gtk_env, uv_gtk_env->quasar);
  init_projection_vectors(uv_gtk_env);
  for(i = 0; i < NBVIEWS; i++)
    {
      uv_gtk_env->quasar_proj[i] = set_quasar_proj(uv_gtk_env, uv_gtk_env->quasar_pos, i);
      uv_gtk_env->the_earth[i] = set_earth_proj(uv_gtk_env, uv_gtk_env->earth, i);
    }
}

int		main(int argc, char **argv)
{
  gtk_init(&argc, &argv);
  glade_init();
  uv_gtk_env = init_uv();
  init_abacus(uv_gtk_env);
  if (argc == 2)
    open_file(argv[1]);
  show_main();
  gtk_main();
  return (0);
}
