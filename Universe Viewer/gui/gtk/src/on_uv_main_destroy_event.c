#include <gtk/gtk.h>
#include <glade/glade.h>
#include "uv-gtk.h"
#include "uv.h"

void    on_uv_main_destroy_event (const gchar *handler_name,
				  GObject *object,
				  const gchar *signal_name,
				  const gchar *signal_data,
				  GObject *connect_object,
				  gboolean after,
				  gpointer user_data)
{
  START;
  printf("Good bye !");
  exit(EXIT_SUCCESS);
}
