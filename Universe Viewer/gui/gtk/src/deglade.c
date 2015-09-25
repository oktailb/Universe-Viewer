#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include <unistd.h>

#include "uv.h"
#include "uv-gtk.h"

char	*glade_path[] = {
  "/usr/share/uv/",
  "./",
  NULL
};

GtkWidget	*deglade(char *glade_file, char *id)
{
  int		i;
  GladeXML	*glade;
  GtkWidget	*res;
  char		*base;

  i = 0;
  while (glade_path[i] != NULL)
    {
      base = xmalloc((strlen(glade_path[i]) + strlen(glade_file) + 1) * sizeof(*base));
      strcpy(base, glade_path[i]);
      strcat(base, glade_file);
      glade = NULL;
      if(access(base, F_OK|R_OK) == 0)
	{
	  glade = glade_xml_new(base, id, NULL);
	  break;
	}
      free(base);
      i++;
    }
  if (glade)
    {
      glade_xml_signal_autoconnect(glade);
      res = glade_xml_get_widget(glade, id);
      return (res);
    }
  else
    {
      printf("Missing glade ressources !\n");
      exit (EXIT_FAILURE);
    }
}

GtkWidget	*get_child(GtkWidget *parent, char *name)
{
  GList		*list;
  GtkWidget	*res;

  list = gtk_container_get_children((GtkContainer*)parent);
  while (list)
    {
      res = list->data;
      if (!strcmp(gtk_widget_get_name(res), name))
	return (res);
      list = list->next;
    }
  START;
  return (NULL);
}
