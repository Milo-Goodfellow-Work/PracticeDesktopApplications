//Include nescassery imports
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

struct manyWidgets {
  GtkWidget *widget1;
  GtkTextView *widget2;

};


void save_file(struct manyWidgets populateText)
{
  GtkTextIter start, end;
  GtkTextBuffer *buffer;
  gchar *text;
  FILE *fp;

  fp = fopen("Save.txt", "w+");

  
  GTK_TEXT_VIEW(populateText.widget2);
  buffer = gtk_text_view_get_buffer(populateText.widget2);
  gtk_text_buffer_get_bounds(buffer, &start, &end);
  text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  fputs(text, fp);
  fclose(fp);
  
  
}

void open_file(struct manyWidgets populateText)
{
  FILE *fp = fopen("Save.txt", "r");
  char buff[255];
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(populateText.widget2);
  gchar *bufferText = fgets(buff, 255, (FILE*)fp);
  gtk_text_buffer_set_text(buffer, bufferText, strlen(bufferText));
  fclose(fp);
  
}
  
//Auto running function
int main(int argc, char *argv[])
{
  //Declare required variables

  //Windows
  GtkWidget *window;

  //File Searching
  GtkWidget *fileSearch;
  
  //Any internal objects
  GObject *openBtn;
  GObject *saveBtn;
  
  //File Importing
  GtkBuilder *builder;
  GtkWidget *dialog;

  //Error handling on file import
  GError *error = NULL;
  
  //Initialize GTK
  gtk_init(&argc, &argv);

  //Set the builder pointer to a new instance of the builder object
  builder = gtk_builder_new();

  //Attempt to open the glade design file. Should this fail, print the error and return 1
  if(gtk_builder_add_from_file(builder,"Glade/UserInterface.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  //Retrieve the window from the design file and create file chooser 
  window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
  dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, ("Cancel"), GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT, NULL);
  
  //Connect the window X button to the window destruction
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //Input box handling
  
  
  //Button handling
  openBtn = gtk_builder_get_object(builder, "OpenButton");
  
  struct manyWidgets set = {dialog, GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TextView"))};
  g_signal_connect_swapped(openBtn, "clicked", G_CALLBACK(open_file), &set);

  saveBtn = gtk_builder_get_object(builder, "SaveButton");
  g_signal_connect_swapped(saveBtn, "clicked", G_CALLBACK(save_file), &set);

  //Show the first window
  gtk_widget_show_all(window);
  
  //Run the program
  gtk_main();

  //Return 0
  return 0;
}


  
