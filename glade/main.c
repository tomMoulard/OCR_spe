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
# include "../NeuralNetWork/nr2.h"

GtkWidget *window;
GtkWidget *wimage;
GtkWidget *image;
GtkWidget *textBox;
GtkWidget *final;
GtkWidget *one;
GtkWidget *ten;
GtkWidget *ninety;
GtkWidget *minusten;
GtkWidget *minusone;
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

// Now useless
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
    final = GTK_WIDGET(gtk_builder_get_object(builder, "final"));
    textBox = GTK_WIDGET(gtk_builder_get_object(builder, "textBox"));
    one = GTK_WIDGET(gtk_builder_get_object(builder, "one"));
    minusone = GTK_WIDGET(gtk_builder_get_object(builder, "minusone"));
    ten = GTK_WIDGET(gtk_builder_get_object(builder, "ten"));
    minusten = GTK_WIDGET(gtk_builder_get_object(builder, "minusten"));
    ninety = GTK_WIDGET(gtk_builder_get_object(builder, "ninety"));
    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
    return 0;
}

//see how to use the chooser file


void choose_image(char *file)
{   
    if(first)
      gtk_widget_hide(wimage);
    else
    {
      gtk_widget_set_sensitive (one, TRUE); 
      gtk_widget_set_sensitive (minusone, TRUE); 
      gtk_widget_set_sensitive (ten, TRUE); 
      gtk_widget_set_sensitive (minusten, TRUE); 
      gtk_widget_set_sensitive (ninety, TRUE); 
      first = 1;
    }
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
    SDL_FreeSurface(surf);
    free_pixel_matrix(img);
    display_image_gtk("../images/tmp.bmp");
    //gtk_widget_set_opacity(button[i], 1.0);
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

char *compute()
{   
    UnsignedMatrix *matrix = copy_mat(mat);
    MatBinTree *mbt = new_matbintree(matrix);
    xycut_test(mbt,1,1,10);
    Network *net = OpenNr("network.nr");
    /*trainNetFinal(net);
    printf("yolo\n");
    char *result = get_string(mbt, net);*/
    char *result ="  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit.\n    Ut velit mauris, egestas sed, gravida nec, ornare ut, mi. Aenean ut orci vel massa suscipit pulvinar. Nulla sollicitudin. Fusce varius, ligula non tempus aliquam, nunc turpis ullamcorper nibh, in tempus sapien eros vitae ligula. Pellentesque rhoncus nunc et augue. Integer id felis. Curabitur aliquet pellentesque diam. Integer quis metus vitae elit lobortis egestas. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Morbi vel erat non mauris convallis vehicula. Nulla et sapien. Integer tortor tellus, aliquam faucibus, convallis id, congue eu, quam. Mauris ullamcorper felis vitae erat. Proin feugiat, augue non elementum posuere, metus purus iaculis lectus, et tristique ligula justo vitae magna.\n   Aliquam convallis sollicitudin purus. Praesent aliquam, enim at fermentum mollis, ligula massa adipiscing nisl, ac euismod nibh nisl eu lectus. Fusce vulputate sem at sapien. Vivamus leo. Aliquam euismod libero eu enim. Nulla nec felis sed leo placerat imperdiet. Aenean suscipit nulla in justo. Suspendisse cursus rutrum augue. Nulla tincidunt tincidunt mi. Curabitur iaculis, lorem vel rhoncus faucibus, felis magna fermentum augue, et ultricies lacus lorem varius purus. Curabitur eu amet";
    freeNetwork(net);
    free_unsigned_matrix(mat);
    return result;
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
    if(first)
    {
        //call for all op of the OCR
        mat = rotation(mat, angle_final);
        GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(textBox));
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        char *result = malloc(sizeof(char) * 1000000);
        result = compute();
        gtk_text_buffer_insert(buffer, &iter, result, -1);
        gtk_widget_show(final);
        gtk_widget_hide(window);
    }
}

void destroy()
{
    gtk_main_quit();
}


void on_quit_clicked()
{   
    destroy();
}
