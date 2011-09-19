#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <gtk/gtk.h>
using namespace std;

gchar* selected;
string act;
string homedir;
string fn;
string cmd;
string settingsdir;
string profiledir;

// Callbacks:
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    g_print ("Delete event occurred. Exiting...\n");
    gtk_main_quit();
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
gtk_main_quit();	
}

static void set_active_profile(GtkWidget *widget, gchar* profile) {
selected = profile;	
}

static void apply(GtkWidget *widget, GtkWidget *main_window) {
GtkWidget *dialog;
GtkWidget *button;
GtkWidget *label;
cmd = "rm " + fn;
system(cmd.c_str());
ofstream actout(fn.c_str());
actout << selected;
actout.close();
gtk_widget_hide(main_window);
dialog = gtk_dialog_new();
button = gtk_button_new_with_label("Ok");
gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> action_area), button, true, true, 0);
gtk_widget_show(button);
g_signal_connect(button, "clicked", G_CALLBACK(destroy), NULL);
stringstream labelss;
labelss << "Activated profile: " << endl << selected << endl << "Thank you for using Phitherek_' s Startup Profiler!";
string slabel = labelss.str();
label = gtk_label_new(slabel.c_str());
gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, true, true, 0);
gtk_widget_show(label);
gtk_widget_show(dialog);
}

int main(int argc, char** argv) {
// Widgets:
GtkWidget *main_window;
GtkWidget *main_vbox;
GtkWidget *top_vbox;
GtkWidget *list_vbox;
GtkWidget *bottom_hbox;
GtkWidget *welcome_label;
GtkWidget *title_label;
GtkWidget *active_profile_label;
GtkWidget *empty_label;
GtkWidget *separator;
GtkWidget *radio_button;
GtkWidget *middle_vbox;
GtkWidget *close_button;
GtkWidget *apply_button;
GSList *rb_group;
// Init...
gtk_init(&argc, &argv);
// UI:
main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(main_window), "Phitherek_' s Startup Profiler - GTK Config Tool v. 0.1 (c) 2011 by Phitherek_");
main_vbox = gtk_vbox_new(false, 5);
top_vbox = gtk_vbox_new(false, 5);
title_label = gtk_label_new("Phitherek_' s Startup Profiler - GTK Config Tool v. 0.1 (c) 2011 by Phitherek_");
gtk_box_pack_start(GTK_BOX(top_vbox), title_label, true, true, 5);
gtk_widget_show(title_label);
system("echo $HOME > houm");
ifstream houm("houm");
houm >> homedir;
houm.close();
system("rm houm");
settingsdir = homedir + "/.phsp/";
profiledir = settingsdir + "profiles/";
cmd = "ls " + profiledir + "*.phsp > " + settingsdir + "profilelist";
system(cmd.c_str());
fn = settingsdir + "profilelist";
ifstream profilelist(fn.c_str());
vector<string> profiles;
while(!profilelist.eof()) {
string tmp;
profilelist >> tmp;
if(profilelist) {
profiles.push_back(tmp);
}
}
profilelist.close();
fn = settingsdir + "active";
ifstream active(fn.c_str());
string acs;
if(active) {
active >> act;
active.close();
acs = "Active profile: "+act;
} else {
acs = "Active profile not set!";
active.close();
}
active_profile_label = gtk_label_new(acs.c_str());
gtk_box_pack_start(GTK_BOX(top_vbox), active_profile_label, true, true, 5);
gtk_widget_show(active_profile_label);
welcome_label = gtk_label_new("Welcome to Phitherek_' s Startup Profiler GTK Config Tool!\nPlease select a profile from the list below:");
gtk_box_pack_start(GTK_BOX(top_vbox), welcome_label, true, true, 5);
gtk_widget_show(welcome_label);
gtk_box_pack_start(GTK_BOX(main_vbox), top_vbox, true, true, 5);
gtk_widget_show(top_vbox);
separator = gtk_hseparator_new();
gtk_box_pack_start(GTK_BOX(main_vbox), separator, true, true, 5);
gtk_widget_show(separator);
middle_vbox = gtk_vbox_new(false, 5);
bool empty = false;
if(profiles.size() == 0) {
empty = true;
empty_label = gtk_label_new("List empty!");
gtk_box_pack_start(GTK_BOX(middle_vbox), empty_label, true, true, 5);
gtk_widget_show(empty_label);
} else {
for(int i = 0; i < profiles.size(); i++) {
	if(i == 0) {
	radio_button = gtk_radio_button_new_with_label(NULL, profiles[i].c_str());	
	} else {
	rb_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button));
	radio_button = gtk_radio_button_new_with_label(rb_group, profiles[i].c_str());	
	}
	gtk_box_pack_start(GTK_BOX(middle_vbox), radio_button, true, true, 5);
	if(profiles[i] == act) {
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), true);
	selected = (gchar*)profiles[i].c_str();	
	}
	gtk_widget_show(radio_button);
	g_signal_connect(radio_button, "toggled", G_CALLBACK(set_active_profile), (void*)gtk_button_get_label(GTK_BUTTON(radio_button)));
}	
}
gtk_box_pack_start(GTK_BOX(main_vbox), middle_vbox, true, true, 5);
gtk_widget_show(middle_vbox);
separator = gtk_hseparator_new();
gtk_box_pack_start(GTK_BOX(main_vbox), separator, true, true, 5);
gtk_widget_show(separator);
bottom_hbox = gtk_hbox_new(false, 5);
if(!empty) {
apply_button = gtk_button_new_with_label("Apply");
gtk_box_pack_start(GTK_BOX(bottom_hbox), apply_button, true, true, 5);
gtk_widget_show(apply_button);
g_signal_connect(apply_button, "clicked", G_CALLBACK(apply), main_window);
}
close_button = gtk_button_new_with_label("Close");
gtk_box_pack_start(GTK_BOX(bottom_hbox), close_button, true, true, 5);
gtk_widget_show(close_button);
g_signal_connect(close_button, "clicked", G_CALLBACK(destroy), NULL);
gtk_box_pack_start(GTK_BOX(main_vbox), bottom_hbox, true, true, 5);
gtk_widget_show(bottom_hbox);
gtk_container_add(GTK_CONTAINER(main_window), main_vbox);
gtk_widget_show(main_vbox);
g_signal_connect(main_window, "delete_event", G_CALLBACK(delete_event), NULL);
g_signal_connect(main_window, "destroy", G_CALLBACK(destroy), NULL);
gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
gtk_widget_show(main_window);
// Run!
gtk_main();
return EXIT_SUCCESS;
}
