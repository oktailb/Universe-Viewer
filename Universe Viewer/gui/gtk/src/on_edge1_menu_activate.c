#include <gtk/gtk.h>
#include <glade/glade.h>
#include "uv-gtk.h"
#include "uv.h"

extern Environnement	*uv_gtk_env;

void		on_edge1_menu_activate (const gchar *handler_name,
					GObject *object,
					const gchar *signal_name,
					const gchar *signal_data,
					GObject *connect_object,
					gboolean after,
					gpointer user_data)
{
  GtkWidget	*view;
  GtkWidget	*draw;
  int		i;
  gint		width;
  gint		height;
  
  START;
  i = 0;
  if(!vue_is_displayed[0])
    {
      vue_is_displayed[0] = 1;
      uv_gtk_env->quasar_proj[0] = set_quasar_proj(uv_gtk_env, uv_gtk_env->quasar_pos,0);
      view = deglade("uv_view.glade", "uv_view");
      draw = get_child(view, "uv_draw");
      if (draw != NULL)
	{
	  gtk_widget_show(draw);
	  gtk_widget_get_size_request(draw, &width, &height);
	  width = width/2;
	  height = height/2;
	  for(i = 0; i < uv_gtk_env->data_lenght; i++)
	    {
	      gdk_draw_point(draw->window,
			     draw->style->black_gc,
			     (int) (uv_gtk_env->quasar_proj[0][i].x*width+width),
			     (int) (height-uv_gtk_env->quasar_proj[0][i].y*height)
			     );
	    }
	  gtk_widget_show(view);
	}
      else
	printf("GTK de merde !\n");
    }
}
