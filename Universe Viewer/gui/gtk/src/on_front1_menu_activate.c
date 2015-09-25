#include <gtk/gtk.h>
#include <glade/glade.h>
#include "uv-gtk.h"
#include "uv.h"

void    on_front1_menu_activate (const gchar *handler_name,
				 GObject *object,
				 const gchar *signal_name,
				 const gchar *signal_data,
				 GObject *connect_object,
				 gboolean after,
				 gpointer user_data)
{
  if(!vue_is_displayed[3])
    {
      vue_is_displayed[3] = 1;
      uv_gtk_env->quasar_proj[3] = set_quasar_proj(uv_gtk_env, uv_gtk_env->quasar_pos,3);
    }
}
