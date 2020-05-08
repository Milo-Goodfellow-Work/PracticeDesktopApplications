//Include nescassery imports
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Structure formed of two GTKWidgets to hold window swaps
struct manyWidgets {
  GtkWidget *widget1;
  GtkWidget *widget2;

};

//Swap windows of input struct
void open_window(struct manyWidgets windowChange)
{
  gtk_widget_hide(windowChange.widget1);
  gtk_widget_show_all(windowChange.widget2);
  
}

//Final dialogue function
void final_order(GtkToggleButton *finalOrders[7])
{
  //Create a string whos purpose is to store food options
  char initialLabelSet[1000];
  //Assign that strings first position to zero in order to resolve UTF errors
  initialLabelSet[0] = 0;
  
  //Create the final dialogue window and assign it
  GtkDialog *finalMessage;
  finalMessage = GTK_DIALOG(gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, NULL));

  //Cycle over the food labels
  //If a food option is chosen, save it to the food options string
  strcat(initialLabelSet, "Your order was saved and is as follows:\n");
  for(int i = 0; i < 7; i++)
  {
    if(gtk_toggle_button_get_active(finalOrders[i]))
    {
      strcat(initialLabelSet, gtk_button_get_label(GTK_BUTTON(finalOrders[i])));
      strcat(initialLabelSet, "\n");

    } 
  }
  
  //Create a new file and save the order to it
  FILE * fp;
  fp = fopen("Order.txt", "w+");
  fputs(initialLabelSet, fp);
  fclose(fp);

  //Show the dialogue box containing that order
  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(finalMessage), initialLabelSet);
  gtk_dialog_run(finalMessage);
  
}


//Auto running function
int main(int argc, char *argv[])
{
  //Declare required variables

  //Windows
  GtkWidget *window;
  GtkWidget *windowRestaurant;
  GtkWidget *windowGallery;

  //Any internal objects
  GObject *exitBtn;
  GObject *orderBtn;
  GObject *backBtn;
  GObject *galleryBtn;
  GObject *galleryBackBtn;
  GtkToggleButton *saladBtn;
  GtkToggleButton *breadBtn;
  GtkToggleButton *crunchBtn;
  GtkToggleButton *burritoBtn;
  GtkToggleButton *shrimpBtn;
  GtkToggleButton *dateBtn;
  GtkToggleButton *lemonBtn;
  GObject *submitBtn;

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
  windowGallery = GTK_WIDGET(gtk_builder_get_object(builder, "GalleryWindow"));
  
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


  //Prepare windows for deletion
  g_signal_connect(G_OBJECT(windowGallery), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(windowRestaurant), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  
  //Button handling
  exitBtn = gtk_builder_get_object(builder, "ExitButton");
  g_signal_connect(exitBtn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
  
  //Passing multiple widgets to a function using a struct
  struct manyWidgets openCloseSetToRestaurant = {window, windowRestaurant};
  orderBtn = gtk_builder_get_object(builder, "OrderButton");
  g_signal_connect_swapped(orderBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToRestaurant);

  //Setup window switching
  struct manyWidgets openCloseSetToHome = {windowRestaurant, window};
  backBtn = gtk_builder_get_object(builder, "BackButton");
  g_signal_connect_swapped(backBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToHome);

  struct manyWidgets openCloseSetToGallery = {window, windowGallery};
  galleryBtn = gtk_builder_get_object(builder, "GalleryButton");
  g_signal_connect_swapped(galleryBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToGallery);

  struct manyWidgets openCloseSetToHomeGallery = {windowGallery, window};
  galleryBackBtn = gtk_builder_get_object(builder, "GalleryBackButton");
  g_signal_connect_swapped(galleryBackBtn, "clicked", G_CALLBACK(open_window), &openCloseSetToHomeGallery);
  
  //Radio Buttons
  saladBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "SaladCheckBox"));
  breadBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "BreadCheckBox"));
  crunchBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "CrunchCheckBox"));
  burritoBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "BurritoCheckBox"));
  shrimpBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "ShrimpCheckBox"));
  dateBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "DateCheckBox"));
  lemonBtn = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "LemonCheckBox"));
  
  //Submit Order Button
  submitBtn = gtk_builder_get_object(builder,"SubmitButton");
  GtkToggleButton *finalDialogue[7] = {saladBtn, breadBtn, crunchBtn, burritoBtn, shrimpBtn, dateBtn, lemonBtn};
  g_signal_connect_swapped(submitBtn, "clicked", G_CALLBACK(final_order), finalDialogue);
  
  //Show the first window
  gtk_widget_show_all(window);
  
  //Run the program
  gtk_main();

  //Return 0
  return 0;
}


  
