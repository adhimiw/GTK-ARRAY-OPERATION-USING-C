#include <gtk/gtk.h>

#define MAX_SIZE 100

int array[MAX_SIZE];
int size = 0;

GtkWidget *outputLabel;

// Function prototypes
void insert_element(GtkWidget *widget, gpointer data);
void delete_element(GtkWidget *widget, gpointer data);
void search_element(GtkWidget *widget, gpointer data);
void display_array(GtkWidget *widget, gpointer data);
void traverse_array(GtkWidget *widget, gpointer data);
void merge_arrays(GtkWidget *widget, gpointer data);
void exit_program(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *insertButton, *deleteButton, *searchButton, *displayButton, *traverseButton, *mergeButton, *exitButton;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Array Operations");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    insertButton = gtk_button_new_with_label("Insert Element");
    deleteButton = gtk_button_new_with_label("Delete Element");
    searchButton = gtk_button_new_with_label("Search Element");
    displayButton = gtk_button_new_with_label("Display Array");
    traverseButton = gtk_button_new_with_label("Traverse Array");
    mergeButton = gtk_button_new_with_label("Merge Arrays");
    exitButton = gtk_button_new_with_label("Exit");

    outputLabel = gtk_label_new("");

    g_signal_connect(G_OBJECT(insertButton), "clicked", G_CALLBACK(insert_element), NULL);
    g_signal_connect(G_OBJECT(deleteButton), "clicked", G_CALLBACK(delete_element), NULL);
    g_signal_connect(G_OBJECT(searchButton), "clicked", G_CALLBACK(search_element), NULL);
    g_signal_connect(G_OBJECT(displayButton), "clicked", G_CALLBACK(display_array), NULL);
    g_signal_connect(G_OBJECT(traverseButton), "clicked", G_CALLBACK(traverse_array), NULL);
    g_signal_connect(G_OBJECT(mergeButton), "clicked", G_CALLBACK(merge_arrays), NULL);
    g_signal_connect(G_OBJECT(exitButton), "clicked", G_CALLBACK(exit_program), window);

    gtk_box_pack_start(GTK_BOX(vbox), insertButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), deleteButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), searchButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), displayButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), traverseButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), mergeButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), outputLabel, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

// Function definitions
void traverse_array(GtkWidget *widget, gpointer data) {
    // Display the array elements in the output label
    char outputMessage[200] = "Array elements (Traversed) are: ";
    for (int i = size - 1; i >= 0; i--) {
        char elementStr[10];
        sprintf(elementStr, "%d ", array[i]);
        strcat(outputMessage, elementStr);
    }
    gtk_label_set_text(GTK_LABEL(outputLabel), outputMessage);
}

void merge_arrays(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags;

    int newArray[MAX_SIZE];
    int newSize;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Merge Arrays", NULL, flags, "_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create labels and entry widgets for input
    GtkWidget *labelSize = gtk_label_new("Enter the size of the new array:");
    GtkWidget *entrySize = gtk_entry_new();
    GtkWidget *labelElements = gtk_label_new("Enter elements of the new array (space-separated):");
    GtkWidget *entryElements = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(content_area), labelSize);
    gtk_container_add(GTK_CONTAINER(content_area), entrySize);
    gtk_container_add(GTK_CONTAINER(content_area), labelElements);
    gtk_container_add(GTK_CONTAINER(content_area), entryElements);

    // Show the dialog
    gtk_widget_show_all(dialog);

    // Run the dialog and get user input
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        // Get user input
        const char *sizeText = gtk_entry_get_text(GTK_ENTRY(entrySize));
        const char *elementsText = gtk_entry_get_text(GTK_ENTRY(entryElements));

        // Convert input to integers
        newSize = atoi(sizeText);

        // Parse and fill the new array
        sscanf(elementsText, "%d %d %d %d %d %d %d %d %d %d",
               &newArray[0], &newArray[1], &newArray[2], &newArray[3], &newArray[4],
               &newArray[5], &newArray[6], &newArray[7], &newArray[8], &newArray[9]);

        // Merge the arrays
        if (size + newSize <= MAX_SIZE) {
            for (int i = 0; i < newSize; i++) {
                array[size + i] = newArray[i];
            }
            size += newSize;

            // Display the updated array
            display_array(widget, data);
        } else {
            // Show an error message
            gtk_label_set_text(GTK_LABEL(outputLabel), "Merging arrays would exceed the maximum size.");
        }
    }

    // Close the dialog
    gtk_widget_destroy(dialog);
}

// ... (Other function definitions remain unchanged)

// Function definitions
void insert_element(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags;

    int element, position;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Insert Element", NULL, flags, "_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create labels and entry widgets for input
    GtkWidget *labelElement = gtk_label_new("Enter the new element:");
    GtkWidget *entryElement = gtk_entry_new();
    GtkWidget *labelPosition = gtk_label_new("Enter the position (1 to current size + 1):");
    GtkWidget *entryPosition = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(content_area), labelElement);
    gtk_container_add(GTK_CONTAINER(content_area), entryElement);
    gtk_container_add(GTK_CONTAINER(content_area), labelPosition);
    gtk_container_add(GTK_CONTAINER(content_area), entryPosition);

    // Show the dialog
    gtk_widget_show_all(dialog);

    // Run the dialog and get user input
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        // Get user input
        const char *elementText = gtk_entry_get_text(GTK_ENTRY(entryElement));
        const char *positionText = gtk_entry_get_text(GTK_ENTRY(entryPosition));

        // Convert input to integers
        element = atoi(elementText);
        position = atoi(positionText);

        if (position >= 1 && position <= size + 1) {
            // Insert the new element at the specified position
            for (int i = size; i >= position; i--) {
                array[i] = array[i - 1];
            }
            array[position - 1] = element;
            size++;

            // Display the updated array
            display_array(widget, data);
        } else {
            // Show an error message
            gtk_label_set_text(GTK_LABEL(outputLabel), "Invalid position. Please enter a position between 1 and current size + 1.");
        }
    }

    // Close the dialog
    gtk_widget_destroy(dialog);
}

void delete_element(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags;

    int index;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Delete Element", GTK_WINDOW(widget), flags, "_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create labels and entry widgets for input
    GtkWidget *labelIndex = gtk_label_new("Enter the index of the element to be deleted:");
    GtkWidget *entryIndex = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(content_area), labelIndex);
    gtk_container_add(GTK_CONTAINER(content_area), entryIndex);

    // Show the dialog
    gtk_widget_show_all(dialog);

    // Run the dialog and get user input
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        // Get user input
        const char *indexText = gtk_entry_get_text(GTK_ENTRY(entryIndex));

        // Convert input to integer
        index = atoi(indexText);

        if (index >= 1 && index <= size) {
            // Shift elements to fill the gap left by the deleted element
            for (int i = index - 1; i < size - 1; i++) {
                array[i] = array[i + 1];
            }
            size--;

            // Display the updated array
            display_array(widget, data);
        } else {
            // Show an error message
            gtk_label_set_text(GTK_LABEL(outputLabel), "Invalid index. Please enter an index between 1 and current size.");
        }
    }

    // Close the dialog
    gtk_widget_destroy(dialog);
}

void search_element(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags;

    int toSearch;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Search Element", GTK_WINDOW(widget), flags, "_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create labels and entry widgets for input
    GtkWidget *labelToSearch = gtk_label_new("Enter element to search:");
    GtkWidget *entryToSearch = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(content_area), labelToSearch);
    gtk_container_add(GTK_CONTAINER(content_area), entryToSearch);

    // Show the dialog
    gtk_widget_show_all(dialog);

    // Run the dialog and get user input
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        // Get user input
        const char *toSearchText = gtk_entry_get_text(GTK_ENTRY(entryToSearch));

        // Convert input to integer
        toSearch = atoi(toSearchText);

        // Search for the element in the array
        int found = 0;
        for (int i = 0; i < size; i++) {
            if (array[i] == toSearch) {
                found = 1;
                // Show the result
                char resultMessage[50];
                sprintf(resultMessage, "%d is found at position %d", toSearch, i + 1);
                gtk_label_set_text(GTK_LABEL(outputLabel), resultMessage);
                break;
            }
        }

        if (!found) {
            // Show an error message
            gtk_label_set_text(GTK_LABEL(outputLabel), "Element not found in the array.");
        }
    }

    // Close the dialog
    gtk_widget_destroy(dialog);
}

void display_array(GtkWidget *widget, gpointer data) {
    // Display the array elements in the output label
    char outputMessage[200] = "Array elements are: ";
    for (int i = 0; i < size; i++) {
        char elementStr[10];
        sprintf(elementStr, "%d ", array[i]);
        strcat(outputMessage, elementStr);
    }
    gtk_label_set_text(GTK_LABEL(outputLabel), outputMessage);
}

void exit_program(GtkWidget *widget, gpointer data) {
    // Exit the program
    gtk_main_quit();
}
