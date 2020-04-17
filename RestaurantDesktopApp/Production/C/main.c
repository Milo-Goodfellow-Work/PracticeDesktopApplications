#include <gtk/gtk.h>

struct manyWidgets {
  GtkWidget *widget1;
  GtkWidget *widget2;

};

void open_window(struct manyWidgets windowChange)
{
  gtk_widget_hide(windowChange.widget1);
  gtk_widget_show_all(windowChange.widget2);
  
}

int main(int argc, char *argv[])
{
  //Declare required variables

  //Windows
  GtkWidget *window;
  GtkWidget *windowRestaurant;

  //Any internal objects
  GObject *exitBtn;
  GObject *orderBtn;
  GObject *backBtn;

  //Error handling on file import
  GError *error = NULL;

  //File handling and CSS
  GdkScreen *screen = gdk_screen_get_default();
  GtkBuilder *builder;
  GtkStyleContext *context;
  GtkCssProvider *provider;

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

  //Retrieve the windows from the design file 
  window = GTK_WIDGET(gtk_builder_get_object(builder, "IntroductoryWindow"));
  windowRestaurant = GTK_WIDGET(gtk_builder_get_object(builder, "OrderWindow"));

  //Connect the window X button to the window destruction
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //Get context of the window for CSS editing
  context = gtk_widget_get_style_context(window);

  //Create the Gtk css provider and assign it as a new css provider object
  provider = gtk_css_provider_new();

  //Handle CSS file import
  if(gtk_css_provider_load_from_path(provider, "CSS/WindowOne.css", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
    
  }


  //Enable CSS
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  //Button handling
  exitBtn = gtk_builder_get_object(builder, "ExitButton");
  g_signal_connect(exitBtn, "clicked", G_CALLBACK(gtk_main_quit), NULL);

  //Passing multiple widgets to a function using a struct
  struct manyWidgets openCloseSetToRestaurant = {window, windowRestaurant};
  orderBtn = gtk_builder_get_object(builder, "OrderButton");
  g_signal_connect_swapped(orderBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToRestaurant);

  struct manyWidgets openCloseSetToHome = {windowRestaurant, window};
  backBtn = gtk_builder_get_object(builder, "BackButton");
  g_signal_connect_swapped(backBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToHome);
  
  //Show the first window
  gtk_widget_show_all(window);
  
  //Run the program
  gtk_main();
  
  return 0;
}


  
