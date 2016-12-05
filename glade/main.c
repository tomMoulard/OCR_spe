# define _XOPEN_SOURCE 500

# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "../types/pixel.h"
# include "../image_op/binarize.h"
# include "../matrix_op/rlsa.h"
# include "../types/rectangle.h"
# include "../types/matrix.h"
# include "../types/matbintree.h"
# include "../matrix_op/xycut.h"
# include "../image_op/sdl_fct.h"
# include "../images/database.h"
# include "../image_op/rotation.h"

//neural NetWork
# include "../NeuralNetWork/nr.h"

GtkWidget *window;
GtkWidget *wimage;
GtkWidget *image;
int first = 0;
UnsignedMatrix *mat;
double angle_final = 0.0;

void display_image_gtk(const gchar *filename)
{
    wimage = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(wimage), 320, 200);
    gtk_window_set_title(GTK_WINDOW(wimage), "GtkImage");
    g_signal_connect(G_OBJECT(wimage), "destroy", 
                              G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *pVBox = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(wimage), pVBox);
    image = gtk_image_new_from_file(filename);
    gtk_box_pack_start(GTK_BOX(pVBox), image, FALSE, FALSE, 5);
    gtk_widget_show_all(wimage);
}

void display_text(const gchar *text)
{
    GtkWidget *label = gtk_label_new(text);   
    GtkWidget *wtext = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(wtext), 320, 200);
    gtk_window_set_title(GTK_WINDOW(wtext), "GtkImage");
    g_signal_connect(G_OBJECT(wtext), "destroy",
                              G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *pVBox = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(wtext), pVBox);
    gtk_box_pack_start(GTK_BOX(pVBox), label, FALSE, FALSE, 5);
    GtkWidget *quitButton = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(pVBox), quitButton, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(quitButton), "clicked", 
                              G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *quitLabel = gtk_label_new("Quit");
    gtk_container_add(GTK_CONTAINER(quitButton), quitLabel);
    gtk_widget_show_all(wtext);
}


int main(int argc, char *argv[])
{
    init_sdl();
    GtkBuilder      *builder; 
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "main.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
    return 0;
}

//see how to use the chooser file


void choose_image(char *file)
{   
    //test if it is a bmp
    if(first)
      gtk_widget_hide(wimage);
    else
      first = 1;
    //get the image, bineraze it and save it to a file
    size_t lines = bmpWidth(file);
    size_t cols = bmpHeight(file);
    SDL_Surface *surf = load_image(file);
    PixelMatrix *img = new_pixel_matrix(lines, cols);
    mat = new_unsigned_matrix(lines, cols);
    save_image(surf, img);
    binarize(img, mat);
    surf = unsignedMatrix_to_pict(mat, 1);
    SDL_SaveBMP(surf, "../images/tmp.bmp");
    free_pixel_matrix(img);
    display_image_gtk("../images/tmp.bmp");
    /*for(int i = 0; i < 5; i++)
        gtk_widget_set_opacity(button[i], 1.0);*/
}

void rotate_image(double angle)
{
  angle_final += angle;
  if(angle_final >= 360.0)
    angle_final -= 360.0;
  if(angle_final <= -360.0)
    angle_final += 360.0;
  UnsignedMatrix *rot = rotation(mat, angle_final);
  SDL_Surface *surf = unsignedMatrix_to_pict(rot, 1);
  free_unsigned_matrix(rot);
  SDL_SaveBMP(surf, "../images/tmp.bmp");
  gtk_image_set_from_file(GTK_IMAGE(image), "../images/tmp.bmp");
}


//use all button to rotate the mat

void file_selected(GtkWidget *filechooserbutton)
{
  char *filename =
    gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
  printf("%s\n", filename);
  choose_image(filename);
}

void min_one()
{   
  rotate_image(-1.0);
}

void min_ten()
{   
  rotate_image(-10.0);
}

void plus_ninety()
{   
  rotate_image(90.0);
}

void plus_ten()
{   
  rotate_image(10.0);
}

void plus_one()
{   
  rotate_image(1.0);
}

void play_button()
{
    //call for all op of the OCR
    //mat = rotation(mat, angle_final);
    display_text("lol");
    gtk_widget_hide(window);
    //gtk_main_quit();
}

void destroy()
{
    gtk_main_quit();
}
